/* Lecture d'une image TGA non compressee et de preference 24 bits (sans
 * transparence) */
/* Cette image est affichee par placage de texture sur une face qui tourne */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <GL/gl.h>
#include <GL/glut.h>
#include <SFML/Audio.hpp>
#elif __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#endif

/* Taille de la fenetre au depart */
#define FENETRE_L 512
#define FENETRE_H 256

#define SPACE_KEY 32
#define ESC_KEY 27

bool animationSquare = false;

/* Un type "image" vraiment très simple */
/* le champ texID va contenir l'identifiant de texture donne par OpenGL */
typedef struct {
    GLubyte *imageData; // Le format TGA peut coder jusqu'4 octets par pixel
    GLuint bpp;   // c'est la qu'est justement stocke le nombre de bits utilises
    GLuint width; // la largeur
    GLuint height; // la hauteur
    GLuint texID;  // l'identifiant de texture
} TextureImage;

/* C'est dans cette variable que va etre stocke la texture */
TextureImage texture;

// Transformation géométrique
#define ANGLE_SPEED 10.0f

#define X 0
#define Y 1
#define Z 2

GLfloat M1[16];

/* Pour faire bouger la texture sur la face */
float uCoord = 0;
float yCoord = 0;

/* Prototype de la fonction, elle est ecrite a la fin du fichier*/
int chargeTextureTGA(TextureImage *texture, char *filename);

void initGL(void) {
    chargeTextureTGA(&texture, "Nyan.tga"); // Lecture de l'image et
                                            // attribution d'un emplacement
                                            // pour la texture rq : on doit
                                            // charger la texture APRES la
                                            // creation du contexte GL
    glEnable(GL_TEXTURE_2D);                // La texture
    glEnable(GL_DEPTH_TEST);                // Le Z-Buffer

    /* on recule le cube ici, c'est plus facile de garder les rotations lors
       d'un redim ... a reflechir un peu ... */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
}

void scroll(int v) {
    // Pour faire "bouger" la texture sur la face */
    uCoord == 1 ? uCoord = 0 : uCoord -= 0.01;
    yCoord == 1 ? yCoord = 0 : yCoord -= sin(uCoord * 60) / 40;
    glutPostRedisplay(); /* On demande l'affichage */
    glutTimerFunc(20, scroll, 0);
}

void updateMatrix(GLfloat M[16], int axe, GLfloat angle) {
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

/* On anime le cube ... car on associe "tourne" a un timer */
void tourne(int v) {
    if (animationSquare) {
        updateMatrix(M1, X, 0.9);
        updateMatrix(M1, Y, 0.6);

        // glRotatef(.9, 1.0f, 0.0f, 0.0f);
        // glRotatef(.6, 0.0f, 1.0f, 0.0f);

        glutPostRedisplay(); /* On demande l'affichage */
        glutTimerFunc(20, tourne, 0);
    }
}

/* Rien de particulier a dire, on a deja explique cette fonction plusieurs fois
 */
void redim(int l, int h) {
    glViewport(0, 0, l, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (GLfloat)l / h, 1., 7.);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, M1);

    gluLookAt(0, 0, -2, 0, 0, 0, 0, 1, 0);
}

void def_carre() {
    glBegin(GL_POLYGON);

    glNormal3f(0.0, 0.0, -1.0);

    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);

    glEnd();
}

void def_carre_texture() {
    glBindTexture(GL_TEXTURE_2D, texture.texID);

    glBegin(GL_POLYGON);

    glColor3f(1.0f, 1.0f, 1.0f);
    glNormal3f(0.0, 0.0, -1.0);

    glTexCoord2f(uCoord, yCoord);
    glVertex2f(-0.5, -0.5);
    glTexCoord2f(uCoord, yCoord + 1.0f);
    glVertex2f(-0.5, 0.5);
    glTexCoord2f(uCoord + 1.0f, yCoord + 1.0f);
    glVertex2f(0.5, 0.5);
    glTexCoord2f(uCoord + 1.0f, yCoord);
    glVertex2f(0.5, -0.5);

    glEnd();
}

