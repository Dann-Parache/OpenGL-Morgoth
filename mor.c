/*
 *  Taylor Andrews
 */

#include "mor.h"
 
/* Global Variables */
// extern int emission;
// extern float shinyvec[1];
// extern unsigned int textures[10];

/* Draw the Figure */
void drawMor(double x, double y, double z, double dx, double dy, double dz, double t) 
{
    double head_scaleX = dx;
    double head_scaleY = dy;
    double head_scaleZ = dz;

    double head_posX = x;
    double head_posY = y;
    double head_posZ = z;

    double torso_posX = head_posX;
    double torso_posY = head_posY-1.5*head_scaleY;
    double torso_posZ = head_posZ;

    double lefthand_posX = head_posX+2*head_scaleX;
    double lefthand_posY = head_posY-4.5*head_scaleY;
    double lefthand_posZ = head_posZ+0*head_scaleZ;
    double lefthand_scaleX = head_scaleX*4;
    double lefthand_scaleY = head_scaleY*4;
    double lefthand_scaleZ = head_scaleZ*4;

    double righthand_posX = head_posX-2*head_scaleX;
    double righthand_posY = head_posY-4.5*head_scaleY;
    double righthand_posZ = head_posZ+0*head_scaleZ;
    double righthand_scaleX = head_scaleX*4;
    double righthand_scaleY = head_scaleY*4;
    double righthand_scaleZ = head_scaleZ*4;

    double rleg_posX = torso_posX-.5*head_scaleX;
    double rleg_posY = torso_posY-3*head_scaleY; 
    double rleg_posZ = torso_posZ;

    double lleg_posX = torso_posX+.5*head_scaleX; 
    double lleg_posY = torso_posY-3*head_scaleY; 
    double lleg_posZ = torso_posZ;

    double armtheta = t;
    double leftarmtheta;
    double legtheta = t;
    double torsotheta = t;

    torsotheta /= 10;
    torsotheta = torsotheta > 18 ? 36 - torsotheta : torsotheta;

    // Set up animation
    armtheta = 180 - armtheta;
    armtheta = armtheta > 0 ? -armtheta : armtheta;

    if (armtheta > -60) {
        armtheta = -60;
        torsotheta = 12; // Restrict the torso movement when the arm is in place
    }

    leftarmtheta = armtheta;
    leftarmtheta /= 100;

    /* Body Animation Block */
    glPushMatrix();
    glTranslated(-.5*head_posX, head_posY, head_posZ);
    glRotated(torsotheta, 0, 1, 0);
    glTranslated(.5*head_posX, -head_posY, -head_posZ);

        /* Head and Neck */
        glPushMatrix();
        glTranslated(head_posX, head_posY, head_posZ);
        glScaled(head_scaleX+.1, head_scaleY+.1, head_scaleZ+.1);
            drawMorHelmet(t);
            drawMorNeck();
        glPopMatrix();

        // Enable face culling to improve performance
        glEnable(GL_CULL_FACE);

        /* Left Hand and Arm */
        glPushMatrix();
        // Arm animation
        glTranslated(lefthand_posX-.5, lefthand_posY+6.5, lefthand_posZ);
        glRotated(-leftarmtheta, 0, 0, 1);
        glTranslated(-lefthand_posX+.5, -lefthand_posY-6.5, -lefthand_posZ);

            // Left Hand
            glPushMatrix();
            glTranslated(lefthand_posX, lefthand_posY, lefthand_posZ);
            glScaled(lefthand_scaleX, lefthand_scaleY, lefthand_scaleZ);
            glRotated(90, 0, 1, 0);
                drawMorLeftHand();
            glPopMatrix();

            // Left Arm
            glPushMatrix();
            glTranslated(lefthand_posX, lefthand_posY+.15*lefthand_scaleY, lefthand_posZ);
            glScaled(lefthand_scaleX, lefthand_scaleY, lefthand_scaleZ);
            glRotated(180, 0, 0, 1);
            glRotated(270, 0, 1, 0);
                drawMorLeftArm();
            glPopMatrix();

        glPopMatrix(); // End arm animation transformation

        /* Right Hand and Arm */
        glPushMatrix();
        // Arm animation
        glTranslated(righthand_posX+righthand_scaleX*.11, righthand_posY+righthand_scaleY*(.82), righthand_posZ+righthand_scaleZ*0);
        glRotated(armtheta, 1, 0, 0);
        glTranslated(-righthand_posX-righthand_scaleX*.11, -righthand_posY-righthand_scaleY*(.82), -righthand_posZ-righthand_scaleZ*0);

            // Right Hand
            glPushMatrix();
            glTranslated(righthand_posX, righthand_posY, righthand_posZ);
            glScaled(righthand_scaleX, righthand_scaleY, righthand_scaleZ);
            glRotated(270, 0, 1, 0);
                drawMorRightHand(t, armtheta);
            glPopMatrix();

            // Right Arm
            glPushMatrix();
            glTranslated(righthand_posX, righthand_posY+.15*righthand_scaleY, righthand_posZ);
            glScaled(righthand_scaleX, righthand_scaleY, righthand_scaleZ);
            glRotated(180, 0, 0, 1);
            glRotated(90, 0, 1, 0);
                drawMorRightArm();
            glPopMatrix();

        glPopMatrix(); // End arm animation transformation

        glDisable(GL_CULL_FACE);

        /* Body */
        glPushMatrix();
        glTranslated(torso_posX, torso_posY, torso_posZ);
        //glScaled(righthand_scaleX, righthand_scaleY, righthand_scaleZ);
        //glRotated(180, 0, 0, 1);
        //glRotated(90, 0, 1, 0);
            drawMorTorso(torsotheta);
        glPopMatrix();

    /* Legs */
    legtheta /= 10;
    legtheta = legtheta > 18 ? 36 - legtheta : legtheta;

    // Left Leg
    glPushMatrix();
    glScaled(1, 1.25, .85);
    glTranslated(lleg_posX, lleg_posY, lleg_posZ);
    glRotated(legtheta, 0, 1, 0);
        drawMorLeftLeg(t);
    glPopMatrix();

    // Right Leg
    glPushMatrix();
    glScaled(1, 1.25, .85);
    glTranslated(rleg_posX, rleg_posY, rleg_posZ);
    glRotated(-10, 0, 1, 0);
        drawMorRightLeg(t);
    glPopMatrix();

    glPopMatrix(); // End body animation block
}

