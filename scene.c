/*
 *  Taylor Andrews
 */

#include "scene.h"
#include "mor.h"
#include "fin.h"
 
/* Global Variables */
extern int emission;
extern float shinyvec[1];
extern unsigned int textures[10];

/* Draw the Scene */
void drawScene() {

    glPushMatrix();
    //glTranslated(-1, 1, 0);
    //glScaled(1, 1, 1);
        drawMor(-2.5, 0.8, -1.1, 1, 1, 1);
    glPopMatrix();

    glPushMatrix();
    //glTranslated(0, -1, 0);
    //glScaled(5, 5, 5);
        drawFin(2.5, 0.8, -1.1, 7.5, 7.5, 7.5);
    glPopMatrix();
}