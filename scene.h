/*
 * Taylor Andrews
 * Header file for the scene.
 */

#ifndef SCENE_H
#define SCENE_H
 
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define GL_GLEXT_PROTOTYPES // OpenGL with prototypes for glext
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "CSCIx229.h"
#include "mor.h"
#include "fin.h"

#define PI 3.141592

/* Vector */
typedef struct {
    double x;
	double y;
	double z;
} vect;

/* Global Variables */
extern unsigned int textures[10];
extern unsigned int ground[1];

extern float Lpos[4];
extern float ylight;

/* Draw the Scene */
void drawScene(int light, double t);
void drawSquare();
void Lights(int light, double t); // Draw Light

/* Glut Functions */
void project();
void display();
void key(unsigned char ch, int x, int y);
void special(int key, int x, int y);
void idle();
void reshape(int width, int height);

#endif