/* Draw the Mace */
void drawMorMace(double t) 
{
    double radius = .2;
    double height = 4;
    double xpos = 0;
    double ypos = -2.5;
    double zpos = 0;

    double amount = 360;

    drawMorCylinderTube(xpos, ypos, zpos, radius, height, radius, amount, 0, 0, 0, 0);
    drawMorCylinderCap(xpos, ypos+height, zpos, radius, ypos, radius, 0, 0);

    glPushMatrix();
    glScaled(1.5, 3, 1);
    radius = .5;
        morBall(xpos, (ypos-height)/3, zpos, radius, 0, 0, 0);
    glPopMatrix();
}

/* Draw the Left Leg */
void drawMorLeftLeg(double t)
{
    double radius = .48;
    double height = .9;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double amount = 360;
    double pinch_factor = .9;

    double knee_radius = .5;

    // Animation
    // t /= 10;
    // t = t > 18 ? 36 - t : t;

    glPushMatrix();
    // glTranslated(3.3*height, -1.75*height, 0);
    // glRotated(t, 1, 0, 0);
    // glTranslated(-3.3*height, 1.75*height, 0);

    /* Thigh */
    glPushMatrix();
    glScaled(1, 1, 1);
    glRotated(180, 1, 0, 0);
        drawMorPinchedTube(xpos, ypos+height, zpos, radius, height, radius, amount, pinch_factor, 0, 0);
    glPopMatrix();

    /* Knee */
    glPushMatrix();
        morBall(xpos, ypos-1.8*height, zpos, knee_radius, 0, 0, 0);
    glPopMatrix();

    /* Shin */
    glPushMatrix();
        drawMorCylinderTube(xpos, ypos-2.5*height, zpos, radius*.8, .35*height, radius*.8, amount, 0, 0, 0, 0);
    glPopMatrix();

    /* Boot */
    glPushMatrix();
    glRotated(180, 1, 0, 0);
        pinch_factor = .5;
        drawMorPinchedTube(xpos, ypos+3.7*height, zpos, radius, height, radius, amount, pinch_factor, 0, 5);
        drawMorCylinderCap(xpos, ypos+3.7*height-height, zpos, radius, ypos, radius, 0, 5);
    glPopMatrix();

    // Ankle
    glPushMatrix();
        morBall(xpos, ypos-4.5*height, zpos, radius*.75, 0, 0, 5);
    glPopMatrix();

    // Heel and Toe
    glPushMatrix();
        drawMorCylinderTube(xpos, ypos-5*height, zpos, radius*.6, .25*height, radius*.6, amount, 0, 0, 0, 5);
        drawMorCylinderCap(xpos, ypos-5.25*height, zpos, radius*.6, ypos, radius*.6, 0, 5);

        drawMorCylinderTube(xpos, ypos-5*height, zpos+height*1.15, radius*.4, .25*height, radius*.4, amount, 0, 0, 0, 5);
        drawMorCylinderCap(xpos, ypos-5.25*height, zpos+height*1.15, radius*.4, ypos, radius*.4, 0, 5);
    glPopMatrix();
    
    // Foot
    glPushMatrix();
    glRotated(90, 1, 0, 0);
        radius = .25;
        pinch_factor = .8;
        //drawFinCylinderTube(xpos, ypos+.5, zpos+4.9*height, radius, .5*height, radius, amount, 0, 0, 0, 5);
        glPushMatrix();
        glRotated(180, 0, 0, 1);
            drawMorPinchedTube(xpos, ypos-.35, zpos+4.9*height, radius, .5*height, radius, amount, pinch_factor, 0, 5);
        glPopMatrix();
        drawMorPinchedTube(xpos, ypos+.9, zpos+4.9*height, radius, .12*height, radius, amount, pinch_factor, 0, 5);
        morBall(xpos, ypos+.6+.5*height, zpos+4.9*height, radius, -90, 1, 5);
    glPopMatrix();

    glPopMatrix(); // End animation
}

