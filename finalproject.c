/*
 *  Taylor Andrews
 */

#include "finalproject.h"
#include "mor.h"
#include "fin.h"
 
/* Global Variables */
extern int emission;
extern float shinyvec[1];
extern unsigned int textures[4];

/* Draw the Scene */
void drawScene() {
    glPushMatrix();
    glScaled(1, 1, 1);
        drawMor();
    glPopMatrix();

    glPushMatrix();
    glScaled(7, 7, 7);
        drawFin();
    glPopMatrix();
}