/*
 *  Taylor Andrews
 *
 *  Key bindings:
 *  1      
 *  -      Zoom Out
 *  +      Zoom in
 *  arrows Change view angle
 *  ESC    Exit
 */

#include "scene.h"

#define MAXN 64


//typedef struct {float x,y,z;} Point;

/* Global Variables */
/* Window Settings */
int th = 0; // Azimuth of view angle
int ph = 0; // Elevation of view angle
int rot = 0; // Rotation in first person
int fov = 55; // Field of view
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
float Lpos[4]; // Light position
float ylight = 2; // Light y height
int distance = 7; // Light distance
int local = 0; // Local Viewer Model
int emission = 0; // Emission intensity (%)
int ambient = 40; // Ambient intensity (%)
int diffuse = 100; // Diffuse intensity (%)
int specular = 1; // Specular intensity (%)
//int shininess = 0; // Shininess (power of two)
float shinyvec[1]; // Shininess (value)
int zh = 90; // Light azimuth

/* Textures */
unsigned int textures[10]; // Textures for Fighters
unsigned int skybox[2]; // Skybox textures
unsigned int ground[1]; // Ground Texture

/* Shaders */
int shader;

/* Shadows */
int obj = 2;
int box = 1; // Skybox
unsigned int framebuf=0;// Frame buffer id
double       Svec[4];   // Texture planes S
double       Tvec[4];   // Texture planes T
double       Rvec[4];   // Texture planes R
double       Qvec[4];   // Texture planes Q
int          Width;     // Window width
int          Height;    // Window height
int          shadowdim; // Size of shadow map textures
char* text[]={"Shadows","Shadow Map"};

/* Draw the Skybox
 * Adapted from Example 25
 */
