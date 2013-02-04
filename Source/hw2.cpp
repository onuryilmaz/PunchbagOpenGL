/*
 * Onur Yilmaz
 * CENG 477 HW#2
 *
 */

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

// Pi is used for radian conversion
#define PI 3.142f

using namespace std;

// Camera position
float CameraPositionX = 0;
float CameraPositionY = 0;
float CameraPositionZ = +8;

// Rotation angles
float RotationY = 0;
float RotationX = 0;

// For keyboard movement
float HorizontalBefore;
float VerticalBefore;

// Hit distance for arms
float LeftHit = 0;
float RightHit = 0;

// Mouse click flags
int RightClick = 0;
int LeftClick = 0;

// Collision flags
int LeftCollision = 0;
int RightCollision = 0;
int Collision = 0;

// Swing amount
float Swing;

// Swinging in radian
float SwingRadian;

// Swing changes in X and Z
float SwingPositionX;
float SwingPositionZ;

// Punch height
float PunchHeight = 1.0;

// Main window
int main_window;

// Light position and white color
// Taken from triangle.cpp
GLfloat light_position[] = {10, 10, 10, 1.0}; // Light position coordinates
GLfloat whiteColor[] = {1.0, 1.0, 1.0, 0.0}; // White color RGB values

// Function declarations
void drawPunch(void);
void DrawPoleHorizontal(void);
void DrawPoleVertical(void);
void drawCone(void);
void drawArm(void);
void drawGlove(void);
void display(void);
void update(int, int);
void keyboard(unsigned char, int, int);
void mouseMovement(int, int);
void mouseButton(int, int, int, int);
void myInit(void);

// Drawing function for sphere in punchbag

void drawPunch(void) {
    GLUquadric *quadric = gluNewQuadric();
    gluSphere(quadric, 1.2f, 300, 100);
}

// Drawing function for pole (horizontal part) in punchbag

void DrawPoleHorizontal(void) {
    GLUquadric *quadric = gluNewQuadric();
    gluCylinder(quadric, 0.1, 0.1, 3.0f, 64, 64);
}

// Drawing function for pole (vertical part) in punchbag

void DrawPoleVertical(void) {
    GLUquadric *quadric = gluNewQuadric();
    gluCylinder(quadric, 0.1, 0.1, PunchHeight + 3 + 5 + 0.01, 64, 64);
}

// Drawing function for cone in punchbag

void drawCone(void) {
    GLUquadricObj *quadObj = gluNewQuadric();
    gluCylinder(quadObj, 1.2, 0.001, 3, 100, 100);
}

// Drawing function for gloves

void drawGlove(void) {
    GLUquadric *quadric = gluNewQuadric();
    gluSphere(quadric, 0.8f, 70, 200);
}

// Drawing function for arms

void drawArm(void) {
    GLUquadric *quadric = gluNewQuadric();
    gluCylinder(quadric, 0.4, 0.4, 150.0f, 64, 64);
}

/*
 * Display function
 *
 */
