/*
 * Taylor Andrews
 *
 * Key bindings:
 * f          Toggle first person
 * m          Toggle orthogonal and perspective (must be out of first person)
 * w/s        Move in first person
 * a/d        Rotate camera in first person
 * PgUp/PgDn  Zoom in and zoom out
 * 1/2        Change FOV
 * arrows     Change view angle
 * space      Pause light
 * 0          Reset view angle
 * ESC        Exit
 */

#include "scene.h"
#include "loadtexbmp.h"

/* Necessary Function Prototypes */
void idle();

/* Global Variables */
/* Window Settings */
int th = 0; // Azimuth of view angle
int ph = 0; // Elevation of view angle
int rot = 0; // Rotation in first person
int fov = 60; // Field of view
double asp = 1; // Window aspect ratio
double dim = 5.0; // Dimension of orthogonal box

/* Vectors */
vect camera = {0, 0, 0}; // Represents where the camera is pointed
vect eye = {0, 0, 5}; // Represents where the eye is located

/* Modes */
int fp = 0; // Toggle between first person and global view
int mode = 1; // Toggle orthogonal and projection
int move = 1; // Move the light

/* Light Values */
float yLight = 9; // Light y height
int distance = 7;  // Light distance
int local = 0;  // Local Viewer Model
int emission = 0;  // Emission intensity (%)
int ambient = 40;  // Ambient intensity (%)
int diffuse = 100;  // Diffuse intensity (%)
int specular = 1;  // Specular intensity (%)
float shinyvec[1];    // Shininess (value)
int zh  = 90;  // Light azimuth

/* Shadows */
#define dFloor 100
#define yFloor -4.6
float N[] = {0, -1, 0}; // Normal vector for the plane
float E[] = {0, yFloor, 0 }; // Point of the plane

/* Textures */
unsigned int textures[10]; // Textures for Fighters
unsigned int skybox[2]; // Skybox textures
unsigned int ground[1]; // Ground Texture

/* 
 * Adapted from example 34
 *
 * Multiply the current ModelView-Matrix with a shadow-projetion matrix.
 *
 * L is the position of the light source
 * E is a point within the plane on which the shadow is to be projected.  
 * N is the normal vector of the plane.
 *
 * Everything that is drawn after this call is "squashed" down to the plane.
 */
void ShadowProjection(float L[4], float E[4], float N[4])
{
    float mat[16];
    float e = E[0]*N[0] + E[1]*N[1] + E[2]*N[2];
    float l = L[0]*N[0] + L[1]*N[1] + L[2]*N[2];
    float c = e - l;
    
    // Create the matrix.
    mat[0] = N[0]*L[0]+c; mat[4] = N[1]*L[0];   mat[8]  = N[2]*L[0];   mat[12] = -e*L[0];
    mat[1] = N[0]*L[1];   mat[5] = N[1]*L[1]+c; mat[9]  = N[2]*L[1];   mat[13] = -e*L[1];
    mat[2] = N[0]*L[2];   mat[6] = N[1]*L[2];   mat[10] = N[2]*L[2]+c; mat[14] = -e*L[2];
    mat[3] = N[0];        mat[7] = N[1];        mat[11] = N[2];        mat[15] = -l;
    
    // Multiply modelview matrix
    glMultMatrixf(mat);
}

/* 
 * Draw the Skybox
 * Adapted from Example 25
 */
