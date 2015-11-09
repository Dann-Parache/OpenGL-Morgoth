/*
 *  Taylor Andrews
 */

#include "fin.h"
 
/* Global Variables */
extern int emission;
extern float shinyvec[1];
extern unsigned int textures[10];

/* Draw the Figure */
void drawFin() 
{
    glPushMatrix();
    glTranslated(.5, 0, 0);
    glScaled(1, 1, 1);
        //drawFinHelmet();
        //drawFinNeck();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(1, 1, 1);
    //glRotated(180, 0, 1, 0);
        drawFinLeftHand();
    glPopMatrix();
}

/* Draw the Hand that isn't holding the sword */
void drawFinLeftHand() 
{
    double radius = .075;
    double height = .1;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double amount = 360;
    double pinch_factor = .6;

    double wrist_radius = .09;
    double finger_radius = .09;
    double finger_height = .06;
    double thumb_radius = .09;
    double thumb_height = .1;

    double xtilt;
    double ztilt;
    double tilt;

    glColor3f(1, 1, 1);

    /* Wrist */
    glPushMatrix();
    glScaled(.5, .5, .2);
        finBall(xpos, ypos+height+.04, zpos, wrist_radius, 0, 0, 3);
    glPopMatrix();

    /* Palm */
    glPushMatrix();
    glScaled(.9, .5, .3);
        drawFinPinchedTube(xpos, ypos, zpos, radius, height, radius, amount, pinch_factor, 0, 3);
        //drawFinCylinderCap(xpos, ypos, zpos, radius, ypos-height, radius, 0, -1);
    glPopMatrix();

    /* Knuckles */
    //Thumb
    glPushMatrix();
    glScaled(.3, .3, .25);
        finBall(xpos-2*radius, ypos+height*.7, zpos, thumb_radius, 0, 0, 3);
    glPopMatrix();

    //Fingers
    glPushMatrix();
    glScaled(.295, .295, .295);
        finBall(xpos-.15, ypos-height-finger_radius, zpos, finger_radius, 0, 0, 3);
    glPopMatrix();

    glPushMatrix();
    glScaled(.33, .3, .33);
        finBall(xpos-.05, ypos-height-finger_radius, zpos, finger_radius, 0, 0, 3);
    glPopMatrix();

    glPushMatrix();
    glScaled(.3, .3, .3);
        finBall(xpos+.05, ypos-height-finger_radius, zpos, finger_radius, 0, 0, 3);
    glPopMatrix();

    glPushMatrix();
    glScaled(.285, .285, .285);
        finBall(xpos+.15, ypos-height-finger_radius, zpos, finger_radius, 0, 0, 3);
    glPopMatrix();

    /* Fingers */
    glPushMatrix();
    glScaled(.3, .49, .3);
        tilt = -2.5;
        drawFinFinger(xpos-.15, ypos-height-finger_radius, zpos, finger_radius-.02, finger_height, finger_radius-.02, 0, 0, tilt, 3);
    glPopMatrix();

    // Middle (should be slightly longer)
    glPushMatrix();
    glScaled(.3, .51, .3);
        tilt = -2.5;
        drawFinFinger(xpos-.05, ypos-height-finger_radius, zpos, finger_radius-.02, finger_height, finger_radius-.02, 0, 0, tilt, 3);
    glPopMatrix();

    glPushMatrix();
    glScaled(.3, .49, .3);
        tilt = -2.5;
        drawFinFinger(xpos+.05, ypos-height-finger_radius, zpos, finger_radius-.02, finger_height, finger_radius-.02, 0, 0, tilt, 3);
    glPopMatrix();

    // Pinky (should be slightly smaller)
    glPushMatrix();
    glScaled(.2, .45, .2);
        tilt = -2.5;
        drawFinFinger(xpos+.15*.3/.2, ypos-height-finger_radius, zpos, finger_radius-.02, finger_height, finger_radius-.02, 0, 0, tilt, 3);
    glPopMatrix();


    /* Thumb */
    glPushMatrix();
    glScaled(.2, .2, .2);
    glRotated(90, 0, 0, 1);
    xtilt = 1.3;
    ztilt = 1.5;
        drawFinThumb(xpos+.01, ypos+.35, zpos-.13, thumb_radius, thumb_height, thumb_radius, 0, xtilt, ztilt, 3);
    glPopMatrix();

}

