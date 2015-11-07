/*
 *  Taylor Andrews
 */

#include "mor.h"
 
/* Global Variables */
extern int emission;
extern float shinyvec[1];
extern unsigned int textures[4];

/* Draw the Figure */
void drawMor() {
    glPushMatrix();
    glScaled(1, 1, 1);
        drawMorHelmet();
    glPopMatrix();
}

/* Draw the Larger Fighter's Helmet */
void drawMorHelmet() {
    double radius = .5;
    double height = .4;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double cone_radius = radius;
    double cone_height = .2;

    double horn_height = 1.5;
    double horn_radius = .12;
    double ball_radius = .1;

    double r = radius - horn_radius;
    double br = radius-0.05;
    double bh = .1;

    double rotation = 0;
    double tilt = -30;
    double amount = 270; 
    int axis = 1;

    int dir = 0;

    glColor3f(.2, .2, .2);

    /* Draw Main Helmet */
    glPushMatrix();
    morHalfBall(xpos, ypos+height, zpos, radius, -90, axis, 0);
    glPopMatrix();
    
    // Large cylindrical outside 
    glPushMatrix();
    glRotated(225, 0, 1, 0);
    drawMorCylinderTube(xpos, ypos, zpos, radius, height, radius, amount, 0, 0);
    glPopMatrix();

    // Facial Portion
    glPushMatrix();
    amount = 90;
    glRotated(-45, 0, 1, 0);
    drawMorCylinderTube(xpos, ypos+(2*height/3), zpos, radius, height/3, radius, amount, 0, 0);
    glPopMatrix();

    glPushMatrix();
    amount = 40;
    glRotated(-45, 0, 1, 0);
    drawMorPointedCylinder(xpos, ypos-(height/2), zpos, radius, height/2, radius, 0, amount, 0, dir);
    glPopMatrix();

    glPushMatrix();
    amount = 40;
    dir = 1;
    glRotated(-95, 0, 1, 0);
    drawMorPointedCylinder(xpos, ypos-(height/2), zpos, radius, height/2, radius, 0, amount, 0, dir);
    glPopMatrix();


    /* Draw Helmet Horns */
    rotation = 0;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height+0.2, horn_radius, 0);
    rotation = 60;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height-0.1, horn_radius, 0);
    rotation = 100;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height-0.5, horn_radius, 0);
    rotation = 140;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height-0.1, horn_radius, 0);
    rotation = 220;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height-0.1, horn_radius, 0);
    rotation = 260;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height-0.5, horn_radius, 0);
    rotation = 300;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height-0.1, horn_radius, 0);

    /* Draw Helmet Gems */
    glColor3f(1, 1, 1);
    rotation = 325;
    morHalfBall(xpos+br*Cos(90-rotation), ypos+height-bh, zpos+br*Sin(90-rotation), ball_radius, tilt, 0, 1);
    rotation = 0;
    tilt = 0;
    morHalfBall(xpos+br*Cos(90-rotation), ypos+height-bh-.05, zpos+br*Sin(90-rotation), ball_radius, tilt, 0, 1);
    rotation = 35;
    tilt = 30;
    morHalfBall(xpos+br*Cos(90-rotation), ypos+height-bh, zpos+br*Sin(90-rotation), ball_radius, tilt, 0, 1);

    /* Draw Eyes */
    glPushMatrix();
    glScaled(.7, .5, .5);
    glColor3f(.5, .1, 0);
    rotation = 325;
    tilt = 0;
    morBall(xpos+br*Cos(90-rotation), ypos+height-bh-.15, zpos+br*Sin(90-rotation)+.3, ball_radius, tilt, 0, 2);
    rotation = 35;
    morBall(xpos+br*Cos(90-rotation), ypos+height-bh-.15, zpos+br*Sin(90-rotation)+.3, ball_radius, tilt, 0, 2);
    glPopMatrix();

    /* Draw Back Plane */
    glColor3f(0, 0, 0);
    glBegin(GL_QUAD_STRIP);
        glVertex3d(xpos-radius*.79, ypos-height, zpos+.3);
        glVertex3d(xpos-radius*.79, ypos+(height/3), zpos+.3);
        glVertex3d(xpos+radius*.8, ypos-height, zpos+.3);
        glVertex3d(xpos+radius*.8, ypos+(height/3), zpos+.3);
    glEnd();

    /* Seal Helmet */
    drawMorCylinderCap(xpos, ypos, zpos, radius, ypos+height-2*height/3, radius, 0);
    drawMorCylinderCap(xpos, ypos, zpos, radius, -height, radius, 0);

}