void sky(double size)
{
    glColor3f(1, 0, 0);
    glEnable(GL_TEXTURE_2D);

    // Sides of the sky box
    // glBindTexture(GL_TEXTURE_2D, textures[8]);
    // glBegin(GL_QUADS);
    //     glTexCoord2f(0.00,0.33); glVertex3f(-size,-size,-size);
    //     glTexCoord2f(0.25,0.33); glVertex3f(+size,-size,-size);
    //     glTexCoord2f(0.25,0.66); glVertex3f(+size,+size,-size);
    //     glTexCoord2f(0.00,0.66); glVertex3f(-size,+size,-size);

    //     glTexCoord2f(0.25,0.33); glVertex3f(+size,-size,-size);
    //     glTexCoord2f(0.50,0.33); glVertex3f(+size,-size,+size);
    //     glTexCoord2f(0.50,0.66); glVertex3f(+size,+size,+size);
    //     glTexCoord2f(0.25,0.66); glVertex3f(+size,+size,-size);

    //     glTexCoord2f(0.50,0.33); glVertex3f(+size,-size,+size);
    //     glTexCoord2f(0.75,0.33); glVertex3f(-size,-size,+size);
    //     glTexCoord2f(0.75,0.66); glVertex3f(-size,+size,+size);
    //     glTexCoord2f(0.50,0.66); glVertex3f(+size,+size,+size);

    //     glTexCoord2f(0.75,0.33); glVertex3f(-size,-size,+size);
    //     glTexCoord2f(1.00,0.33); glVertex3f(-size,-size,-size);
    //     glTexCoord2f(1.00,0.66); glVertex3f(-size,+size,-size);
    //     glTexCoord2f(0.75,0.66); glVertex3f(-size,+size,+size);
    // glEnd();

    // // Top of the sky box
    // glPushMatrix();
    // glRotated(360, 0, 1, 0);
    // glBegin(GL_QUADS);
    //     glTexCoord2f(.33,0.67); glVertex3f(+size,+size,-size);
    //     glTexCoord2f(.54,0.67); glVertex3f(+size,+size,+size);
    //     glTexCoord2f(.54,1); glVertex3f(-size,+size,+size);  
    //     glTexCoord2f(.33,1); glVertex3f(-size,+size,-size);

    //     // glTexCoord2f(0,0); glVertex3f(+size,+size,-size);
    //     // glTexCoord2f(1,0); glVertex3f(+size,+size,+size);
    //     // glTexCoord2f(1,1); glVertex3f(-size,+size,+size);  
    //     // glTexCoord2f(0,1); glVertex3f(-size,+size,-size);

    // glEnd();
    // glPopMatrix();

    // // Bottom of the sky box
    // glBegin(GL_QUADS);
    //     glTexCoord2f(.33,0.33); glVertex3f(-size-1,-size+1,+size+1);
    //     glTexCoord2f(0.5,0.33); glVertex3f(+size+1,-size+1,+size+1);
    //     glTexCoord2f(0.5,0); glVertex3f(+size+1,-size+1,-size-1);
    //     glTexCoord2f(.33,0); glVertex3f(-size-1,-size+1,-size-1);
    // glEnd();

    //  Sides
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

     //Top and bottom
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
      if (mode)
         gluPerspective(fov,asp,dim/16,16*dim);
      //  Orthogonal projection
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
    int id;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Erase the window and clear the depth buffer
    //glClearColor(.3, .3, .3, 0);
    //glEnable(GL_DEPTH_TEST); // Enable Z-buffering
    glDisable(GL_LIGHTING); // Turn off lighting
    glLoadIdentity(); // Reset the transformation matrix

    project();
    glViewport(0,0,Width,Height);

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
    
    sky(3.5*dim);

    /* Create 1st Light Vectors */
    // float Ambient[] = {0.01*ambient, 0.01*ambient, 0.01*ambient, 1.0};
    // float Diffuse[] = {0.01*diffuse, 0.01*diffuse, 0.01*diffuse, 1.0};
    // float Specular[] = {0.01*specular, 0.01*specular, 0.01*specular, 1.0};
    
    // float Position[]  = {distance*Cos(zh), 0, distance*Sin(zh), 1.0}; // Light position

    // glColor3f(1, 1, 1); 
    // morBall(Position[0], Position[1], Position[2], 0.1, 0, 0, -1); // Draw the light position as a ball
    
    /* Draw the Light */
    glColor3f(1,1,1);

    glPushMatrix();
    glTranslated(Lpos[0],Lpos[1],Lpos[2]);
      glutSolidSphere(0.1,10,10);
    glPopMatrix();

    //  Enable shader program
    glUseProgram(shader);
    id = glGetUniformLocation(shader,"tex");
    if (id>=0) glUniform1i(id,0);
    id = glGetUniformLocation(shader,"depth");
    if (id>=0) glUniform1i(id,1);

    // Set up the eye plane for projecting the shadow map on the scene
    glActiveTexture(GL_TEXTURE1);
    glTexGendv(GL_S,GL_EYE_PLANE,Svec);
    glTexGendv(GL_T,GL_EYE_PLANE,Tvec);
    glTexGendv(GL_R,GL_EYE_PLANE,Rvec);
    glTexGendv(GL_Q,GL_EYE_PLANE,Qvec);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_R_TO_TEXTURE);
    glActiveTexture(GL_TEXTURE0);

    //glEnable(GL_NORMALIZE);
    //glEnable(GL_LIGHTING);

    /* Location of Viewer */
    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
    
    //glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    //glEnable(GL_COLOR_MATERIAL);

    //glEnable(GL_LIGHT0);
    
    /* Set Light Characteristics */ 
    // glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
    // glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
    // glLightfv(GL_LIGHT0, GL_POSITION, Position);

    /* Draw the Scene */
    drawScene(1, zh);

    //  Disable shader program
    glUseProgram(0);
    
    //glDisable(GL_LIGHTING); // Done lighting, disable it

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
           mode = 1-mode;
   }

   project();
   //Project(fov, asp, dim);
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

/*
 *  Build Shadow Map
 */