void sky(double size)
{
    glColor3f(1, 0, 0);
    glEnable(GL_TEXTURE_2D);

    // Sides
    glBindTexture(GL_TEXTURE_2D, skybox[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.00,0); glVertex3f(-size,-size,-size);
        glTexCoord2f(0.25,0); glVertex3f(+size,-size,-size);
        glTexCoord2f(0.25,1); glVertex3f(+size,+size,-size);
        glTexCoord2f(0.00,1); glVertex3f(-size,+size,-size);

        glTexCoord2f(0.25,0); glVertex3f(+size,-size,-size);
        glTexCoord2f(0.50,0); glVertex3f(+size,-size,+size);
        glTexCoord2f(0.50,1); glVertex3f(+size,+size,+size);
        glTexCoord2f(0.25,1); glVertex3f(+size,+size,-size);

        glTexCoord2f(0.50,0); glVertex3f(+size,-size,+size);
        glTexCoord2f(0.75,0); glVertex3f(-size,-size,+size);
        glTexCoord2f(0.75,1); glVertex3f(-size,+size,+size);
        glTexCoord2f(0.50,1); glVertex3f(+size,+size,+size);

        glTexCoord2f(0.75,0); glVertex3f(-size,-size,+size);
        glTexCoord2f(1.00,0); glVertex3f(-size,-size,-size);
        glTexCoord2f(1.00,1); glVertex3f(-size,+size,-size);
        glTexCoord2f(0.75,1); glVertex3f(-size,+size,+size);
    glEnd();

     // Top and bottom
    glBindTexture(GL_TEXTURE_2D, skybox[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0); glVertex3f(+size,+size,-size);
        glTexCoord2f(0.5,0); glVertex3f(+size,+size,+size);
        glTexCoord2f(0.5,1); glVertex3f(-size,+size,+size);
        glTexCoord2f(0.0,1); glVertex3f(-size,+size,-size);  

        glTexCoord2f(1.0,1); glVertex3f(-size,-size,+size);
        glTexCoord2f(0.5,1); glVertex3f(+size,-size,+size);
        glTexCoord2f(0.5,0); glVertex3f(+size,-size,-size);
        glTexCoord2f(1.0,0); glVertex3f(-size,-size,-size);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

/* Set the projection */
void project()
{
    glMatrixMode(GL_PROJECTION); // Tell OpenGL we want to manipulate the projection matrix
    glLoadIdentity(); // Undo previous transformations
    // First person
    if(fp) 
    {
        gluPerspective(fov,asp,dim/16,16*dim);
    }
    else 
    {
      // Perspective
      if (mode)
         gluPerspective(fov,asp,dim/16,16*dim);
      // Orthogonal projection
      else
         glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
    } 
    glMatrixMode(GL_MODELVIEW); // Switch to manipulating the model matrix
    glLoadIdentity(); // Undo previous transformations
}

/* Draw the scene */
void display()
{
    int err; // For error checking

    // Set up Light
    float Ambient[]  = {0.3, 0.3, 0.3, 1.0};
    float Diffuse[]  = {1.0, 1.0, 1.0, 1.0};
    float Specular[] = {0.01*specular, 0.01*specular, 0.01*specular, 1.0};
    float Position[] = {distance*Cos(zh), yLight, distance*Sin(zh), 1.0};

    /* Create 1st Light Vectors */
    // float Ambient[] = {0.01*ambient, 0.01*ambient, 0.01*ambient, 1.0};
    // float Diffuse[] = {0.01*diffuse, 0.01*diffuse, 0.01*diffuse, 1.0};
    // float Specular[] = {0.01*specular, 0.01*specular, 0.01*specular, 1.0};

    // Erase the window and clear the depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // Enable Z-buffering
    glLoadIdentity(); // Reset the transformation matrix

    if (fp) {
        camera.x = 2 * dim * Sin(rot); // Ajust the camera vector based on rotation
        camera.z = -2 * dim * Cos(rot);

        gluLookAt(eye.x,eye.y,eye.z, camera.x+eye.x,eye.y,camera.z+eye.z, 0,1,0); // Use gluLookAt, y is the up-axis
    }
    else {
        // Perspective mode sets eye position
        if (mode) {
          double px = -2 * dim * Sin(th) * Cos(ph);
          double py = +2 * dim * Sin(ph);
          double pz = +2 * dim * Cos(th) * Cos(ph);
          gluLookAt(px,py,pz , 0,0,0 , 0,Cos(ph),0);
        }
        // Orthogonal - set world orientation
        else
        {
           glRotatef(ph,1,0,0);
           glRotatef(th,0,1,0);
        }
    }
    
    sky(3.5*dim);  // Draw the skybox
 
    // Draw the light as a sphere
    glColor3f(1,1,1);
    glPushMatrix();
        glTranslated(Position[0],Position[1],Position[2]);
        glutSolidSphere(0.03,10,10);
    glPopMatrix();

    glEnable(GL_NORMALIZE); // Normalize normals
    glEnable(GL_LIGHTING); // Enable lighting

    // Enable color material    
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    // Enable light
    glEnable(GL_LIGHT0);
    
    /* Set Light Characteristics */ 
    glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
    glLightfv(GL_LIGHT0, GL_POSITION, Position);

    /* Surrounding Arena */
    glEnable(GL_POLYGON_OFFSET_FILL);
    drawSquares();    
    glDisable(GL_POLYGON_OFFSET_FILL);

    /* Draw the Scene */
    drawScene(zh);

    //  Save what is glEnabled
    glPushAttrib(GL_ENABLE_BIT);

    /* Shadows, adapted from example 34 */
    glDisable(GL_LIGHTING);
    
    // Enable stencil operations
    glEnable(GL_STENCIL_TEST);

         /*
          *  Step 1:  Set stencil buffer to 1 where there are shadows
          */
         //  Existing value of stencil buffer doesn't matter
         glStencilFunc(GL_ALWAYS,1,0xFFFFFFFF);
         //  Set the value to 1 (REF=1 in StencilFunc)
         //  only if Z-buffer would allow write
         glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
         //  Make Z-buffer and color buffer read-only
         glDepthMask(0);
         glColorMask(0,0,0,0);
         //  Draw flattened scene
         glPushMatrix();
         ShadowProjection(Position,E,N);
         drawScene(zh);
         glPopMatrix();
         //  Make Z-buffer and color buffer read-write
         glDepthMask(1);
         glColorMask(1,1,1,1);

         /*
          *  Step 2:  Draw shadow masked by stencil buffer
          */
         //  Set the stencil test draw where stencil buffer is > 0
         glStencilFunc(GL_LESS,0,0xFFFFFFFF);
         //  Make the stencil buffer read-only
         glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
         //  Enable blending
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
         glColor4f(0,0,0,0.5);
         //  Draw the shadow over the entire floor
         glBegin(GL_QUADS);
         glVertex3f(-dFloor,yFloor,-dFloor);
         glVertex3f(+dFloor,yFloor,-dFloor);
         glVertex3f(+dFloor,yFloor,+dFloor);
         glVertex3f(-dFloor,yFloor,+dFloor);
         glEnd();
    

    // Undo everything we enabled above
    glPopAttrib();

    glDisable(GL_LIGHTING); // Done lighting, disable it

    /* Error Checking */
    err = glGetError();
    if (err) fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), "display");

    /* Render the scene */
    glFlush();
    glutSwapBuffers();
}

/* Called when a key is pressed */
void key(unsigned char ch, int x, int y)
{
    // Exit on ESC
    if (ch == 27)
    {
        exit(0);
    }
    //  Pause Light
    else if (ch == ' ') 
    {
        move = 1-move;
    }
    // Toggle first person
    else if (ch == 'f' || ch == 'F')
    {
        fp = 1-fp;
    }
    // If we are in first person, allow for navigation
    if (fp) 
    {
        double dt = 0.05;
        if (ch == 'w' || ch == 'W')
        {
            eye.x += camera.x*dt; // Update the x direction of the eye vector based on the camera vector
            eye.z += camera.z*dt; // Update the z direction of the eye vector based on the camera vector
        }
        else if (ch == 'a' || ch == 'A')
        {
            rot -= 3;
        }
        else if (ch == 's' || ch == 'S')
        {
            eye.x -= camera.x*dt; // Update the x direction of the eye vector based on the camera vector
            eye.z -= camera.z*dt; // Update the z direction of the eye vector based on the camera vector
        }
        else if (ch == 'd' || ch == 'D')
        {
            rot += 3;
        }

        // Keep angles to +/-360 degrees
        rot %= 360;
   }
   // We are in orthogonal or perspective
   else 
   {
        // Reset view angle
        if (ch == '0')
        {
            th = ph = 0;
        }
        // Change field of view angle
        else if (ch == '1') 
        {
            fov--;
        }
        else if (ch == '2')
        {
            fov++;
        }
        //  Switch display mode
        else if (ch == 'm' || ch == 'M')
        {
           mode = 1-mode;
        }
   }

   project();
   glutIdleFunc(move?idle:NULL); // Animate
   glutPostRedisplay(); // GLUT needs to redisplay the scene
}


/* Called when an arrow key is pressed */
void special(int key, int x, int y)
{
    if(!fp) {
        // Right arrow key increases angle by 5 degrees
        if (key == GLUT_KEY_RIGHT)
        {
            th += 5;
        }
        // Left arrow key decreases angle by 5 degrees
        else if (key == GLUT_KEY_LEFT)
        {
            th -= 5;
        }
        // Up arrow key increases elevation by 5 degrees
        else if (key == GLUT_KEY_UP)
        {
            ph -= 5;
        }
        // Down arrow key decreases elevation by 5 degrees
        else if (key == GLUT_KEY_DOWN)
        {
            ph += 5;
        }
        /* Keep angles to +/-360 degrees */
        th %= 360;
        ph %= 360;

        //PageUp key increase dim
        if (key == GLUT_KEY_PAGE_UP && dim>1)
            dim -= 0.1;
        //PageDown key decrease dim
        else if (key == GLUT_KEY_PAGE_DOWN)
            dim += 0.1;
   }
   project();
   //Project(fov, asp, dim); // Update projection
   glutIdleFunc(move?idle:NULL); // Animate
   glutPostRedisplay(); // GLUT needs to redisplay the scene
}

/* Called when glut is idle */
void idle()
{
    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0; // Keep track of time for animations
    zh = fmod(90*t,360.0);
    glutPostRedisplay(); // Tell glut to redisplay the scene
}

/* Called when window is resized */
void reshape(int width, int height)
{
    asp = (height>0) ? (double) width/height : 1; // Aspect ration of width to height
    //glViewport(-4, -4, width+4, height+4); // Set the viewport to the entire window
    project(); // Set projection
    //  Set the viewport to the entire window
    glViewport(0,0, width,height);
    //  Set projection
    //Project(fov,asp,dim);
}

/* Start Glut */
int main(int argc, char* argv[])
{
    int err; // For error checking

    /* Initialize Window */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_STENCIL | GLUT_DEPTH);
    glutInitWindowSize(800,450); // Window size
    glutCreateWindow("Taylor Andrews"); // Name the window

    /* Tell Glut What to Call */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    /* Load Textures */
    textures[0] = LoadTexBMP("steel.bmp"); // Primary Mor Armor Texture
    textures[1] = LoadTexBMP("gem.bmp"); // Texture for Helmet Gems
    textures[2] = LoadTexBMP("eye.bmp"); // Eye Texture
    textures[3] = LoadTexBMP("gold.bmp"); // Primary Fin Armor Texture 
    textures[4] = LoadTexBMP("greenCloth.bmp");
    textures[5] = LoadTexBMP("leather.bmp"); // Mor Gauntlet and Boot Texture
    textures[6] = LoadTexBMP("steelHelmet.bmp"); // Secondary Mor Armor Texture
    textures[7] = LoadTexBMP("chainmail.bmp"); // For Chainmail
    textures[8] = LoadTexBMP("goldHelmet.bmp"); // Secondary Fin Armor Texture
    textures[9] = LoadTexBMP("leather.bmp"); // Fin Gauntlet and Boot Texture

    skybox[0] = LoadTexBMP("sky0.bmp");
    skybox[1] = LoadTexBMP("sky1.bmp");

    ground[0] = LoadTexBMP("ground.bmp");

    /* Error Checking */
    err = glGetError();
    if (err) fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), "init");

    glutMainLoop(); // Start glut
    return 0;
}
