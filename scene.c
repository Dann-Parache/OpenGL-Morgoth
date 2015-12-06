/*
 * Taylor Andrews
 * Draw the Scene.
 */

#include "scene.h"

/* Draw the Scene */
void drawScene(double t) {
    // t = 0; // Uncomment to stop animation (for debugging)

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
}

/* Function to draw a the ground */
void drawSquares() {
    int i, j; // Loop Iterators
    int n = 20; // Number of chunks in the big square
    double s = 10; // Size of the square

    glColor3f(.38, .20, .07); // Medium Brown

    /* Enable Textures */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ground[0]);

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

    glDisable(GL_TEXTURE_2D); // Disable textures
}