void ShadowMap(void)
{
   double Lmodel[16];  //  Light modelview matrix
   double Lproj[16];   //  Light projection matrix
   double Tproj[16];   //  Texture projection matrix
   double Dim=2.0;     //  Bounding radius of scene
   double Ldist;       //  Distance from light to scene center

   //  Save transforms and modes
   glPushMatrix();
   glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);
   //  No write to color buffer and no smoothing
   glShadeModel(GL_FLAT);
   glColorMask(0,0,0,0);
   // Overcome imprecision
   glEnable(GL_POLYGON_OFFSET_FILL);

    //  Turn off lighting and set light position
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);

   //  Light distance
   Ldist = sqrt(Lpos[0]*Lpos[0] + Lpos[1]*Lpos[1] + Lpos[2]*Lpos[2]);
   if (Ldist<1.1*Dim) Ldist = 1.1*Dim;

   //  Set perspective view from light position
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(114.6*atan(Dim/Ldist),1,Ldist-Dim,Ldist+Dim);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(Lpos[0],Lpos[1],Lpos[2] , 0,0,0 , 0,1,0);
   //  Size viewport to desired dimensions
   glViewport(0,0,shadowdim,shadowdim);

   // Redirect traffic to the frame buffer
   glBindFramebuffer(GL_FRAMEBUFFER,framebuf);

   // Clear the depth buffer
   glClear(GL_DEPTH_BUFFER_BIT);
   // Draw all objects that can cast a shadow
   drawScene(0, zh);

   //  Retrieve light projection and modelview matrices
   glGetDoublev(GL_PROJECTION_MATRIX,Lproj);
   glGetDoublev(GL_MODELVIEW_MATRIX,Lmodel);

   // Set up texture matrix for shadow map projection,
   // which will be rolled into the eye linear
   // texture coordinate generation plane equations
   glLoadIdentity();
   glTranslated(0.5,0.5,0.5);
   glScaled(0.5,0.5,0.5);
   glMultMatrixd(Lproj);
   glMultMatrixd(Lmodel);

   // Retrieve result and transpose to get the s, t, r, and q rows for plane equations
   glGetDoublev(GL_MODELVIEW_MATRIX,Tproj);
   Svec[0] = Tproj[0];    Tvec[0] = Tproj[1];    Rvec[0] = Tproj[2];    Qvec[0] = Tproj[3];
   Svec[1] = Tproj[4];    Tvec[1] = Tproj[5];    Rvec[1] = Tproj[6];    Qvec[1] = Tproj[7];
   Svec[2] = Tproj[8];    Tvec[2] = Tproj[9];    Rvec[2] = Tproj[10];   Qvec[2] = Tproj[11];
   Svec[3] = Tproj[12];   Tvec[3] = Tproj[13];   Rvec[3] = Tproj[14];   Qvec[3] = Tproj[15];

   // Restore normal drawing state
   glShadeModel(GL_SMOOTH);
   glColorMask(1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);
   glPopAttrib();
   glPopMatrix();
   glBindFramebuffer(GL_FRAMEBUFFER,0);

   //  Check if something went wrong
   ErrCheck("ShadowMap");
}

