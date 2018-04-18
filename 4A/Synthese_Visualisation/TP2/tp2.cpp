#ifdef __linux__
#include <GL/gl.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#endif

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

#define ANGLE_SPEED 10.0f

#define SPACE_KEY 32
#define ESC_KEY 27

bool animationM1 = false;
bool animationM2 = false;

GLfloat M1[16]; // Boite n°1
GLfloat M2[16]; // Boite n°2

#define X 0
#define Y 1
#define Z 2

void def_carre() {
    glBegin(GL_POLYGON);

    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);

    glEnd();
}

void def_axes() {
    glLineWidth(3);
    glBegin(GL_LINES);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(3.0, 0.0, 0.0); // X axis

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 3.0, 0.0); // Y axis

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 3.0); // Z axis

    glEnd();
}

void def_boite(int a) {
    // Blanc
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    glColor3f(1.0, 1.0, 1.0);
    def_carre();
    glPopMatrix();

    // Rouge
    glPushMatrix();
    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    def_carre();
    glPopMatrix();

    // Vert
    glPushMatrix();
    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    def_carre();
    glPopMatrix();

    // BLEU
    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    def_carre();
    glPopMatrix();

    // CYAN
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5);
    glRotatef(180.0, 1.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 1.0);
    def_carre();
    glPopMatrix();
}

void affichage(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    def_axes();

    // glPolygonMode(GL_BACK, GL_LINE);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);

    glPushMatrix();
    glMultMatrixf(M1);
    def_boite(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0f, 1.0f, -1.0f);
    glMultMatrixf(M2);
    def_boite(1);
    glPopMatrix();

    glutSwapBuffers();
}

void updateMatrix(GLfloat M[16], int axe, int angle) {
    glPushMatrix();
    glLoadIdentity();
    glLoadMatrixf(M);

    switch (axe) {
    case X:
        glRotatef(angle, 1.0f, 0.0f, 0.0f);
        break;
    case Y:
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        break;
    case Z:
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        break;
    }

    glGetFloatv(GL_MODELVIEW_MATRIX, M);
    glPopMatrix();
}

void reshapeCallback(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glGetFloatv(GL_MODELVIEW_MATRIX, M1);
    glGetFloatv(GL_MODELVIEW_MATRIX, M2);

    gluLookAt(1.0f, 1.0f, 3.0f, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1.0, 1.0, 5.0);
}

void animationM1Callback(int) {
    if (animationM1 == true) {
        updateMatrix(M1, X, ANGLE_SPEED);
        updateMatrix(M1, Y, ANGLE_SPEED);
        updateMatrix(M1, Z, ANGLE_SPEED);
        glutPostRedisplay();
        glutTimerFunc(50, animationM1Callback, 0);
    }
}

void animationM2Callback(int) {
    if (animationM2 == true) {
        updateMatrix(M2, X, ANGLE_SPEED);
        updateMatrix(M2, Y, ANGLE_SPEED);
        updateMatrix(M2, Z, ANGLE_SPEED);
        glutPostRedisplay();
        glutTimerFunc(50, animationM2Callback, 0);
    }
}

void keyboardCallback(unsigned char key, int x, int y) {
    switch (key) {
    case ESC_KEY:
        exit(0);
    case 'q':
        updateMatrix(M1, Y, -ANGLE_SPEED);
        break;
    case 'Q':
        updateMatrix(M2, Y, -ANGLE_SPEED);
        break;
    case 'd':
        updateMatrix(M1, Y, ANGLE_SPEED);
        break;
    case 'D':
        updateMatrix(M2, Y, ANGLE_SPEED);
        break;
    case 'z':
        updateMatrix(M1, X, ANGLE_SPEED);
        break;
    case 'Z':
        updateMatrix(M2, X, ANGLE_SPEED);
        break;
    case 's':
        updateMatrix(M1, X, -ANGLE_SPEED);
        break;
    case 'S':
        updateMatrix(M2, X, -ANGLE_SPEED);
        break;
    case 'a':
        updateMatrix(M1, Z, ANGLE_SPEED);
        break;
    case 'A':
        updateMatrix(M2, Z, ANGLE_SPEED);
        break;
    case 'e':
        updateMatrix(M1, Z, -ANGLE_SPEED);
        break;
    case 'E':
        updateMatrix(M2, Z, -ANGLE_SPEED);
        break;
    case SPACE_KEY:
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
            animationM2 = !animationM2;
            glutTimerFunc(50, animationM2Callback, 0);
        } else {
            animationM1 = !animationM1;
            glutTimerFunc(50, animationM1Callback, 0);
        }
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    int win = glutCreateWindow("TP2");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(affichage);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);

    glutMainLoop();

    return 0;
}