void display(void) {

    // Background color
    glClearColor(0.4f, 0.4f, 0.8f, 1.0f);

    // Buffer clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Load identity matrix
    glLoadIdentity();

    // If left click
    if (LeftClick) {

        // Decrease length
        LeftHit -= 0.1;

        // Check limit
        if (LeftHit<-2)
            LeftHit = -2;

        // Remove flag
        if (LeftHit == -2)
            LeftClick = 0;

    }

    // If flag is removed

    if (!LeftClick) {
        // Increase length
        LeftHit += 0.1;

        // Check limit
        if (LeftHit > 0)
            LeftHit = 0;
    }


    // If right click
    if (RightClick) {

        // Decrease length
        RightHit -= 0.1;

        // Check limit
        if (RightHit<-2)
            RightHit = -2;

        // Remove flag
        if (RightHit == -2)
            RightClick = 0;

    }

    // If flag is removed

    if (!RightClick) {
        // Increase length
        RightHit += 0.1;

        // Check limit
        if (RightHit > 0)
            RightHit = 0;
    }

    // Test for writing the distance
    // cout << pow((CameraPositionX), 2) + pow((CameraPositionY - PunchHeight), 2) + pow((CameraPositionZ + 2.2), 2) << endl;

    // Left collision
    // If hits and touches or just touches
    if ((LeftClick && (pow((CameraPositionX), 2) + pow((CameraPositionY - PunchHeight), 2) + pow((CameraPositionZ + 2.2), 2)) < 45) ||
            (pow((CameraPositionX), 2) + pow((CameraPositionY - PunchHeight), 2) + pow((CameraPositionZ + 2.2), 2)) < 30)
        LeftCollision = 1;

    // Right collision
    // If hits and touches or just touches
    if ((RightClick && (pow((CameraPositionX), 2) + pow((CameraPositionY - PunchHeight), 2) + pow((CameraPositionZ + 2.2), 2)) < 45) ||
            (pow((CameraPositionX), 2) + pow((CameraPositionY - PunchHeight), 2) + pow((CameraPositionZ + 2.2), 2)) < 30)
        RightCollision = 1;

    // Check for collision
    if (LeftCollision == 1 || RightCollision == 1)
        Collision = 1;
    else Collision = 0;

    // If collision occurs
    if (Collision) {

        // Decrease angle
        Swing = Swing - 2;

        // Check for limit
        if (Swing <-30) {
            Swing = -30;
            Collision = 0;
            LeftCollision = 0;
            RightCollision = 0;
        }
    }

    // If no collision
    if (!Collision) {

        // Increase angle
        Swing = Swing + 2;

        // Check for limit
        if (Swing > 0)
            Swing = 0;
    }


    // Camera rotation and translate
    glRotatef(RotationX, 1.0, 0.0, 0.0);
    glRotatef(RotationY, 0.0, 1.0, 0.0);
    glTranslatef(-CameraPositionX, -CameraPositionY, -CameraPositionZ);

    // Draw sphere of punchbag
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f);
    glTranslatef(0, PunchHeight, -2.2);
    glTranslatef(0, 0, Swing / 60);
    drawPunch();
    glPopMatrix();

    // Draw cone of punchbag
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f);
    glTranslatef(0, PunchHeight, -2.2);
    glRotatef(-90, 1.0, 0, 0);
    glTranslatef(0, -Swing / 60, 0);
    glRotatef(-Swing / 2, -(CameraPositionX - 3), 0, -(CameraPositionZ - 8));
    drawCone();
    glPopMatrix();

    // Draw horizontal pole of punchbag
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f);
    glTranslatef(0, PunchHeight + 3, -2.2);
    glRotatef(90, 0, 1.0, 0);
    DrawPoleHorizontal();
    glPopMatrix();

    // Draw vertical pole of punchbag
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f);
    glTranslatef(3, -4.99, -2.2);
    glRotatef(-90, 1.0, 0, 0);
    DrawPoleVertical();
    glPopMatrix();


    // Draw left arm
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(-RotationX, 1.0, 0.0, 0.0);
    glRotatef(-RotationY, 0.0, 1.0, 0.0);
    glTranslatef(CameraPositionX, CameraPositionY, CameraPositionZ);
    glTranslatef(-3, -3, -10 + LeftHit);

    drawArm();
    glPopMatrix();

    // Draw left glove
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glRotatef(-RotationX, 1.0, 0.0, 0.0);
    glRotatef(-RotationY, 0.0, 1.0, 0.0);

    glTranslatef(CameraPositionX, CameraPositionY, CameraPositionZ);
    glTranslatef(-3, -3, -10 + LeftHit);
    drawGlove();
    glPopMatrix();

    // Draw right arm
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(-RotationX, 1.0, 0.0, 0.0);
    glRotatef(-RotationY, 0.0, 1.0, 0.0);

    glTranslatef(CameraPositionX, CameraPositionY, CameraPositionZ);
    glTranslatef(+3, -3, -10 + RightHit);
    drawArm();
    glPopMatrix();

    // Draw right glove
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glRotatef(-RotationX, 1.0, 0.0, 0.0);
    glRotatef(-RotationY, 0.0, 1.0, 0.0);

    glTranslatef(CameraPositionX, CameraPositionY, CameraPositionZ);
    glTranslatef(+3, -3, -10 + RightHit);
    drawGlove();
    glPopMatrix();

    // Draw floor
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.75, 0.75, 0.75);
    glVertex3f(-10, -5, 15);
    glVertex3f(-10, -5, -15);
    glVertex3f(10, -5, -15);
    glVertex3f(10, -5, 15);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();

}

// Update function

void update(int w, int h) {

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(60, (GLfloat) w / (GLfloat) h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);

}

/*
 * Keyboard movement function
 * Idea based on the article http://nehe.gamedev.net/article/camera_class_tutorial/18010/
 */
