#ifdef __linux__
#include <GL/gl.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#endif

#include <iostream>

using namespace std;

void affichageFn2(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void affichage() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void reshapeCallback(int width, int height) { glViewport(0, 0, width, height); }

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    // Fenetre 1
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(400, 500);
    int win = glutCreateWindow("Exemple Fenetre");
    glutDisplayFunc(affichage);
    glutReshapeFunc(reshapeCallback);

    // Fenetre 2
    int win2 = glutCreateWindow("Exemple Fenetre 2");
    glutDisplayFunc(affichageFn2);
    glutReshapeFunc(reshapeCallback);

    glutMainLoop();

    return 0;
}