void InitMap()
{
   unsigned int shadowtex; //  Shadow buffer texture id
   int n;

   //  Make sure multi-textures are supported
   glGetIntegerv(GL_MAX_TEXTURE_UNITS,&n);
   if (n<2) Fatal("Multiple textures not supported\n");

   //  Get maximum texture buffer size
   glGetIntegerv(GL_MAX_TEXTURE_SIZE,&shadowdim);
   //  Limit texture size to maximum buffer size
   glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE,&n);
   if (shadowdim>n) shadowdim = n;
   //  Limit texture size to 2048 for performance
   if (shadowdim>2048) shadowdim = 2048;
   if (shadowdim<512) Fatal("Shadow map dimensions too small %d\n",shadowdim);

   //  Do Shadow textures in MultiTexture 1
   glActiveTexture(GL_TEXTURE1);

   //  Allocate and bind shadow texture
   glGenTextures(1,&shadowtex);
   glBindTexture(GL_TEXTURE_2D,shadowtex);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, shadowdim, shadowdim, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

   //  Map single depth value to RGBA (this is called intensity)
   glTexParameteri(GL_TEXTURE_2D,GL_DEPTH_TEXTURE_MODE,GL_INTENSITY);

   //  Set texture mapping to clamp and linear interpolation
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

   //  Set automatic texture generation mode to Eye Linear
   glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
   glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
   glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
   glTexGeni(GL_Q,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);

   // Switch back to default textures
   glActiveTexture(GL_TEXTURE0);

   // Attach shadow texture to frame buffer
   glGenFramebuffers(1,&framebuf);
   glBindFramebuffer(GL_FRAMEBUFFER,framebuf);
   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowtex, 0);
   //  Don't write or read to visible color buffer
   glDrawBuffer(GL_NONE);
   glReadBuffer(GL_NONE);
   //  Make sure this all worked
   if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) Fatal("Error setting up frame buffer\n");
   glBindFramebuffer(GL_FRAMEBUFFER,0);

   //  Check if something went wrong
   ErrCheck("InitMap");

   //  Create shadow map
   ShadowMap();
}

/* Called when glut is idle */
void idle()
{
    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0; // Keep track of time for animations
    //zh = fmod(90*t,360.0);
    zh = fmod(90*t,360.0);
    // Update shadow map
    //ShadowMap();
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

    Width = width;
    Height = height;

    //  Set projection
    //Project(fov,asp,dim);
}

/* Read in the Text File */
static char* ReadText(const char *file)
{
   int   n;
   char* buffer;
   //  Open file
   FILE* f = fopen(file,"rt");
   if (!f) Fatal("Cannot open text file %s\n",file);
   //  Seek to end to determine size, then rewind
   fseek(f,0,SEEK_END);
   n = ftell(f);
   rewind(f);
   //  Allocate memory for the whole file
   buffer = (char*)malloc(n+1);
   if (!buffer) Fatal("Cannot allocate %d bytes for text file %s\n",n+1,file);
   //  Snarf the file
   if (fread(buffer,n,1,f)!=1) Fatal("Cannot read %d bytes for text file %s\n",n,file);
   buffer[n] = 0;
   //  Close and return
   fclose(f);
   return buffer;
}

/* Create the Shader */
void CreateShader(int prog,const GLenum type,const char* file)
{
   //  Create the shader
   int shader = glCreateShader(type);
   //  Load source code from file
   char* source = ReadText(file);
   glShaderSource(shader,1,(const char**)&source,NULL);
   free(source);
   //  Compile the shader
   glCompileShader(shader);
   //  Attach to shader program
   glAttachShader(prog,shader);
}

/*
 *  Create the Shader Program
 */
int CreateShaderProg(const char* VertFile,const char* FragFile)
{
   //  Create program
   int prog = glCreateProgram();
   //  Create and compile vertex shader
   if (VertFile) CreateShader(prog,GL_VERTEX_SHADER,VertFile);
   //  Create and compile fragment shader
   if (FragFile) CreateShader(prog,GL_FRAGMENT_SHADER,FragFile);
   //  Link program
   glLinkProgram(prog);
   //  Return name
   return prog;
}

/* Start Glut */
int main(int argc, char* argv[])
{
    int err; // For error checking

    /* Initialize Window */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Ask for z buffering
    glutInitWindowSize(800,450); // Window size
    glutCreateWindow("Taylor Andrews"); // Name the window

#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
   if (!GLEW_VERSION_2_0) Fatal("OpenGL 2.0 not supported\n");
#endif

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

    glEnable(GL_DEPTH_TEST); // Enable Z-buffering

    // Initialize texture map
    shader = CreateShaderProg("shadow.vert","shadow.frag");
    InitMap();

    /* Error Checking */
    err = glGetError();
    if (err) fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), "init");

    glutMainLoop(); // Start glut
    return 0;
}
