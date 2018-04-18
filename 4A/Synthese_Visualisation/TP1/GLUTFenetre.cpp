#ifdef __linux__
#include <GL/gl.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#endif

#include <iostream>

using namespace std;

#define SPACEBAR 32

int colorNumber = 0;

void affichage() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void reshapeCallback(int width, int height) { glViewport(0, 0, width, height); }

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(400, 500);
    int win = glutCreateWindow("Exemple Fenetre");
    glutKeyboardFunc(keyboardCallback);
    glutReshapeFunc(reshapeCallback);
    glutDisplayFunc(affichage);

    glutMainLoop();

    return 0;
}
