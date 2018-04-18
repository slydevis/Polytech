#ifdef __linux__
#include <GL/gl.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#endif

#include <iostream>
#include <vector>

using namespace std;

#define SPACEBAR 32

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

int colorNumber = 0;
int compositionNumber = GL_POLYGON;

class Pos {
  public:
    float x;
    float y;
    Pos(float x, float y) : x(x), y(y) {}
};

std::vector<Pos> squares;

void drawShape() {
    glBegin(compositionNumber);
    glColor3f(1.0, 1.0, 1.0);

    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 0.3);
    glVertex2f(0.4, 0.3);
    glVertex2f(0.6, 0.15);
    glVertex2f(0.4, 0.0);

    glEnd();
}

#define SQUARE_SIZE 0.01f

void drawSquares() {
    for (Pos pos : squares) {
        glBegin(compositionNumber);
        glColor3f(1.0, 1.0, 1.0);

        glVertex2f(pos.x - SQUARE_SIZE, pos.y - SQUARE_SIZE);
        glVertex2f(pos.x - SQUARE_SIZE, pos.y + SQUARE_SIZE);
        glVertex2f(pos.x + SQUARE_SIZE, pos.y + SQUARE_SIZE);
        glVertex2f(pos.x + SQUARE_SIZE, pos.y - SQUARE_SIZE);

        glEnd();
    }
}

void affichage(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawShape();
    drawSquares();

    glFlush();
    glutSwapBuffers();
}

void changeBackgroundColor() {
    switch (colorNumber) {
    case 0:
        glClearColor(255, 0, 0, 1);
        break;
    case 1:
        glClearColor(0, 255, 0, 1);
        break;
    case 2:
        glClearColor(0, 0, 255, 1);
        break;
    case 3:
        glClearColor(255, 255, 0, 1);
        break;
    case 4:
        glClearColor(255, 0, 255, 1);
        break;
    default:
        colorNumber = 0;
        break;
    }

    colorNumber++;

    affichage();
}

void keyboardCallback(unsigned char key, int x, int y) {
    if (key == 'q') {
        exit(0);
    } else if (key == SPACEBAR) {
        changeBackgroundColor();
    }
}

void menuCallback(int value) {
    switch (value) {
    case 1:
        compositionNumber = GL_LINES;
        break;
    case 2:
        compositionNumber = GL_LINE_STRIP;
        break;
    case 3:
        compositionNumber = GL_LINE_LOOP;
        break;
    case 4:
        compositionNumber = GL_POLYGON;
        break;
    case 5:
        compositionNumber = GL_QUADS;
        break;
    case 6:
        compositionNumber = GL_QUAD_STRIP;
        break;
    case 7:
        compositionNumber = GL_TRIANGLES;
        break;
    case 8:
        compositionNumber = GL_TRIANGLE_STRIP;
        break;
    case 9:
        compositionNumber = GL_TRIANGLE_FAN;
    default:
        compositionNumber = GL_POLYGON;
        break;
    }

    affichage();
}

void mouseCallback(int button, int state, int x, int y) {
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            float posx = -1.0f + (x / (glutGet(GLUT_WINDOW_WIDTH) / 2.0f));
            float posy = 1.0f - (y / (glutGet(GLUT_WINDOW_HEIGHT) / 2.0f));

            squares.push_back(Pos(posx, posy));
        }
        break;
    }

    affichage();
}

void reshapeCallback(int width, int height) { glViewport(0, 0, width, height); }

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    int win = glutCreateWindow("Exemple Fenetre");
    glutDisplayFunc(affichage);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutMouseFunc(mouseCallback);

    int sousMenu = glutCreateMenu(menuCallback);
    glutAddMenuEntry("GL_LINES", 1);
    glutAddMenuEntry("GL_LINE_STRIP ", 2);
    glutAddMenuEntry("GL_LINE_LOOP", 3);
    glutAddMenuEntry("GL_POLYGON", 4);
    glutAddMenuEntry("GL_QUADS", 5);
    glutAddMenuEntry("GL_QUAD_STRIP", 6);
    glutAddMenuEntry("GL_TRIANGLES", 7);
    glutAddMenuEntry("GL_TRIANGLE_STRIP", 8);
    glutAddMenuEntry("GL_TRIANGLE_FAN", 9);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