/* Draw the Right Leg */
void drawMorRightLeg(double t)
{
    double radius = .48;
    double height = .9;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double amount = 360;
    double pinch_factor = .9;

    double knee_radius = .5;

    double rot = t;

    // Animation
    rot /= 80;
    rot = rot > 2.25 ? 4.5 - rot : rot;

    glPushMatrix();
    glTranslated(-3.3*height, .4*height, knee_radius);
    glRotated(rot, 1, 0, 0);
    glTranslated(3.3*height, -.4*height, -knee_radius);

    /* Thigh */
    glPushMatrix();
    glRotated(180, 1, 0, 0);
        drawMorPinchedTube(xpos, ypos+height, zpos, radius, height, radius, amount, pinch_factor, 0, 0);
    glPopMatrix();

    /* Knee */
    glPushMatrix();
        morBall(xpos, ypos-1.8*height, zpos, knee_radius, 0, 0, 0);
    glPopMatrix();

    /* Shin */
    glPushMatrix();
        drawMorCylinderTube(xpos, ypos-2.5*height, zpos, radius*.8, .35*height, radius*.8, amount, 0, 0, 0, 0);
    glPopMatrix();

    /* Boot */
    // Leg Portion
    glPushMatrix();
    glRotated(180, 1, 0, 0);
        pinch_factor = .5;
        drawMorPinchedTube(xpos, ypos+3.7*height, zpos, radius, height, radius, amount, pinch_factor, 0, 5);
        drawMorCylinderCap(xpos, ypos+3.7*height-height, zpos, radius, ypos, radius, 0, 5);
    glPopMatrix();

    // Ankle
    glPushMatrix();
        morBall(xpos, ypos-4.5*height, zpos, radius*.75, 0, 0, 5);
    glPopMatrix();

    // Heel and Toe
    glPushMatrix();
        drawMorCylinderTube(xpos, ypos-5*height, zpos, radius*.6, .25*height, radius*.6, amount, 0, 0, 0, 5);
        drawMorCylinderCap(xpos, ypos-5.25*height, zpos, radius*.6, ypos, radius*.6, 0, 5);

        drawMorCylinderTube(xpos, ypos-5*height, zpos+height*1.15, radius*.4, .25*height, radius*.4, amount, 0, 0, 0, 5);
        drawMorCylinderCap(xpos, ypos-5.25*height, zpos+height*1.15, radius*.4, ypos, radius*.4, 0, 5);
    glPopMatrix();

    // Foot
    glPushMatrix();
    glRotated(90, 1, 0, 0);
        radius = .25;
        pinch_factor = .8;
        //drawFinCylinderTube(xpos, ypos+.5, zpos+4.9*height, radius, .5*height, radius, amount, 0, 0, 0, 5);
        glPushMatrix();
        glRotated(180, 0, 0, 1);
            drawMorPinchedTube(xpos, ypos-.35, zpos+4.9*height, radius, .5*height, radius, amount, pinch_factor, 0, 5);
        glPopMatrix();
        drawMorPinchedTube(xpos, ypos+.9, zpos+4.9*height, radius, .12*height, radius, amount, pinch_factor, 0, 5);
        morBall(xpos, ypos+.6+.5*height, zpos+4.9*height, radius, -90, 1, 5);
    glPopMatrix();

    glPopMatrix(); // End Animation
}

