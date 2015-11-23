/*
 *  Taylor Andrews
 */

#include "fin.h"
 
/* Global Variables */
extern int emission;
extern float shinyvec[1];
extern unsigned int textures[10];

/* Draw the Figure */
void drawFin(double x, double y, double z, double dx, double dy, double dz, double t) 
{
    double head_scaleX = dx;
    double head_scaleY = dy;
    double head_scaleZ = dz;

    double head_posX = x;
    double head_posY = y;
    double head_posZ = z;

    double torso_posX = head_posX;
    double torso_posY = head_posY-.2*head_scaleY;
    double torso_posZ = head_posZ;

    double lefthand_posX = head_posX+.25*head_scaleX;
    double lefthand_posY = head_posY-.55*head_scaleY;
    double lefthand_posZ = head_posZ;
    double lefthand_scaleX = head_scaleX/2;
    double lefthand_scaleY = head_scaleY/2;
    double lefthand_scaleZ = head_scaleZ/2;

    double rightshoulder_posX = head_posX-.25*head_scaleX;
    double rightshoulder_posY = head_posY-.475*head_scaleY;
    double rightshoulder_posZ = head_posZ;
    double rightshoulder_scaleX = head_scaleX/2;
    double rightshoulder_scaleY = head_scaleY/2;
    double rightshoulder_scaleZ = head_scaleZ/2;

    double rleg_posX = torso_posX-.07*head_scaleX;
    double rleg_posY = torso_posY-.6*head_scaleY; 
    double rleg_posZ = torso_posZ;

    double lleg_posX = torso_posX+.07*head_scaleX; 
    double lleg_posY = torso_posY-.6*head_scaleY; 
    double lleg_posZ = torso_posZ;

    // Set up animation
    t = t < 180 ? -t : t;
    double armtheta = -t;

    // Enable anti-aliasing to smooth lines
    glEnable(GL_POLYGON_SMOOTH);
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    glEnable( GL_LINE_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Head and Neck */
    glPushMatrix();
    glTranslated(head_posX, head_posY, head_posZ);
    glScaled(head_scaleX, head_scaleY, head_scaleZ);
        drawFinHelmet();
        drawFinNeck();
    glPopMatrix();

    // Enable face culling to improve performance
    glEnable(GL_CULL_FACE);

    /* Left Hand and Arm */
    glPushMatrix();
    glTranslated(lefthand_posX, lefthand_posY, lefthand_posZ);
    glScaled(lefthand_scaleX, lefthand_scaleY, lefthand_scaleZ);
    glRotated(90, 0, 1, 0);
        drawFinLeftHand();
    glPopMatrix();

    glPushMatrix();
    glTranslated(lefthand_posX, lefthand_posY+.15*lefthand_scaleY, lefthand_posZ);
    glScaled(lefthand_scaleX, lefthand_scaleY, lefthand_scaleZ);
    glRotated(180, 0, 0, 1);
    glRotated(270, 0, 1, 0);
        drawFinLeftArm();
    glPopMatrix();

    /* Right Hand and Arm */
    glPushMatrix();
    // Arm animation
    glTranslated(rightshoulder_posX+rightshoulder_scaleX*.11, rightshoulder_posY+rightshoulder_scaleY*(.66), rightshoulder_posZ+rightshoulder_scaleZ*0);
    glRotated(-1*armtheta, 1, 0, 0);
    glTranslated(-rightshoulder_posX-rightshoulder_scaleX*.11, -rightshoulder_posY-rightshoulder_scaleY*(.66), -rightshoulder_posZ-rightshoulder_scaleZ*0);

    glPushMatrix();
    glTranslated(rightshoulder_posX, rightshoulder_posY-.14*rightshoulder_scaleY, rightshoulder_posZ);
    glScaled(rightshoulder_scaleX, rightshoulder_scaleY, rightshoulder_scaleZ);
    //glRotated(180, 0, 1, 0);
        drawFinRightHand();
    glPopMatrix();

    glPushMatrix();
    glTranslated(rightshoulder_posX, rightshoulder_posY, rightshoulder_posZ);
    glScaled(rightshoulder_scaleX, rightshoulder_scaleY, rightshoulder_scaleZ);
    glRotated(180, 0, 0, 1);
    glRotated(90, 0, 1, 0);
        drawFinRightArm();
    glPopMatrix();

    glPopMatrix(); // End arm animation transformation

    /* Body */
    glPushMatrix();
    glTranslated(torso_posX, torso_posY, torso_posZ);
    //glScaled(righthand_scaleX, righthand_scaleY, righthand_scaleZ);
    //glRotated(180, 0, 0, 1);
    //glRotated(90, 0, 1, 0);
        drawFinTorso();
    glPopMatrix();

    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
    glDisable(GL_BLEND);

    /* Legs */
    // Left Leg
    glPushMatrix();
    glTranslated(lleg_posX, lleg_posY, lleg_posZ);
        drawFinLeftLeg();
    glPopMatrix();

    // Right Leg
    glPushMatrix();
    glTranslated(rleg_posX, rleg_posY, rleg_posZ);
        drawFinRightLeg();
    glPopMatrix();

    glDisable(GL_CULL_FACE); // MOVE DOWN YA HEAR

}

/* Draw the Left Leg */
void drawFinLeftLeg()
{
    double radius = .48;
    double height = .9;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double amount = 360;
    double pinch_factor = .9;

    double knee_radius = .5;

    /* Thigh */
    glPushMatrix();
    glScaled(1, 1, 1);
    glRotated(180, 1, 0, 0);
        drawFinPinchedTube(xpos, ypos+height, zpos, radius, height, radius, amount, pinch_factor, 0, 3);
    glPopMatrix();

    /* Knee */
    glPushMatrix();
        finBall(xpos, ypos-1.8*height, zpos, knee_radius, 0, 0, 3);
    glPopMatrix();

    /* Shin */
    glPushMatrix();
        drawFinCylinderTube(xpos, ypos-2.5*height, zpos, radius*.8, .35*height, radius*.8, amount, 0, 0, 0, 3);
    glPopMatrix();

    /* Boot */
    glPushMatrix();
    glRotated(180, 1, 0, 0);
        pinch_factor = .5;
        drawFinPinchedTube(xpos, ypos+3.7*height, zpos, radius, height, radius, amount, pinch_factor, 0, 5);
        drawFinCylinderCap(xpos, ypos+3.7*height-height, zpos, radius, ypos, radius, 0, 5);
    glPopMatrix();

    // Ankle
    glPushMatrix();
        finBall(xpos, ypos-4.5*height, zpos, radius*.75, 0, 0, 5);
    glPopMatrix();

    // Heel and Toe
    glPushMatrix();
        drawFinCylinderTube(xpos, ypos-5*height, zpos, radius*.6, .25*height, radius*.6, amount, 0, 0, 0, 5);
        drawFinCylinderCap(xpos, ypos-5.25*height, zpos, radius*.6, ypos, radius*.6, 0, 5);

        drawFinCylinderTube(xpos, ypos-5*height, zpos+height, radius*.45, .25*height, radius*.45, amount, 0, 0, 0, 5);
        drawFinCylinderCap(xpos, ypos-5.25*height, zpos+height, radius*.45, ypos, radius*.45, 0, 5);
    glPopMatrix();
    
    // Foot
    glPushMatrix();
    glRotated(90, 1, 0, 0);
        radius = .25;
        drawFinCylinderTube(xpos, ypos+.5, zpos+4.9*height, radius, .5*height, radius, amount, 0, 0, 0, 5);
        finBall(xpos, ypos+.5+.5*height, zpos+4.9*height, radius, -90, 1, 5);
    glPopMatrix();
}

/* Draw the Right Leg */
void drawFinRightLeg()
{
    double radius = .48;
    double height = .9;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double amount = 360;
    double pinch_factor = .9;

    double knee_radius = .5;

    /* Thigh */
    glPushMatrix();
    glRotated(180, 1, 0, 0);
        drawFinPinchedTube(xpos, ypos+height, zpos, radius, height, radius, amount, pinch_factor, 0, 3);
    glPopMatrix();

    /* Knee */
    glPushMatrix();
        finBall(xpos, ypos-1.8*height, zpos, knee_radius, 0, 0, 3);
    glPopMatrix();

    /* Shin */
    glPushMatrix();
        drawFinCylinderTube(xpos, ypos-2.5*height, zpos, radius*.8, .35*height, radius*.8, amount, 0, 0, 0, 3);
    glPopMatrix();

    /* Boot */
    // Leg Portion
    glPushMatrix();
    glRotated(180, 1, 0, 0);
        pinch_factor = .5;
        drawFinPinchedTube(xpos, ypos+3.7*height, zpos, radius, height, radius, amount, pinch_factor, 0, 5);
        drawFinCylinderCap(xpos, ypos+3.7*height-height, zpos, radius, ypos, radius, 0, 5);
    glPopMatrix();

    // Ankle
    glPushMatrix();
        finBall(xpos, ypos-4.5*height, zpos, radius*.75, 0, 0, 5);
    glPopMatrix();

    // Heel and Toe
    glPushMatrix();
        drawFinCylinderTube(xpos, ypos-5*height, zpos, radius*.6, .25*height, radius*.6, amount, 0, 0, 0, 5);
        drawFinCylinderCap(xpos, ypos-5.25*height, zpos, radius*.6, ypos, radius*.6, 0, 5);

        drawFinCylinderTube(xpos, ypos-5*height, zpos+height, radius*.45, .25*height, radius*.45, amount, 0, 0, 0, 5);
        drawFinCylinderCap(xpos, ypos-5.25*height, zpos+height, radius*.45, ypos, radius*.45, 0, 5);
    glPopMatrix();

    // Foot
    glPushMatrix();
    glRotated(90, 1, 0, 0);
        radius = .25;
        drawFinCylinderTube(xpos, ypos+.5, zpos+4.9*height, radius, .5*height, radius, amount, 0, 0, 0, 5);
        finBall(xpos, ypos+.5+.5*height, zpos+4.9*height, radius, -90, 1, 5);
    glPopMatrix();
}

/* Draw the Torso */
void drawFinTorso() 
{
    double radius = .5;
    double height = .4;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double hip_radius = 0;

    double pinch_factor = .55;
    double amount = 360;

    int axis = 1;

    glColor3f(1, 1, 1);

    /* Shoulder Portion */
    glPushMatrix();
    glScaled(3, 1, 1.5);
    finHalfBall(xpos, ypos+height, zpos, radius, -90, axis, 3);
    glPopMatrix();

    /* Main Body */
    glPushMatrix();
    glScaled(3, 1, 1.5);
    glRotated(180, 1, 0, 0);
        hip_radius = radius-(1-pinch_factor)*radius;
        drawFinPinchedTube(xpos, ypos+1.5*height, zpos, radius, 2.5*height+.05, radius, amount, pinch_factor, 0, 3);
        drawFinCylinderTube(xpos, ypos+3.5*height, zpos, hip_radius, 1.5*height, hip_radius, amount, 0, 0, 0, 3);
    glPopMatrix();

    // The skirt is not air-tight, require face culling off
    glDisable(GL_CULL_FACE);

    /* Skirt */
    glPushMatrix();
    glScaled(3, 1, 1.5);
        pinch_factor = .6;
        hip_radius += hip_radius*pinch_factor;
        //hip_radius = hip_radius+(1-pinch_factor)*hip_radius;
        drawFinSkirt(xpos, ypos-6.5*height, zpos, hip_radius, 2*height, hip_radius, amount, pinch_factor, 0, 4);

        glColor3f(1, 1, 1);
        drawFinCylinderCap(xpos, ypos-9.5*height, zpos, hip_radius-.06, -1.5*height, hip_radius-.06, 0, -1);
    glPopMatrix();

    // Turn face culling back on
    glEnable(GL_CULL_FACE);
}

/* Draw the skirt portion of the armor */
void drawFinSkirt(double x, double y, double z, double dx, double dy, double dz, double amount, double pinch_factor, double th, int tex)
{
    int j;

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

    //glColor3f(0, .2, 0);

    /* Draw the Cylinder */
    glBegin(GL_QUAD_STRIP);
    for (j = 0; j <= (int) amount; j+=10) 
    {
        double k = j / 10;
        k = (int) k % 2 == 0 ? 1 : 0;

        const float tc = (3*j / (float) 360);

        double x = Cos(j);
        double y = 1;
        double z = Sin(j);

        glNormal3d(Cos(j), 0.0, Sin(j));

        glTexCoord2f(-tc, 0.0); glVertex3d(x, -3*y-k, z);

        glNormal3d(Cos(j), 0.0, Sin(j));
        glTexCoord2f(-tc, 1.0); glVertex3d(x*pinch_factor, y, z*pinch_factor);

    }
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D); 
}