/* Draw the Hand Holding the Sword */
void drawFinRightHand()
{
    double radius = .075;
    double height = .1;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double amount = 360;
    double pinch_factor = .6;

    double wrist_radius = .09;
    double finger_radius = .09;

    glColor3f(1, 1, 1);

    /* Wrist */
    glPushMatrix();
    glScaled(.5, .5, .2);
        finBall(xpos, ypos+height+.04, zpos, wrist_radius, 0, 0, 3);
    glPopMatrix();

    /* Palm */
    glPushMatrix();
    glScaled(.9, .5, .3);
        drawFinPinchedTube(xpos, ypos, zpos, radius, height, radius, amount, pinch_factor, 0, 3);
        drawFinCylinderCap(xpos, ypos, zpos, radius, ypos-height, radius, 0, -1);
    glPopMatrix();

    /* Knuckles */
    //Thumb
    glPushMatrix();
    glScaled(.3, .3, .2);
        finBall(xpos-2*radius, ypos+height*.8, zpos, wrist_radius, 0, 0, 3);
    glPopMatrix();

    //Fingers
    glPushMatrix();
    glScaled(.3, .3, .3);
        finBall(xpos-.15, ypos-height-finger_radius, zpos, finger_radius, 0, 0, 3);
    glPopMatrix();

    glPushMatrix();
    glScaled(.3, .3, .3);
        finBall(xpos-.05, ypos-height-finger_radius, zpos, finger_radius, 0, 0, 3);
    glPopMatrix();

    glPushMatrix();
    glScaled(.3, .3, .3);
        finBall(xpos+.05, ypos-height-finger_radius, zpos, finger_radius, 0, 0, 3);
    glPopMatrix();

    glPushMatrix();
    glScaled(.3, .3, .3);
        finBall(xpos+.15, ypos-height-finger_radius, zpos, finger_radius, 0, 0, 3);
    glPopMatrix();

}

void drawFinFinger(double x, double y, double z, double dx, double dy, double dz, double th, double xtilt, double ztilt, int tex) 
{
    double radius = dx;
    double height = dy;

    double amount = 360;
    int end;

    /* First Section */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        drawFinCylinderTube(x, y, z, radius, height, radius, amount, 0, xtilt, ztilt, tex);
    glPopMatrix();

    /* Middle Joint */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        finBall(x+xtilt/10, y-height, z+ztilt/10+radius, radius+.01, 0, 0, tex);
    glPopMatrix();

    /* Second Secontion */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        end = 0;
        drawFinCappedCylinder(x+xtilt/10, y-height, z+ztilt/10-1.42*radius, radius, height/2+.01, radius, amount, 0, 0, -1*ztilt, tex, end);
    glPopMatrix();

}


void drawFinThumb(double x, double y, double z, double dx, double dy, double dz, double th, double xtilt, double ztilt, int tex) 
{
    double radius = dx;
    double height = dy;

    double amount = 360;
    int end;

    /* First Section */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        drawFinCylinderTube(x, y, z, radius, height, radius, amount, 0, xtilt, ztilt, tex);
    glPopMatrix();  

    /* Middle Joint */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        finBall(x, y+radius, z, radius+.01, 0, 0, tex);
    glPopMatrix();

    /* Second Secontion */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        end = 1;
        drawFinCappedCylinder(x+.01, y+radius*.9-.04, z+.016, radius, height/2, radius, amount, 0, -1.8, -1, tex, end);
    glPopMatrix();

}

/* Draw Fin's Neck */
void drawFinNeck() 
{
    double radius = .085;
    double height = .04;
    double xpos = 0;
    double ypos = -0.06;
    double zpos = -0.01;

    double amount = 360;
    double pinch_factor = .9;

    glColor3f(1, 1, 1);
    drawFinPinchedTube(xpos, ypos, zpos, radius, height, radius, amount, pinch_factor, 0, 4);
}

