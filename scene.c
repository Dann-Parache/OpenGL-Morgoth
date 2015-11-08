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
    glTranslated(1, 0, 0);
    glScaled(1, 1, 1);
        //drawMor();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(16, 16, 16);
        drawFin();
    glPopMatrix();
}