/* Draw the Left Arm */
void drawFinLeftArm()
{
    double radius = .075;
    double height = .1;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double elbow_radius = .08;
    double shoulder_radius = .11;

    double xtilt = 0;
    double ztilt = -1;

    double amount = 360;
    double pinch_factor = .4;   
 
    /*Forearm */
    //glColor3f(.37, .15, .12);
    drawFinPinchedTube(xpos, ypos, zpos, radius, height, radius, amount, pinch_factor, 0, 5);
    drawFinCylinderCap(xpos, ypos, zpos, radius, -height, radius, 0, 5); // Makes Model Water Tight
    glColor3f(1, 1, 1);
    drawFinCylinderTube(xpos, ypos-2*height, zpos, radius*pinch_factor*1.65, height, radius*pinch_factor*1.65, amount, 0, 0, 0, 3);

    /* Elbow */
    finBall(xpos, ypos-3*height, zpos, elbow_radius, 0, 0, 3);

    /* Upper Arm */
    drawFinCylinderTube(xpos, ypos-4*height-elbow_radius, zpos, radius-.01, height*1.9, radius-.01, amount, 0, xtilt, ztilt, 3);

    /* Shoulder */
    finBall(xpos+xtilt/10, ypos-6*height-elbow_radius, zpos+ztilt/10, shoulder_radius, 0, 0, 3);

}