void def_boite(float a) {
    float mil = a / 2.0f;

    // Blanc
    glPushMatrix();
    glTranslatef(0.0, 0.0, -mil);
    glScaled(a, a, 1);
    // glColor3f(1.0, 1.0, 1.0);
    def_carre_texture();
    glPopMatrix();

    // Rouge
    glPushMatrix();
    glTranslatef(mil, 0.0, 0.0);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glScaled(a, a, 1);
    // glColor3f(1.0, 0.0, 0.0);
    def_carre_texture();
    glPopMatrix();

    // Vert
    glPushMatrix();
    glTranslatef(-mil, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScaled(a, a, 1);
    // glColor3f(0.0, 1.0, 0.0);
    def_carre_texture();
    glPopMatrix();

    // BLEU
    glPushMatrix();
    glTranslatef(0.0, -mil, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glScaled(a, a, 1);
    // glColor3f(0.0, 0.0, 1.0);
    def_carre_texture();
    glPopMatrix();

    // CYAN
    glPushMatrix();
    glTranslatef(0.0, 0.0, mil);
    glRotatef(180.0, 1.0, 0.0, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0); // Pour avoir le nyan cat dans le bon sens
    glScaled(a, a, 1);
    glColor3f(0.0, 1.0, 1.0);
    def_carre_texture();
    // def_carre();
    glPopMatrix();
}

/* La fonction d'affichage, ce qui nous interesse c'est le glBindTexture et les
 * glTexCoord2f */
void affiche(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glBindTexture(GL_TEXTURE_2D, texture.texID);

    // glBegin(GL_QUADS);
    /* Texture fixe */
    // glTexCoord2f(0.0f, 0.0f); glVertex3f(-.5f, -.5f,  .5f);	// bas gauche
    // glTexCoord2f(1.0f, 0.0f); glVertex3f( .5f, -.5f,  .5f);	// bas droit
    // glTexCoord2f(1.0f, 1.0f); glVertex3f( .5f,  .5f,  .5f);	// haut droit
    // glTexCoord2f(0.0f, 1.0f); glVertex3f(-.5f,  .5f,  .5f);	// haut gauche

    /* On change les coordonnées de texture à chaque affiche, la texture "bouge"
     */
    // glTexCoord2f(uCoord, 0.0f);
    // glVertex3f(-.5f, -.5f, .5f); // bas gauche
    // glTexCoord2f(uCoord + 1.0f, 0.0f);
    // glVertex3f(.5f, -.5f, .5f); // bas droit
    // glTexCoord2f(uCoord + 1.0f, 1.0f);
    // glVertex3f(.5f, .5f, .5f); // haut droit
    // glTexCoord2f(uCoord, 1.0f);
    // glVertex3f(-.5f, .5f, .5f); // haut gauche
    // glEnd();

    glPushMatrix();
    glMultMatrixf(M1);
    def_boite(1.0f);
    glPopMatrix();

    glutSwapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y) {
    switch (key) {
    case ESC_KEY:
        exit(0);
        break;
    case 'q':
        updateMatrix(M1, Y, -ANGLE_SPEED);
        break;
    case 'd':
        updateMatrix(M1, Y, ANGLE_SPEED);
        break;
    case 'z':
        updateMatrix(M1, X, -ANGLE_SPEED);
        break;
    case 's':
        updateMatrix(M1, X, ANGLE_SPEED);
        break;
    case SPACE_KEY:
        animationSquare = !animationSquare;
        glutTimerFunc(4.0f, tourne, 0);
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

/* Que du classique pour vous maintenant ! */
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(FENETRE_L, FENETRE_H);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("texture");

#ifdef __linux__
    sf::Music music;

    if (!music.openFromFile("Nyan.ogx"))
        return -1;

    music.play();
    music.setLoop(true);
#endif

    initGL();

    glutDisplayFunc(affiche);
    glutReshapeFunc(redim);
    glutKeyboardFunc(keyboardCallback);
    glutTimerFunc(4., scroll, 0);

    glutMainLoop();
    return 0;
}

/* Fonction pour un fichier image au format TGA recuperee sur internet */
/* La partie interessante est celle sur la texture a la fin ...*/
int chargeTextureTGA(TextureImage *texture,
                     char *filename) // Loads A TGA File Into Memory
{
    GLubyte TGAheader[12] = {0, 0, 2, 0, 0, 0,
                             0, 0, 0, 0, 0, 0}; // Uncompressed TGA Header
    GLubyte TGAcompare[12];                     // Used To Compare TGA Header
    GLubyte header[6]; // First 6 Useful Bytes From The Header
    GLuint
        bytesPerPixel; // Holds Number Of Bytes Per Pixel Used In The TGA File
    GLuint imageSize;  // Used To Store The Image Size When Setting Aside Ram
    GLuint temp;       // Temporary Variable
    GLuint type = GL_RGBA; // Set The Default GL Mode To RBGA (32 BPP)
    GLuint i;

    FILE *file = fopen(filename, "rb"); // Open The TGA File

    if (file == NULL || // Does File Even Exist?
        fread(TGAcompare, 1, sizeof(TGAcompare), file) !=
            sizeof(TGAcompare) || // Are There 12 Bytes To Read?
        memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) !=
            0 || // Does The Header Match What We Want?
        fread(header, 1, sizeof(header), file) !=
            sizeof(header)) // If So Read Next 6 Header Bytes
    {
        fclose(file); // If Anything Failed, Close The File
        return -1;    // Return False
    }

    texture->width =
        header[1] * 256 +
        header[0]; // Determine The TGA Width	(highbyte*256+lowbyte)
    texture->height =
        header[3] * 256 +
        header[2]; // Determine The TGA Height	(highbyte*256+lowbyte)

    if (texture->width <= 0 ||  // Is The Width Less Than Or Equal To Zero
        texture->height <= 0 || // Is The Height Less Than Or Equal To Zero
        (header[4] != 24 && header[4] != 32)) // Is The TGA 24 or 32 Bit?
    {
        fclose(file); // If Anything Failed, Close The File
        return -1;    // Return False
    }

    texture->bpp = header[4]; // Grab The TGA's Bits Per Pixel (24 or 32)
    bytesPerPixel = texture->bpp / 8; // Divide By 8 To Get The Bytes Per Pixel
    imageSize = texture->width * texture->height *
                bytesPerPixel; // Calculate The Memory Required For The TGA Data

    texture->imageData =
        (GLubyte *)malloc(imageSize); // Reserve Memory To Hold The TGA Data

    if (texture->imageData == NULL || // Does The Storage Memory Exist?
        fread(texture->imageData, 1, imageSize, file) !=
            imageSize) // Does The Image Size Match The Memory Reserved?
    {
        if (texture->imageData != NULL) // Was Image Data Loaded
            free(texture->imageData);   // If So, Release The Image Data

        fclose(file); // Close The File
        return -1;    // Return False
    }

    for (i = 0; i < imageSize;
         i += bytesPerPixel) // Loop Through The Image Data
    {                        // Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
        temp =
            texture
                ->imageData[i]; // Temporarily Store The Value At Image Data 'i'
        texture->imageData[i] = texture->imageData[i + 2]; // Set The 1st Byte
                                                           // To The Value Of
                                                           // The 3rd Byte
        texture->imageData[i + 2] =
            temp; // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
    }

    fclose(file); // Close The File

    /**********************************/
    /******* TEXTURE C'EST LA *********/
    /**********************************/

    /* Demande un identifiant de texture a OpenGL, on le garde en memoire, on en
     * a besoin pour afficher */
    glGenTextures(1, &texture->texID);

    /* Rend la texture "courante, active ..." */
    glBindTexture(GL_TEXTURE_2D, texture->texID);

    /* Filtrage lineaire : classique peu couteux ... */
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* On regarde si l'image est bien en RGB */
    /* pour l'instant on ne gere pas la transparence */
    if (texture->bpp == 24)
        type = GL_RGB;

    /* on "charge" l'image comme texture */
    glTexImage2D(GL_TEXTURE_2D, 0, type, texture->width, texture->height, 0,
                 type, GL_UNSIGNED_BYTE, texture->imageData);

    return 0;
}