/* Draw a cylinder at (x,y,z) scaled by dx,dy,dz and rotated by th */
void drawMorCylinderTube(double x, double y, double z, double dx, double dy, double dz, double amount, double th, int tex) 
{
    double j;

    /* Enable textures */
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    
    /* Begin Lighting */
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();

    /* Transform Cylinder */
    glTranslated(x,y,z);
    glRotated(th,0,0,1);
    glScaled(dx,dy,dz);
    
    glBindTexture(GL_TEXTURE_2D,textures[tex]);

    /* Draw the Cylinder */
    glBegin(GL_QUAD_STRIP);
    for (j = 0; j <= amount; j+=.125) 
    {
        const float tc = (3*j / (float) 360);

        double x = Cos(j);
        double y = 1;
        double z = Sin(j);

        glNormal3d(Cos(j), 0.0, Sin(j));

        glTexCoord2f(-tc, 0.0); glVertex3d(x, -y, z);
        glTexCoord2f(-tc, 1.0); glVertex3d(x, y, z);
    }
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D); 
}

/* Draw a cylinder cap at (x,y,z) scaled by dx,dy,dz and rotated by th */
void drawMorCylinderCap(double x, double y, double z, double dx, double dy, double dz, double th) 
{
    int i;

    /* Enable textures */
    //glEnable(GL_TEXTURE_2D);
    //glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    
    /* Begin Lighting */
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();

    /* Transform Cylinder */
    glTranslated(x,y,z);
    glRotated(th,0,0,1);
    glScaled(dx,dy,dz);

    if (dy > 0) {
        glNormal3d(0,1,0);
    }
    else {
        glNormal3d(0,-1,0);
    }

    //glBindTexture(GL_TEXTURE_2D,textures[tex]);

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5,0.5); 
    glVertex3d(0.0, 1, 0.0);

    for(i = 0.0; i <= 360; i+=10) {
        //glTexCoord2f(-0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
        glVertex3d(Cos(i), 1, Sin(i));
    }
    glEnd();

    glPopMatrix();
    //glDisable(GL_TEXTURE_2D); 
}


void drawMorPointedCylinder(double x, double y, double z, double dx, double dy, double dz, double th, double amount, int tex, int dir)
{
    double j;

    /* Enable textures */
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    
    /* Begin Lighting */
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();

    /* Transform Cylinder */
    glTranslated(x,y,z);
    glRotated(th,0,0,1);
    glScaled(dx,dy,dz);
    
    glBindTexture(GL_TEXTURE_2D,textures[tex]);

    /* Draw the Cylinder */
    glBegin(GL_TRIANGLE_STRIP);
    for (j = 0; j <= amount; j+=1) 
    {
        const float tc = (3*j / (float) 360);

        double x = Cos(j);
        double y = 1;
        double z = Sin(j);

        glNormal3d(Cos(j), 0.0, Sin(j));

        glTexCoord2f(-tc, 0.0); glVertex3d(x, y, z);
        if (dir) {
            glTexCoord2f(-tc, 1.0); glVertex3d(x, -y-(amount-j)/amount, z);
        }
        else {
            glTexCoord2f(-tc, 1.0); glVertex3d(x, -y-j/amount, z);
        }
    }
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D); 

}