/* Draw the Smaller Fighter's Helmet */
void drawFinHelmet() 
{
    double radius = .09;
    double height = .05;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    //double r = radius - horn_radius;
    double ball_radius = .03;
    double br = radius-ball_radius;
    double bh = .01;

    double rotation = 0;
    double tilt = -30;
    double grate_pos = 0;
    double amount = 270; 
    int axis = 1;

    int dir = 0;

    glColor3f(.5, .5, .5);

    /* Draw Main Helmet */
    glPushMatrix();
        finHalfBall(xpos, ypos+height, zpos, radius, -90, axis, 3);
    glPopMatrix();
    
    // Large cylindrical outside 
    glPushMatrix();
    glRotated(225, 0, 1, 0);
        drawFinCylinderTube(xpos, ypos, zpos, radius, height, radius, amount, 0, 0, 0, 3);
    glPopMatrix();

    // Facial Portion
    glPushMatrix();
    amount = 90;
    glRotated(-45, 0, 1, 0);
        drawFinCylinderTube(xpos, ypos+(2*height/3), zpos, radius, height/3, radius, amount, 0, 0, 0, 3);
    glPopMatrix();

    glPushMatrix();
    amount = 45;
    glRotated(-45, 0, 1, 0);
        drawFinPointedCylinder(xpos, ypos-(height/2), zpos, radius, height/2, radius, 0, amount, 3, dir);
    glPopMatrix();

    glPushMatrix();
    amount = 45;
    dir = 1;
    glRotated(-90, 0, 1, 0);
        drawFinPointedCylinder(xpos, ypos-(height/2), zpos, radius, height/2, radius, 0, amount, 3, dir);
    glPopMatrix();

    // Eye grate
    glPushMatrix();
    amount = 40;
    grate_pos = ypos+((2*height/3))-(height/2);
    glRotated(-95, 0, 1, 0);
        drawFinHelmetGrate(xpos, grate_pos, zpos, radius, height/2-height/3, radius, amount, 0, 3);
	glPopMatrix();

    glPushMatrix();
    amount = 40;
    grate_pos = ypos+((2*height/3))-(height/2);
    glRotated(-50, 0, 1, 0);
        drawFinHelmetGrate(xpos, grate_pos, zpos, radius, height/2-height/3, radius, amount, 0, 3);
	glPopMatrix();

    /* Draw Back Plane */
    glColor3f(0, 0, 0);
    glBegin(GL_QUAD_STRIP);
        glVertex3d(xpos-radius*.79, ypos-height, zpos+.05);
        glVertex3d(xpos-radius*.79, ypos+(height/3), zpos+.05);
        glVertex3d(xpos+radius*.8, ypos-height, zpos+.05);
        glVertex3d(xpos+radius*.8, ypos+(height/3), zpos+.05);
    glEnd();

    /* Draw Eyes */
    glPushMatrix();
    glScaled(.4, .2, .2);
    glColor3f(0, 1, 1);
    rotation = 280;
    tilt = 0;
        finBall(xpos+br*Cos(90-rotation), ypos+height-bh, zpos+br*Sin(90-rotation)+.25, ball_radius, tilt, 0, 2);
    rotation = 80;
        finBall(xpos+br*Cos(90-rotation), ypos+height-bh, zpos+br*Sin(90-rotation)+.25, ball_radius, tilt, 0, 2);
    glPopMatrix();

    /* Seal Helmet */
    glColor3f(1, 1, 1);
    drawFinCylinderCap(xpos, ypos, zpos, radius, ypos+height-2*height/3, radius, 0, -1);
    drawFinCylinderCap(xpos, ypos, zpos, radius, ypos, radius, 0, -1);
    drawFinCylinderCap(xpos, ypos, zpos, radius, -height, radius, 0, -1);
}

/* Draw a Cylinder Tube */
void drawFinCylinderTube(double x, double y, double z, double dx, double dy, double dz, double amount, double th, double xtilt, double ztilt, int tex) 
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
    for (j = 0; j <= amount; j++) 
    {
        const float tc = (3*j / (float) 360);

        double x = Cos(j);
        double y = 1;
        double z = Sin(j);

        glNormal3d(Cos(j), 0.0, Sin(j));

        glTexCoord2f(-tc, 0.0); glVertex3d(x+xtilt, -y, z+ztilt);
        glTexCoord2f(-tc, 1.0); glVertex3d(x, y, z);
    }
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D); 
}

