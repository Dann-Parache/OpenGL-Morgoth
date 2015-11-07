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

#include "finalproject.h"

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
int mode = 0; // Toggle between perspective and orthogonal
int fp = 0; // Toggle between first person and global view
int move = 1; // Move the light

/* Light Values */
int distance = 5;  // Light distance
int local = 0;  // Local Viewer Model
int emission = 0;  // Emission intensity (%)
int ambient = 40;  // Ambient intensity (%)
int diffuse = 100;  // Diffuse intensity (%)
int specular = 1;  // Specular intensity (%)
//int shininess = 0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
int zh  = 90;  // Light azimuth

/* Textures */
unsigned int textures[4]; // Texture names

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
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // Erase the window and clear the depth buffer
    glClearColor(.3, .3, .3, 0);
    glEnable(GL_DEPTH_TEST); // Enable Z-buffering
    glLoadIdentity(); // Reset the transformation matrix

    if (fp) {
        camera.x = 2 * dim * Sin(rot); // Ajust the camera vector based on rotation
        camera.z = -2 * dim * Cos(rot);

        gluLookAt(eye.x,eye.y,eye.z, camera.x+eye.x,eye.y,camera.z+eye.z, 0,1,0); // Use gluLookAt, y is the up-axis

    }
    else {
        // Perspective mode sets eye position
        if (mode)
        {
            double px = -2 * dim * Sin(th) * Cos(ph);
            double py = +2 * dim * Sin(ph);
            double pz = +2 * dim * Cos(th) * Cos(ph);
            gluLookAt(px,py,pz , 0,0,0 , 0,Cos(ph),0);
        }
        // Orthogonal mode sets world orientation
        else
        {
            glRotatef(ph,1,0,0);
            glRotatef(th,0,1,0);
        }
    }
    
    glShadeModel(GL_SMOOTH);

    /* Create 1st Light Vectors */
    float Ambient[] = {0.01*ambient, 0.01*ambient, 0.01*ambient, 1.0};
    float Diffuse[] = {0.01*diffuse, 0.01*diffuse, 0.01*diffuse, 1.0};
    float Specular[] = {0.01*specular, 0.01*specular, 0.01*specular, 1.0};
    
    float Position[]  = {distance*Cos(zh), 0, distance*Sin(zh), 1.0}; // Light position

    //glColor3f(1, 1, 1); 
    //ball(Position[0], Position[1], Position[2], 0.1, -1); // Draw the light position as a ball

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    /* Location of Viewer */
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
    
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHT0);
    
    /* Set Light Characteristics */ 
    glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
    glLightfv(GL_LIGHT0, GL_POSITION, Position);

    /* Draw the Scene */
    drawScene();

    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING); // Done lighting, disable it

    /* Render the scene */
    ErrCheck("display");
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
        // Switch display mode
        else if (ch == 'm' || ch == 'M')
        {
            mode = 1-mode;
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

   project(); // Update projection
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
    asp = (height>0)?(double)width/height:1; // Aspect ration of width to height
    glViewport(0, 0, width, height); // Set the viewport to the entire window
    project(); // Set projection
}

/* Start Glut */
int main(int argc, char* argv[])
{
    /* Initialize Window */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Ask for z buffering
    glutInitWindowSize(800,450); // Window size
    glutCreateWindow("Taylor Andrews"); // Name the window

    /* Tell Glut What to Call */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    /* Load Textures */
    textures[0] = LoadTexBMP("gray_armor.bmp");
    textures[1] = LoadTexBMP("opal.bmp");
    textures[2] = LoadTexBMP("mor-eye.bmp");
    textures[3] = LoadTexBMP("gold.bmp");

    ErrCheck("init"); // Error checking

    glutMainLoop(); // Start glut
    return 0;
}