/* Draw the Right Arm */
// TO-DO Animate this
void drawFinRightArm()
{
    double radius = .075;
    double height = .1;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double elbow_radius = .08;
    double shoulder_radius = .11;

    double xtilt = 0;
    double ztilt = -1;

    double amount = 360;
    double pinch_factor = .4;   
 
    /*Forearm */
    //glColor3f(.37, .15, .12);
    drawFinPinchedTube(xpos, ypos, zpos, radius, height, radius, amount, pinch_factor, 0, 5);
    drawFinCylinderCap(xpos, ypos, zpos, radius, -height, radius, 0, 5); // Makes Model Water Tight
    glColor3f(1, 1, 1);
    drawFinCylinderTube(xpos, ypos-2*height, zpos, radius*pinch_factor*1.65, height, radius*pinch_factor*1.65, amount, 0, 0, 0, 3);

    /* Elbow */
    finBall(xpos, ypos-3*height, zpos, elbow_radius, 0, 0, 3);

    /* Upper Arm */
    drawFinCylinderTube(xpos, ypos-4*height-elbow_radius, zpos, radius-.01, height*1.9, radius-.01, amount, 0, xtilt, ztilt, 3);

    /* Shoulder */
    finBall(xpos+xtilt/10, ypos-6*height-elbow_radius, zpos+ztilt/10, shoulder_radius, 0, 0, 3);

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

    int tex = 5;

    //glColor3f(.37, .15, .12);

    /* Wrist */
    glPushMatrix();
    glScaled(.5, .5, .4);
        finBall(xpos, ypos+height+.04, zpos, wrist_radius, 0, 0, tex);
    glPopMatrix();

    /* Palm */
    glPushMatrix();
    glScaled(.9, .5, .3);
        drawFinPinchedTube(xpos, ypos, zpos, radius, height, radius, amount, pinch_factor, 0, tex-2);
        //drawFinCylinderCap(xpos, ypos, zpos, radius, ypos-height, radius, 0, -1);
    glPopMatrix();

    /* Knuckles */
    //Thumb
    glPushMatrix();
    glScaled(.3, .3, .25);
        finBall(xpos-2*radius, ypos+height*.7, zpos, thumb_radius, 0, 0, tex-2);
    glPopMatrix();

    //Fingers
    glPushMatrix();
    glScaled(.295, .295, .295);
        finBall(xpos-.15, ypos-height-finger_radius, zpos, finger_radius, 0, 0, tex-2);
    glPopMatrix();

    glPushMatrix();
    glScaled(.33, .3, .33);
        finBall(xpos-.05, ypos-height-finger_radius, zpos, finger_radius, 0, 0, tex-2);
    glPopMatrix();

    glPushMatrix();
    glScaled(.3, .3, .3);
        finBall(xpos+.05, ypos-height-finger_radius, zpos, finger_radius, 0, 0, tex-2);
    glPopMatrix();

    glPushMatrix();
    glScaled(.285, .285, .285);
        finBall(xpos+.15, ypos-height-finger_radius, zpos, finger_radius, 0, 0, tex-2);
    glPopMatrix();

    /* Fingers */
    glPushMatrix();
    glScaled(.3, .49, .3);
        tilt = -2.5;
        drawFinFinger(xpos-.15, ypos-height-finger_radius, zpos, finger_radius-.02, finger_height, finger_radius-.02, 0, 0, tilt, tex);
    glPopMatrix();

    // Middle (should be slightly longer)
    glPushMatrix();
    glScaled(.3, .51, .3);
        tilt = -2.5;
        drawFinFinger(xpos-.05, ypos-height-finger_radius, zpos, finger_radius-.01, finger_height, finger_radius-.01, 0, 0, tilt, tex);
    glPopMatrix();

    glPushMatrix();
    glScaled(.3, .49, .3);
        tilt = -2.5;
        drawFinFinger(xpos+.05, ypos-height-finger_radius, zpos, finger_radius-.01, finger_height, finger_radius-.01, 0, 0, tilt, tex);
    glPopMatrix();

    // Pinky (should be slightly smaller)
    glPushMatrix();
    glScaled(.2, .45, .2);
        tilt = -2.5;
        drawFinFinger(xpos+.15*.3/.2, ypos-height-finger_radius, zpos, finger_radius-.02, finger_height, finger_radius-.02, 0, 0, tilt, tex);
    glPopMatrix();

    /* Thumb */
    glPushMatrix();
    glScaled(.2, .2, .2);
    glRotated(90, 0, 0, 1);
    xtilt = 1.3;
    ztilt = 1.5;
        drawFinLeftThumb(xpos+.01, ypos+.35, zpos-.13, thumb_radius, thumb_height, thumb_radius, 0, xtilt, ztilt, tex);
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
    double finger_height = .06;
    double thumb_radius = .09;
    double thumb_height = .1;

    double xtilt;
    double ztilt;
    double tilt;

    int tex = 5;

    glColor3f(1, 1, 1);

    /* Wrist */
    glPushMatrix();
    glScaled(.5, .5, .4);
        finBall(xpos, ypos+height+.04, zpos, wrist_radius, 0, 0, tex);
    glPopMatrix();

    /* Palm */
    glPushMatrix();
    glScaled(.9, .5, .3);
        drawFinPinchedTube(xpos, ypos, zpos, radius, height, radius, amount, pinch_factor, 0, tex-2);
        //drawFinCylinderCap(xpos, ypos, zpos, radius, ypos-height, radius, 0, -1);
    glPopMatrix();

    /* Knuckles */
    //Thumb
    glPushMatrix();
    glScaled(.3, .3, .25);
        finBall(xpos+2*radius, ypos+height*.7, zpos, thumb_radius, 0, 0, tex-2);
    glPopMatrix();

    //Fingers
    glPushMatrix();
    glScaled(.285, .285, .285);
        finBall(xpos-.15, ypos-height-finger_radius, zpos, finger_radius, 0, 0, tex-2);
    glPopMatrix();

    glPushMatrix();
    glScaled(.3, .3, .3);
        finBall(xpos-.05, ypos-height-finger_radius, zpos, finger_radius, 0, 0, tex-2);
    glPopMatrix();

    glPushMatrix();
    glScaled(.33, .3, .33);
        finBall(xpos+.05, ypos-height-finger_radius, zpos, finger_radius, 0, 0, tex-2);
    glPopMatrix();

    glPushMatrix();
    glScaled(.295, .295, .295);
        finBall(xpos+.15, ypos-height-finger_radius, zpos, finger_radius, 0, 0, tex-2);
    glPopMatrix();

    /* Fingers */
    glPushMatrix();
    glScaled(.3, .49, .3);
        tilt = -2.5;
        drawFinFinger(xpos+.15, ypos-height-finger_radius, zpos, finger_radius-.02, finger_height, finger_radius-.02, 0, 0, tilt, tex);
    glPopMatrix();

    // Middle (should be slightly longer)
    glPushMatrix();
    glScaled(.3, .51, .3);
        tilt = -2.5;
        drawFinFinger(xpos+.05, ypos-height-finger_radius, zpos, finger_radius-.01, finger_height, finger_radius-.01, 0, 0, tilt, tex);
    glPopMatrix();

    glPushMatrix();
    glScaled(.3, .49, .3);
        tilt = -2.5;
        drawFinFinger(xpos-.05, ypos-height-finger_radius, zpos, finger_radius-.01, finger_height, finger_radius-.01, 0, 0, tilt, tex);
    glPopMatrix();

    // Pinky (should be slightly smaller)
    glPushMatrix();
    glScaled(.2, .45, .2);
        tilt = -2.5;
        drawFinFinger(xpos-.15*.3/.2, ypos-height-finger_radius, zpos, finger_radius-.02, finger_height, finger_radius-.02, 0, 0, tilt, tex);
    glPopMatrix();

    /* Thumb */
    glPushMatrix();
    glScaled(.2, .2, .2);
    glRotated(90, 0, 0, 1);
    glRotated(180, 1, 0, 0);
    xtilt = 1.3;
    ztilt = 1.5;
        drawFinRightThumb(xpos+.01, ypos+.35, zpos+.13, thumb_radius, thumb_height, thumb_radius, 0, xtilt, ztilt, tex);
    glPopMatrix();
}

