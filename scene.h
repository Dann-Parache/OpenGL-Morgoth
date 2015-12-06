/*
 * Taylor Andrews
 * Header file for the scene.
 */

#ifndef SCENE_H
#define SCENE_H
 
#include "mor.h"
#include "fin.h"

/* Vector */
typedef struct {
    double x;
	double y;
	double z;
} vect;

/* Global Variables */
extern unsigned int textures[10];
extern unsigned int ground[1];

/* Draw the Scene */
void drawScene(double t);
void drawSquares(); // Draw the ground

#endif