/* Draw the Torso */
void drawMorTorso(double t) 
{
    double radius = .52;
    double height = .4;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double pinch_factor = .53;
    double amount = 360;

    int axis = 1;

    glColor3f(.35, .35, .35);

    /* Shoulder Portion */
    glPushMatrix();
    glScaled(3, 1, 1.5);
    morHalfBall(xpos, ypos+height, zpos, radius, -90, axis, 0);
    glPopMatrix();

    /* Main Body */
    glPushMatrix();
    glScaled(3, 1, 1.5);
    glRotated(180, 1, 0, 0);
        drawMorPinchedTube(xpos, ypos+1.9*height, zpos, radius, 3*height, radius, amount, pinch_factor, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glScaled(3, 1, 1.5);
        radius = radius-(1-pinch_factor)*radius;
        pinch_factor = .8;
        radius += radius *.25;//* (1-pinch_factor);
        drawMorPinchedTube(xpos, ypos-6*height, zpos, radius, 2*height, radius, amount, -1*pinch_factor, 0, 0);
    glPopMatrix();

    /* Chain Mail */
    glPushMatrix();
    glScaled(3, 1, 1.5);
        radius = radius-(1-pinch_factor)*radius;
        pinch_factor = .9;
        radius += radius *.3;

        glColor3f(.7, .7, .7); // Lighten things for the chainmail
        drawMorPinchedTube(xpos, ypos-9*height, zpos, radius, 2*height, radius, amount, -1*pinch_factor, 0, 7);
        
        glColor3f(0, 0, 0);
        drawMorCylinderCap(xpos, ypos-9.5*height, zpos, radius, -1.5*height, radius, 0, -1);
    glPopMatrix();

    glColor3f(.35, .35, .35); // Reset color
}

/* Draw the Left Arm */
void drawMorLeftArm()
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
    glColor3f(.5, .5, .5);
    drawMorPinchedTube(xpos, ypos, zpos, radius, height, radius, amount, pinch_factor, 0, 5);
    drawMorCylinderCap(xpos, ypos, zpos, radius, -height, radius, 0, 5); // Makes Model Water Tight
    glColor3f(.35, .35, .35);
    drawMorCylinderTube(xpos, ypos-2*height, zpos, radius*pinch_factor*1.65, height, radius*pinch_factor*1.65, amount, 0, 0, 0, 0);

    /* Elbow */
    morBall(xpos, ypos-3*height, zpos, elbow_radius, 0, 0, 0);

    /* Upper Arm */
    drawMorCylinderTube(xpos, ypos-4*height-elbow_radius, zpos, radius-.01, height*1.9, radius-.01, amount, 0, xtilt, ztilt, 0);

    /* Shoulder */
    morBall(xpos+xtilt/10, ypos-6*height-elbow_radius, zpos+ztilt/10, shoulder_radius, 0, 0, 0);

}

/* Draw the Right Arm */
void drawMorRightArm()
{
    double radius = .075;
    double height = .1;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double elbow_radius = .08;
    double shoulder_radius = .12;

    double xtilt = 0;
    double ztilt = -1;

    double amount = 360;
    double pinch_factor = .4;   
 
    /*Forearm */
    glColor3f(.5, .5, .5);
    drawMorPinchedTube(xpos, ypos, zpos, radius, height, radius, amount, pinch_factor, 0, 5);
    drawMorCylinderCap(xpos, ypos, zpos, radius, -height, radius, 0, 5); // Makes Model Water Tight
    glColor3f(.35, .35, .35);
    drawMorCylinderTube(xpos, ypos-2*height, zpos, radius*pinch_factor*1.65, height, radius*pinch_factor*1.65, amount, 0, 0, 0, 0);

    /* Elbow */
    morBall(xpos, ypos-3*height, zpos, elbow_radius, 0, 0, 0);

    /* Upper Arm */
    drawMorCylinderTube(xpos, ypos-4*height-elbow_radius, zpos, radius-.01, height*1.9, radius-.01, amount, 0, xtilt, ztilt, 0);

    /* Shoulder */
    morBall(xpos+xtilt/10, ypos-6*height-elbow_radius, zpos+ztilt/10, shoulder_radius, 0, 0, 0);

}

