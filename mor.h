/*
 *  Taylor Andrews
 */

#ifndef MOR_H
#define MOR_H
 
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
void drawMor(double x, double y, double z, double dx, double dy, double dz, double t);

/* Body Parts */
// Head
void drawMorHelmet(double t);
void drawMorHelmetGrate(double x, double y, double z, double dx, double dy, double dz, double amount, double th, int tex);
void drawMorNeck();
// Body
void drawMorTorso(double t);
// Hands
void drawMorLeftHand();
void drawMorRightHand(double t, double theta);
void drawMorFinger(double x, double y, double z, double dx, double dy, double dz, double th, double xtilt, double ztilt, int tex);
void drawMorLeftThumb(double x, double y, double z, double dx, double dy, double dz, double th, double xtilt, double ztilt, int tex);
void drawMorRightThumb(double x, double y, double z, double dx, double dy, double dz, double th, double xtilt, double ztilt, int tex);
// Weapon
void drawMorMace(double t);
// Arms
void drawMorRightArm();
void drawMorLeftArm();
//Legs 
void drawMorLeftLeg(double t);
void drawMorRightLeg(double t);

/* Shapes and Objects */
void drawMorCylinderTube(double x, double y, double z, double dx, double dy, double dz, double amount, double th, double xtilt, double ztilt, int tex);
void drawMorPinchedTube(double x, double y, double z, double dx, double dy, double dz, double amount, double pinch_factor, double th, int tex);
void drawMorCappedCylinder(double x, double y, double z, double dx, double dy, double dz, double amount, double th, double xtilt, double ztilt, int tex, int end); 
void drawMorCylinderCap(double x, double y, double z, double dx, double dy, double dz, double th, int tex);
void drawMorPointedCylinder(double x, double y, double z, double dx, double dy, double dz, double th, double amount, int tex, int dir);
void drawMorCone(double x, double y, double z, double dx, double dy, double dz, double th, int tex);
void morVertex(double th, double ph, int tex);
void morHalfBall(double x, double y, double z, double r, double tilt, int axis, int tex);
void morBall(double x, double y, double z, double r, double tilt, int axis, int tex);

#endif