/* Draw a cone at (x,y,z) scaled by dx,dy,dz and rotated by th */
void drawMorCone(double x, double y, double z, double dx, double dy, double dz, double th) 
{
    double i; 

    /* Enable textures */
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    /* Begin Lighting */
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();

    /* Transform Cone */
    glTranslated(x,y,z);
    glRotated(th,0,0,1);
    glScaled(dx,dy,dz);

    glBindTexture(GL_TEXTURE_2D,textures[0]);

    /* Cone */
    glBegin(GL_TRIANGLE_FAN);
 
    glNormal3d(0,1,0);  
    glTexCoord2f(1.0, 1.0); glVertex3d(0.0, 1, 0.0);

    for(i = 0.0; i <= 360; i+=10) 
    {
        const float tc = (i / (float) 360);
        glNormal3d(Cos(i), 0.0, Sin(i));
        glTexCoord2f(-tc, 0.0); glVertex3d(Cos(i), 0, Sin(i));
    }
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D); 
}

/*
 *  Draw vertex in polar coordinates with normal
 *  Adapted from ex13
 */
void morVertex(double th, double ph, int tex)
{
    double x = Sin(th)*Cos(ph);
    double y = Cos(th)*Cos(ph);
    double z = Sin(ph);

    // For a sphere at the origin, the position and normal vectors are the same
    glNormal3d(x,y,z);
    if (tex != -1) {
        glTexCoord2f(-th/360.0,-ph/360.0+0.5);
    }
    glVertex3d(x,y,z);
}

/*
 *  Draw a ball at (x,y,z) with radius (r)
 *  Adapted from ex13
 */
void morHalfBall(double x, double y, double z, double r, double tilt, int axis, int tex)
{
    int th,ph;
    //float yellow[] = {1.0,1.0,0.0,1.0};
    //float Emission[]  = {0.0,0.0,0.01*emission,1.0};

    if (tex != -1) {
        /* Enable textures */
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    }

    glPushMatrix(); // Save transformation
    glTranslated(x,y,z);// Offset, scale and rotate
    glScaled(r,r,r);
    if (axis == 0)
        glRotated(tilt, 0, 1, 0);
    else if (axis == 1)
        glRotated(tilt, 1, 0, 0);

    //glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
    //glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
    //glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

    if (tex != -1) {
        glBindTexture(GL_TEXTURE_2D,textures[tex]);
    }

    // Bands of latitude
    int inc = 1;
    for (ph=0;ph<90;ph+=inc)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=2*inc)
        {
            morVertex(th,ph, tex);
            morVertex(th,ph+inc, tex);
            //Vertex(th+inc,ph, tex, 2);
            //Vertex(th+inc,ph+inc, tex, 3);
        }
        glEnd();
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D); 
}

/*
 *  Draw a ball at (x,y,z) with radius (r)
 *  Adapted from ex13
 */
void morBall(double x, double y, double z, double r, double tilt, int axis, int tex)
{
    int th,ph;
    //float yellow[] = {1.0,1.0,0.0,1.0};
    //float Emission[]  = {0.0,0.0,0.01*emission,1.0};

    if (tex != -1) {
        /* Enable textures */
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    }

    glPushMatrix(); // Save transformation
    glTranslated(x,y,z);// Offset, scale and rotate
    glScaled(r,r,r);
    if (axis == 0)
        glRotated(tilt, 0, 1, 0);
    else if (axis == 1)
        glRotated(tilt, 1, 0, 0);
    glRotated(-90, 1, 0, 0);

    //glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
    //glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
    //glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

    if (tex != -1) {
        glBindTexture(GL_TEXTURE_2D,textures[tex]);
    }

    // Bands of latitude
    int inc = 1;
    for (ph=-90;ph<90;ph+=inc)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=2*inc)
        {
            morVertex(th,ph, tex);
            morVertex(th,ph+inc, tex);
            //Vertex(th+inc,ph, tex, 2);
            //Vertex(th+inc,ph+inc, tex, 3);
        }
        glEnd();
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D); 
}