/* Draw the Hand that isn't holding the sword */
void drawMorLeftHand() 
{
    double radius = .075;
    double height = .1;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double amount = 360;
    double pinch_factor = .6;

    double wrist_radius = .09;
    double Finger_radius = .09;
    double Finger_height = .06;
    double thumb_radius = .09;
    double thumb_height = .1;

    double xtilt;
    double ztilt;
    double tilt;

    int tex = 5;

    glColor3f(.5, .5, .5);

    /* Wrist */
    glPushMatrix();
    glScaled(.5, .5, .4);
        morBall(xpos, ypos+height+.04, zpos, wrist_radius, 0, 0, tex);
    glPopMatrix();

    glColor3f(.35, .35, .35);

    /* Palm */
    glPushMatrix();
    glScaled(.9, .5, .3);
        drawMorPinchedTube(xpos, ypos, zpos, radius, height, radius, amount, pinch_factor, 0, 0);
        //drawMorCylinderCap(xpos, ypos, zpos, radius, ypos-height, radius, 0, -1);
    glPopMatrix();

    /* Knuckles */
    //Thumb
    glPushMatrix();
    glScaled(.3, .3, .25);
        morBall(xpos-2*radius, ypos+height*.7, zpos, thumb_radius, 0, 0, 0);
    glPopMatrix();

    //Fingers
    glPushMatrix();
    glScaled(.295, .295, .295);
        morBall(xpos-.15, ypos-height-Finger_radius, zpos, Finger_radius, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glScaled(.33, .3, .33);
        morBall(xpos-.05, ypos-height-Finger_radius, zpos, Finger_radius, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glScaled(.3, .3, .3);
        morBall(xpos+.05, ypos-height-Finger_radius, zpos, Finger_radius, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glScaled(.285, .285, .285);
        morBall(xpos+.15, ypos-height-Finger_radius, zpos, Finger_radius, 0, 0, 0);
    glPopMatrix();

    glColor3f(.5, .5, .5);
    /* Fingers */
    glPushMatrix();
    glScaled(.3, .49, .3);
        tilt = -2.5;
        drawMorFinger(xpos-.15, ypos-height-Finger_radius, zpos, Finger_radius-.02, Finger_height, Finger_radius-.02, 0, 0, tilt, tex);
    glPopMatrix();

    // Middle (should be slightly longer)
    glPushMatrix();
    glScaled(.3, .51, .3);
        tilt = -2.5;
        drawMorFinger(xpos-.05, ypos-height-Finger_radius, zpos, Finger_radius-.01, Finger_height, Finger_radius-.01, 0, 0, tilt, tex);
    glPopMatrix();

    glPushMatrix();
    glScaled(.3, .49, .3);
        tilt = -2.5;
        drawMorFinger(xpos+.05, ypos-height-Finger_radius, zpos, Finger_radius-.01, Finger_height, Finger_radius-.01, 0, 0, tilt, tex);
    glPopMatrix();

    // Pinky (should be slightly smaller)
    glPushMatrix();
    glScaled(.2, .45, .2);
        tilt = -2.5;
        drawMorFinger(xpos+.15*.3/.2, ypos-height-Finger_radius, zpos, Finger_radius-.02, Finger_height, Finger_radius-.02, 0, 0, tilt, tex);
    glPopMatrix();

    /* Thumb */
    glPushMatrix();
    glScaled(.2, .2, .2);
    glRotated(90, 0, 0, 1);
    xtilt = 1.3;
    ztilt = 1.5;
        drawMorLeftThumb(xpos+.01, ypos+.35, zpos-.13, thumb_radius, thumb_height, thumb_radius, 0, xtilt, ztilt, tex);
    glPopMatrix();
}

/* Draw the Hand Holding the Sword */
void drawMorRightHand(double t, double theta)
{
    double radius = .075;
    double height = .1;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

    double amount = 360;
    double pinch_factor = .6;

    double wrist_radius = .09;
    double Finger_radius = .09;
    double Finger_height = .06;
    double thumb_radius = .09;
    double thumb_height = .1;

    double xtilt;
    double ztilt;
    double tilt;

    double rot = 0;

    int tex = 5;

    glColor3f(.5, .5, .5);

    //Animation
    if (theta >= -60) {
        rot = t;
        rot -= 120;

        rot /= 5;

        rot = rot > 12 ? 24 - rot : rot;
    }

    glPushMatrix();
    glRotated(-rot, 0, 0, 1);

        /* Wrist */
        glPushMatrix();
        glScaled(.5, .5, .4);
            morBall(xpos, ypos+height+.04, zpos, wrist_radius, 0, 0, tex);
        glPopMatrix();

        glColor3f(.35, .35, .35);

        /* Palm */
        glPushMatrix();
        glScaled(.9, .5, .3);
            drawMorPinchedTube(xpos, ypos, zpos, radius, height, radius, amount, pinch_factor, 0, 0);
            //drawMorCylinderCap(xpos, ypos, zpos, radius, ypos-height, radius, 0, -1);
        glPopMatrix();

        /* Knuckles */
        //Thumb
        glPushMatrix();
        glScaled(.3, .3, .25);
            morBall(xpos+2*radius, ypos+height*.7, zpos, thumb_radius, 0, 0, 0);
        glPopMatrix();

        //Fingers
        glPushMatrix();
        glScaled(.285, .285, .285);
            morBall(xpos-.15, ypos-height-Finger_radius, zpos, Finger_radius, 0, 0, 0);
        glPopMatrix();

        glPushMatrix();
        glScaled(.3, .3, .3);
            morBall(xpos-.05, ypos-height-Finger_radius, zpos, Finger_radius, 0, 0, 0);
        glPopMatrix();

        glPushMatrix();
        glScaled(.33, .3, .33);
            morBall(xpos+.05, ypos-height-Finger_radius, zpos, Finger_radius, 0, 0, 0);
        glPopMatrix();

        glPushMatrix();
        glScaled(.295, .295, .295);
            morBall(xpos+.15, ypos-height-Finger_radius, zpos, Finger_radius, 0, 0, 0);
        glPopMatrix();

        glColor3f(.5, .5, .5);

        /* Fingers */
        glPushMatrix();
        glScaled(.3, .49, .3);
            tilt = -2.5;
            drawMorFinger(xpos+.15, ypos-height-Finger_radius, zpos, Finger_radius-.02, Finger_height, Finger_radius-.02, 0, 0, tilt, tex);
        glPopMatrix();

        // Middle (should be slightly longer)
        glPushMatrix();
        glScaled(.3, .51, .3);
            tilt = -2.5;
            drawMorFinger(xpos+.05, ypos-height-Finger_radius, zpos, Finger_radius-.01, Finger_height, Finger_radius-.01, 0, 0, tilt, tex);
        glPopMatrix();

        glPushMatrix();
        glScaled(.3, .49, .3);
            tilt = -2.5;
            drawMorFinger(xpos-.05, ypos-height-Finger_radius, zpos, Finger_radius-.01, Finger_height, Finger_radius-.01, 0, 0, tilt, tex);
        glPopMatrix();

        // Pinky (should be slightly smaller)
        glPushMatrix();
        glScaled(.2, .45, .2);
            tilt = -2.5;
            drawMorFinger(xpos-.15*.3/.2, ypos-height-Finger_radius, zpos, Finger_radius-.02, Finger_height, Finger_radius-.02, 0, 0, tilt, tex);
        glPopMatrix();

        /* Thumb */
        glPushMatrix();
        glScaled(.2, .2, .2);
        glRotated(90, 0, 0, 1);
        glRotated(180, 1, 0, 0);
        xtilt = 1.3;
        ztilt = 1.5;
            drawMorRightThumb(xpos+.01, ypos+.35, zpos+.13, thumb_radius, thumb_height, thumb_radius, 0, xtilt, ztilt, tex);
        glPopMatrix();

        glDisable(GL_CULL_FACE);

        glPushMatrix();
        glScaled(.2, .2, .2);
        glRotated(90, 0, 0, 1);
        glTranslated(xpos-.4, ypos, zpos-.3);
            drawMorMace(t);
        glPopMatrix();

        glEnable(GL_CULL_FACE);

    glPopMatrix(); // End Animation
}

/* Convinience Function to Draw a Finger */
void drawMorFinger(double x, double y, double z, double dx, double dy, double dz, double th, double xtilt, double ztilt, int tex) 
{
    double radius = dx;
    double height = dy;

    double amount = 360;
    int end;

    /* First Section */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        drawMorCylinderTube(x, y, z, radius, height, radius, amount, 0, xtilt, ztilt, tex);
    glPopMatrix();

    /* Middle Joint */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        morBall(x+xtilt/10, y-height, z+ztilt/10+radius, radius+.01, 0, 0, tex);
    glPopMatrix();

    /* Second Secontion */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        end = 0;
        drawMorCappedCylinder(x+xtilt/10, y-height, z+ztilt/10-1.42*radius, radius, height/2+.01, radius, amount, 0, 0, -1*ztilt, tex, end);
    glPopMatrix();

}

/* Left Thumb for the Relaxed Hand */
void drawMorLeftThumb(double x, double y, double z, double dx, double dy, double dz, double th, double xtilt, double ztilt, int tex) 
{
    double radius = dx;
    double height = dy;

    double amount = 360;
    int end;

    /* First Section */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        drawMorCylinderTube(x, y, z, radius, height, radius, amount, 0, xtilt, ztilt, tex);
    glPopMatrix();  

    /* Middle Joint */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        morBall(x, y+radius, z, radius+.01, 0, 0, tex);
    glPopMatrix();

    /* Second Secontion */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        end = 1;
        drawMorCappedCylinder(x+.01, y+radius*.9-.04, z+.016, radius, height/2, radius, amount, 0, -1.8, -1, tex, end);
    glPopMatrix();

}

/* Thumb for the Hand with the Sword */
void drawMorRightThumb(double x, double y, double z, double dx, double dy, double dz, double th, double xtilt, double ztilt, int tex)
{
    double radius = dx;
    double height = dy;

    double amount = 360;
    int end;

    /* First Section */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        drawMorCylinderTube(x, y, z, radius, height, radius, amount, 0, xtilt, -1*ztilt, tex);
    glPopMatrix();  

    /* Middle Joint */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        morBall(x, y+radius, z, radius+.01, 0, 0, tex);
    glPopMatrix();

    /* Second Secontion */
    glPushMatrix();
    //glScaled(dx, dy, dz);
        end = 1;
        drawMorCappedCylinder(x+.01, y+radius*.9-.04, z+.016, radius, height/2, radius, amount, 0, -1.8, 1.8, tex, end);
    glPopMatrix();
}

/* Draw Mor's Neck */
void drawMorNeck() 
{
    double radius = .4;
    double height = .25;
    double xpos = 0;
    double ypos = -0.5;
    double zpos = -0.1;

    double amount = 360;
    double pinch_factor = .9;

    glColor3f(0.5, 0.5, 0.5);
    drawMorPinchedTube(xpos, ypos, zpos, radius, height, radius, amount, pinch_factor, 0, 7);

    glColor3f(.35, .35, .35); // Reset color back to standard
}

/* Draw the Smaller Fighter's Helmet */
void drawMorHelmet(double t) 
{
    double radius = .5;
    double height = .4;
    double xpos = 0;
    double ypos = 0;
    double zpos = 0;

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

    glColor3f(.35, .35, .35);

    // Set up animation time
    t /= 28;
    t = (int) t % 14;
    t = t > 7 ? 14 - t : t;

    /* Head Animation*/
    glPushMatrix();
    glRotated(t, 1, 0, 0);

    /* Draw Main Helmet */
    glPushMatrix();
    morHalfBall(xpos, ypos+height-.05, zpos, radius, -90, axis, 6);
    glPopMatrix();
    
    // Large cylindrical outside 
    glPushMatrix();
    glRotated(225, 0, 1, 0);
    drawMorCylinderTube(xpos, ypos, zpos, radius, height, radius, amount, 0, 0, 0, 6);
    glPopMatrix();

    // Facial Portion
    glPushMatrix();
    amount = 90;
    glRotated(-45, 0, 1, 0);
    drawMorCylinderTube(xpos, ypos+(2*height/3), zpos, radius, height/3, radius, amount, 0, 0, 0, 6);
    glPopMatrix();

    glPushMatrix();
    amount = 40;
    glRotated(-45, 0, 1, 0);
    drawMorPointedCylinder(xpos, ypos-(height/2), zpos, radius, height/2, radius, 0, amount, 6, dir);
    glPopMatrix();

    glPushMatrix();
    amount = 40;
    dir = 1;
    glRotated(-95, 0, 1, 0);
    drawMorPointedCylinder(xpos, ypos-(height/2), zpos, radius, height/2, radius, 0, amount, 6, dir);
    glPopMatrix();


    /* Draw Helmet Horns */
    rotation = 0;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height+0.2, horn_radius, 0, 6);
    rotation = 60;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height-0.1, horn_radius, 0, 6);
    rotation = 100;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height-0.5, horn_radius, 0, 6);
    rotation = 140;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height-0.1, horn_radius, 0, 6);
    rotation = 220;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height-0.1, horn_radius, 0, 6);
    rotation = 260;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height-0.5, horn_radius, 0, 6);
    rotation = 300;
    drawMorCone(xpos+r*Cos(90-rotation), ypos+height, zpos+r*Sin(90-rotation), horn_radius, horn_height-0.1, horn_radius, 0, 6);

    /* Draw Helmet Gems */
    glColor3f(0, .2, 1);
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
        glVertex3d(xpos+radius*.7, ypos-height, zpos+.3);
        glVertex3d(xpos+radius*.7, ypos+(height/3), zpos+.3);
    glEnd();

    /* Seal Helmet */
    glColor3f(0, 0, 0);
    drawMorCylinderCap(xpos, ypos, zpos, radius, ypos+height-2*height/3, radius, 0, -1);
    drawMorCylinderCap(xpos, ypos, zpos, radius, -height, radius, 0, 0);

    glPopMatrix(); // End Head Animation
}

