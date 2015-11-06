/*
 *  Taylor Andrews
 */

#ifndef FINALPROJECT_H
#define FINALPROJECT_H
 
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

#define PI 3.141592

/* Vector */
typedef struct {
    double x;
	double y;
	double z;
} vect;

/* Global Variables */
extern int th; // Azimuth of view angle
extern int ph; // Elevation of view angle
extern int fov; // Field of view
extern int mode; // Orthogonal view or projetion view
extern double asp; // Window aspect ratio
extern double dim; // Dimension of orthogonal box

extern vect camera;

extern int fp; // First person mode toggle

extern float shinyvec[1];
extern unsigned int textures[3];

extern int emission;

/* Draw the Scene */
void drawScene();

/* Shapes and Objects */
void drawMorHelmet();
void drawFinHelmet();

void drawCylinderTube(double x, double y, double z, double dx, double dy, double dz, double amount, double th);
void drawCone(double x, double y, double z, double dx, double dy, double dz, double th);
void drawHalfCone(double x, double y, double z, double dx, double dy, double dz, double th);
void Vertex(double th, double ph, int tex);
void ball(double x, double y, double z, double r, double tilt, int axis, int tex);

/* Glut Functions */
void project();
void display();
void key(unsigned char ch, int x, int y);
void special(int key, int x, int y);
void idle();
void reshape(int width, int height);

#endif
