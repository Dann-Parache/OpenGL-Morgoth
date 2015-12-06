/* 
 * File to load a bmp as a texture in opengl.
 *
 * Created by: Willem A. (Vlakkies) Schreüder 
 * Modified by: Taylor Andrews
 */

#ifndef LOADTEXBMP
#define LOADTEXBMP

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

unsigned int LoadTexBMP(const char* file);

#endif