/* Draw a Cylinder Tube */
void drawMorCylinderTube(double x, double y, double z, double dx, double dy, double dz, double amount, double th, double xtilt, double ztilt, int tex) 
{
    int j;

    /* Enable textures */
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    
    /* Begin Lighting */
    // float white[] = {1,1,1,1};
    // float black[] = {0,0,0,1};
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

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
void drawMorCappedCylinder(double x, double y, double z, double dx, double dy, double dz, double amount, double th, double xtilt, double ztilt, int tex, int end) 
{
    int j;

    /* Enable textures */
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    
    /* Begin Lighting */
    // float white[] = {1,1,1,1};
    // float black[] = {0,0,0,1};
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

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
        morHalfBall(x+xtilt, -1, z+ztilt, 1, 90, 1, tex);
    else
        morBall(x, 1, z, 1.35, -90, 1, tex);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D); 
}

/* Draw a cylinder cap at (x,y,z) scaled by dx,dy,dz and rotated by th */
void drawMorCylinderCap(double x, double y, double z, double dx, double dy, double dz, double th, int tex) 
{
    int i;

    /* Enable textures */
    if (tex != -1) {
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    }
    
    /* Begin Lighting */
    // float white[] = {1,1,1,1};
    // float black[] = {0,0,0,1};
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

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
void drawMorPinchedTube(double x, double y, double z, double dx, double dy, double dz, double amount, double pinch_factor, double th, int tex)
{
    int j;
    int flipped = 1;

    if (tex != -1) {
        /* Enable textures */
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    }
    
    /* Begin Lighting */
    // float white[] = {1,1,1,1};
    // float black[] = {0,0,0,1};
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();

    /* Transform Cylinder */
    glTranslated(x,y,z);
    glRotated(th,0,0,1);
    glScaled(dx,dy,dz);
    
    if (tex != -1)
        glBindTexture(GL_TEXTURE_2D,textures[tex]);

    if (pinch_factor < 0) {
        flipped = -1;
        pinch_factor *= -1;
    }

    /* Draw the Cylinder */
    glBegin(GL_QUAD_STRIP);
    for (j = 0; j <= (int) amount; j+=10) 
    {
        const float tc = (3*j / (float) 360);

        double x = Cos(j);
        double y = 1;
        double z = Sin(j);

        glNormal3d(Cos(j), 0.0, Sin(j));

        glTexCoord2f(flipped*-tc, 0.0); glVertex3d(x, -y, z);
        //if (j < amount/2) {
            glNormal3d(Cos(j), 0.0, Sin(j));
            glTexCoord2f(flipped*-tc, 1.0); glVertex3d(x*pinch_factor, y, z*pinch_factor);
        // }
        // else {
        //     glNormal3d(Cos(j)-.1, 0.0, Sin(j)-.1);
        //     glTexCoord2f(-tc, 1.0); glVertex3d(x-.1, y, z-.1);
        // }
    }
    glEnd();

    glPopMatrix();

    if(tex != -1)
        glDisable(GL_TEXTURE_2D); 
}

/* A Cylinder with a Pointy Tip for the Helmet */
void drawMorPointedCylinder(double x, double y, double z, double dx, double dy, double dz, double th, double amount, int tex, int dir)
{
    int j;

    /* Enable textures */
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    
    /* Begin Lighting */
    // float white[] = {1,1,1,1};
    // float black[] = {0,0,0,1};
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();

    /* Transform Cylinder */
    glTranslated(x,y,z);
    glRotated(th,0,0,1);
    glScaled(dx,dy,dz);
    
    glBindTexture(GL_TEXTURE_2D,textures[tex]);

    /* Draw the Cylinder */
    glBegin(GL_TRIANGLE_STRIP);
    for (j = 0; j <= (int) amount; j+=10) 
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
void drawMorCone(double x, double y, double z, double dx, double dy, double dz, double th, int tex) 
{
    int i; 

    /* Enable textures */
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    /* Begin Lighting */
    // float white[] = {1,1,1,1};
    // float black[] = {0,0,0,1};
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

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
void drawMorHelmetGrate(double x, double y, double z, double dx, double dy, double dz, double amount, double th, int tex) 
{    
	int j;
	int off = 1; // Keeps track of whether we are drawing or not

    /* Enable textures */
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    
    /* Begin Lighting */
    // float white[] = {1,1,1,1};
    // float black[] = {0,0,0,1};
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

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
void MorVertex(double th, double ph, int tex)
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
    int inc = 10;
    for (ph=0;ph<90;ph+=inc)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=2*inc)
        {
            MorVertex(th,ph, tex);
            MorVertex(th,ph+inc, tex);
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
    int inc = 10;
    for (ph=-90;ph<90;ph+=inc)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=2*inc)
        {
            MorVertex(th,ph, tex);
            MorVertex(th,ph+inc, tex);
            //Vertex(th+inc,ph, tex, 2);
            //Vertex(th+inc,ph+inc, tex, 3);
        }
        glEnd();
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D); 
}