/* Draw a Cylinder with a Rounded Cap */
void drawFinCappedCylinder(double x, double y, double z, double dx, double dy, double dz, double amount, double th, double xtilt, double ztilt, int tex, int end) 
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
    for (j = 0; j <= amount; j++) 
    {
        const float tc = (3*j / (float) 360);

        double x1 = Cos(j);
        double y1 = 1;
        double z1 = Sin(j);

        glNormal3d(Cos(j), 0.0, Sin(j));

        glTexCoord2f(-tc, 0.0); glVertex3d(x1+xtilt, -y1, z1+ztilt);
        glTexCoord2f(-tc, 1.0); glVertex3d(x1, y1, z1);
    }
    glEnd();

    if (end)
        finHalfBall(x+xtilt, -1, z+ztilt, 1, 90, 1, tex);
    else
        finBall(x, 1, z, 1, -90, 1, tex);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D); 
}

/* Draw a cylinder cap at (x,y,z) scaled by dx,dy,dz and rotated by th */
void drawFinCylinderCap(double x, double y, double z, double dx, double dy, double dz, double th, int tex) 
{
    int i;

    /* Enable textures */
    if (tex != -1) {
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    }
    
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

    if (tex != -1)
        glBindTexture(GL_TEXTURE_2D,textures[tex]);

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5,0.5); 
    glVertex3d(0.0, 1, 0.0);

    for(i = 0.0; i <= 360; i+=10) {
        if (tex != -1)
            glTexCoord2f(-0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
        glVertex3d(Cos(i), 1, Sin(i));
    }
    glEnd();

    glPopMatrix();
    if (tex != -1)
        glDisable(GL_TEXTURE_2D); 
}

/* Pinched Tube for the hands */ 
void drawFinPinchedTube(double x, double y, double z, double dx, double dy, double dz, double amount, double pinch_factor, double th, int tex)
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
    for (j = 0; j <= amount; j++) 
    {
        const float tc = (3*j / (float) 360);

        double x = Cos(j);
        double y = 1;
        double z = Sin(j);

        glNormal3d(Cos(j), 0.0, Sin(j));

        glTexCoord2f(-tc, 0.0); glVertex3d(x, -y, z);
        //if (j < amount/2) {
            glNormal3d(Cos(j), 0.0, Sin(j));
            glTexCoord2f(-tc, 1.0); glVertex3d(x*pinch_factor, y, z*pinch_factor);
        // }
        // else {
        //     glNormal3d(Cos(j)-.1, 0.0, Sin(j)-.1);
        //     glTexCoord2f(-tc, 1.0); glVertex3d(x-.1, y, z-.1);
        // }
    }
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D); 
}

/* A Cylinder with a Pointy Tip for the Helmet */
void drawFinPointedCylinder(double x, double y, double z, double dx, double dy, double dz, double th, double amount, int tex, int dir)
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
void drawFinCone(double x, double y, double z, double dx, double dy, double dz, double th, int tex) 
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

    glBindTexture(GL_TEXTURE_2D,textures[tex]);

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

/* Draw the Helmet Grate */
void drawFinHelmetGrate(double x, double y, double z, double dx, double dy, double dz, double amount, double th, int tex) 
{    
	int j;
	int off = 1; // Keeps track of whether we are drawing or not

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
    for (j = 0; j <= amount; j+=1) 
    {
        const float tc = (3*j / (float) 360);

        if (j%5 == 0)
        	off = 1-off;

        if (off == 0) {
	        double x = Cos(j);
	        double y = 1;
	        double z = Sin(j);

	        glNormal3d(Cos(j), 0.0, Sin(j));

	        glTexCoord2f(-tc, 0.0); glVertex3d(x, -y, z);
	        glTexCoord2f(-tc, 1.0); glVertex3d(x, y, z);
	    }
	    else {
	    	glEnd();
	    	glBegin(GL_QUAD_STRIP);
	    }
    }
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D); 
    
}

/*
 *  Draw vertex in polar coordinates with normal
 *  Adapted from ex13
 */
void finVertex(double th, double ph, int tex)
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
void finHalfBall(double x, double y, double z, double r, double tilt, int axis, int tex)
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
            finVertex(th,ph, tex);
            finVertex(th,ph+inc, tex);
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
void finBall(double x, double y, double z, double r, double tilt, int axis, int tex)
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
            finVertex(th,ph, tex);
            finVertex(th,ph+inc, tex);
            //Vertex(th+inc,ph, tex, 2);
            //Vertex(th+inc,ph+inc, tex, 3);
        }
        glEnd();
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D); 
}