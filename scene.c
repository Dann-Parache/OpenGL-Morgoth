/*
 *  Taylor Andrews
 */

#include "scene.h"
 
/* Global Variables */
//extern int emission;
//extern float shinyvec[1];
extern unsigned int textures[10]; // In case we need textures

/* Draw the Scene */
void drawScene(int light, double t) {
    //t = 0; // Uncomment to stop animation (for debugging)

    /* Setup Lights */
    Lights(light, t);

    /* Draw the Larger Fighter */
    glPushMatrix();
    glTranslated(-2.5, 2.5, 0);
    glRotated(90, 0, 1, 0);
    glScaled(0.68, 0.68, 0.68);
        drawMor(0, 0.8, 0, 1, 1, 1, t);
    glPopMatrix();

    /* Draw the Smaller Fighter */
    glPushMatrix();
    glTranslated(2.5, 0, 0);
    glRotated(-90, 0, 1, 0);
    glScaled(.6, .6, .6);
        drawFin(0, 3, 0, 7.5, 7.5, 7.5, t);
    glPopMatrix();

    if (!light) 
        return; // Floor has no shadow, exit early

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[0]);

    glColor3f(.38, .20, .07); // Medium Brown

    /* Surrounding Arena */
    drawSquare();

    glDisable(GL_TEXTURE_2D);
}

/* Helper Function to Draw a Simple Square */
void drawSquare() {
    int i, j; // Loop Iterators
    int n = 20; // Number of chunks in the big square
    double s = 10; // Size of the square

    glNormal3f(0, 1, 0);
    for (j =- n; j < n; j++)
    {
        glBegin(GL_QUAD_STRIP);
        for (i =- n; i <= n; i++)
        {
            glTexCoord2f(i+n, j+n); glVertex3f(i * s, -4.7, j * s);
            glTexCoord2f(i+n, j+1+n); glVertex3f(i * s, -4.7, (j+1) * s);
        }
        glEnd();
   }
}

/*
 * Create the Lights
 * Adapted from Example 36
 */
void Lights(int light, double t)
{
    // Set light position
    Lpos[0] = 2*Cos(t);
    Lpos[1] = ylight;
    Lpos[2] = 2*Sin(t);
    Lpos[3] = 1;

    // Enable Lighting
    if (light)
    {
        float Med[]  = {0.3, 0.3, 0.3, 1.0};
        float High[] = {1.0, 1.0, 1.0, 1.0};

        // Enable lighting with normalization
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);

        // glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);

        // Light 0
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0,GL_POSITION,Lpos);
        glLightfv(GL_LIGHT0,GL_AMBIENT,Med);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,High);

        // Light 1
    }
    // Disable Lighting
    else
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_NORMALIZE);
    }
}