void keyboard(unsigned char key, int x, int y) {

    switch (key) {

            // Walk forward
        case 'w':
            CameraPositionX = CameraPositionX + float(sin((RotationY / 180 * PI)));
            CameraPositionY = CameraPositionY - float(sin((RotationX / 180 * PI)));
            CameraPositionZ = CameraPositionZ - float(cos((RotationY / 180 * PI)));
            break;

            // Walk backward
        case 's':
            CameraPositionX = CameraPositionX - float(sin(RotationY / 180 * PI));
            CameraPositionY = CameraPositionY + float(sin(RotationX / 180 * PI));
            CameraPositionZ = CameraPositionZ + float(cos(RotationY / 180 * PI));
            break;

            // Walk left
        case 'a':
            CameraPositionX = CameraPositionX - float(cos(RotationY / 180 * PI));
            CameraPositionZ = CameraPositionZ - float(sin(RotationY / 180 * PI));
            break;

            // Walk right
        case 'd':

            CameraPositionX = CameraPositionX + float(cos(RotationY / 180 * PI));
            CameraPositionZ = CameraPositionZ + float(sin(RotationY / 180 * PI));
            break;

            // Decrease height
        case 'z':
            // Test for distance
            //  cout << pow((CameraPositionX-0.5), 2 ) +  pow((CameraPositionY-2.2),2 )<< endl;
            // If in radius, decrease height
            if (pow((CameraPositionX - 0.5), 2) + pow((CameraPositionZ - 2.2), 2) < 100)
                PunchHeight -= 0.1;
            // Height limit
            if (PunchHeight<-1)
                PunchHeight = -1;
            break;

            // Increase height
        case 'x':
            // If in radius, increase height
            if (pow((CameraPositionX - 0.5), 2) + pow((CameraPositionZ - 2.2), 2) < 100)
                PunchHeight += 0.1;
            // Height limit
            if (PunchHeight > 7)
                PunchHeight = 7;
            break;

            // Exit on escape
        case 27:
            exit(0);
            break;
    }
}


// Mouse movement function

void mouseMovement(int x, int y) {

    // Difference calculation
    int ChangeHorizontal = x - HorizontalBefore;
    int ChangeVertical = y - VerticalBefore;

    // Save as last
    HorizontalBefore = x;
    VerticalBefore = y;

    // Change with ratio
    RotationX += (float) ChangeVertical / 20;
    RotationY += (float) ChangeHorizontal / 20;
}

// Mouse click function

void mouseButton(int button, int state, int x, int y) {

    if (button == GLUT_RIGHT_BUTTON) {
        RightClick = 1;
        // cout << "Right click" << endl;
    }

    if (button == GLUT_LEFT_BUTTON) {
        //cout << "Left click" << endl;
        LeftClick = 1;
    }
}

/*
 * init function
 * Taken from triangle.cpp
 *
 */

void myInit(void) {
    // Any initialization before the main loop of GLUT goes here

    glEnable(GL_DEPTH_TEST); // Enable depth Buffering
    glEnable(GL_COLOR_MATERIAL); // Enable color tracking
    glEnable(GL_NORMALIZE); // Enables vector normalization (optional)
    glClearColor(0.4f, 0.4f, 0.8f, 1.0f); // Set initial value of color buffer (Set background color also)

    // Lighting initialization
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    GLfloat ambientColor[] = {0.5f, 0.5f, 0.5f, 1.0f}; // Ambient light RGBs (You can modify the arguments if needed.)

    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //Set position.
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor); //Set ambient light.
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor); //Set diffuse component.
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor); //Set specular component.

    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Set light position

    // Initialize camera
    glMatrixMode(GL_PROJECTION); // Switch  to projection matrix
    glLoadIdentity(); // Clear current matrix to identity matrix
    gluPerspective(80, 1, 1, 1000000); // Set projection of camera (You can modify the arguments if needed.)

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Mouse movement parameters
    HorizontalBefore = 0;
    VerticalBefore = 0;
}

/*
 * Main function
 *
 */

int main(int argc, char **argv) {

    //   Initialize GLUT and create window

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(800, 800);
    main_window = glutCreateWindow("CENG477 - HW#2");

    glutDisplayFunc(display);

    glutIdleFunc(display);
    glutReshapeFunc(update);
    myInit();

    glutPassiveMotionFunc(mouseMovement);
    glutMouseFunc(mouseButton);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}

// End of code
