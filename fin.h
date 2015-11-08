/*
 *  Taylor Andrews
 */

#ifndef FIN_H
#define FIN_H
 
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

/* Global Variables */
extern int th; // Azimuth of view angle
extern int ph; // Elevation of view angle
extern int fov; // Field of view
extern int mode; // Orthogonal view or projetion view
extern double asp; // Window aspect ratio
extern double dim; // Dimension of orthogonal box

extern int fp; // First person mode toggle

extern float shinyvec[1];
extern unsigned int textures[10];

extern int emission;

/* Draw the Scene */
void drawFin();

/* Body Parts */
void drawFinHelmet();
void drawFinHelmetGrate(double x, double y, double z, double dx, double dy, double dz, double amount, double th, int tex);
void drawFinNeck();
void drawFinLeftHand();
void drawFinRightHand();

/* Shapes and Objects */
void drawFinCylinderTube(double x, double y, double z, double dx, double dy, double dz, double amount, double th, int tex);
void drawFinPinchedTube(double x, double y, double z, double dx, double dy, double dz, double amount, double pinch_factor, double th, int tex);
void drawFinCylinderCap(double x, double y, double z, double dx, double dy, double dz, double th, int tex);
void drawFinPointedCylinder(double x, double y, double z, double dx, double dy, double dz, double th, double amount, int tex, int dir);
void drawFinCone(double x, double y, double z, double dx, double dy, double dz, double th, int tex);
void finVertex(double th, double ph, int tex);
void finHalfBall(double x, double y, double z, double r, double tilt, int axis, int tex);
void finBall(double x, double y, double z, double r, double tilt, int axis, int tex);

#endif