/* Convinience Function to Draw a Finger */
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

/* Left Thumb for the Relaxed Hand */
void drawFinLeftThumb(double x, double y, double z, double dx, double dy, double dz, double th, double xtilt, double ztilt, int tex) 
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

/* Thumb for the Hand with the Sword */
void drawFinRightThumb(double x, double y, double z, double dx, double dy, double dz, double th, double xtilt, double ztilt, int tex)
{
    double radius = dx;
    double height = dy;

    double amount = 360;
    int end;

    /* First Section */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        drawFinCylinderTube(x, y, z, radius, height, radius, amount, 0, xtilt, -1*ztilt, tex);
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
        drawFinCappedCylinder(x+.01, y+radius*.9-.04, z+.016, radius, height/2, radius, amount, 0, -1.8, 1.8, tex, end);
    glPopMatrix();
}

/* Draw Fin's Neck */
void drawFinNeck() 
{
    double radius = .065;
    double height = .04;
    double xpos = 0;
    double ypos = -0.06;
    double zpos = -0.01;

    double amount = 360;
    double pinch_factor = .9;

    glColor3f(1, 1, 1);
    drawFinPinchedTube(xpos, ypos-.01, zpos, radius, height, radius, amount, pinch_factor, 0, 4);
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

    glColor3f(1, 1, 1);

    /* Draw Main Helmet */
    glPushMatrix();
        finHalfBall(xpos, ypos+height-.01, zpos, radius, -90, axis, 3);
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
    glColor3f(.91, .78, .51);
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
    glColor3f(.91, .78, .51);
    drawFinCylinderCap(xpos, ypos, zpos, radius-.001, ypos+height-2*height/3, radius-.001, 0, -1);
    drawFinCylinderCap(xpos, ypos, zpos, radius-.001, ypos, radius-.001, 0, -1);
    glColor3f(1, 1, 1);
    drawFinCylinderCap(xpos, ypos, zpos, radius, -height, radius, 0, 3);
}

/* Draw a Cylinder Tube */
void drawFinCylinderTube(double x, double y, double z, double dx, double dy, double dz, double amount, double th, double xtilt, double ztilt, int tex) 
{
    int j;

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
    for (j = 0; j <= (int) amount; j+=10) 
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
    int j;

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
    for (j = 0; j <= (int) amount; j+=10) 
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
        finBall(x, 1, z, 1.35, -90, 1, tex);

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

    for(i = 0; i <= 360; i+=10) {
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
    int j;

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
    for (j = 0; j <= (int) amount; j+=10) 
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
    int j;

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
    for (j = 0; j <= (int) amount; j+=5) 
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
    int i; 

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

    for(i = 0; i <= 360; i+=10) 
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
    for (j = 0; j <= (int) amount; j+=1) 
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
    int inc = 10;
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
    int inc = 10;
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