/*
g++ -Wall -o  carrera carreradecaracole.cpp -lglut -lGL -lGLU
*/

#define numeroDeJugadores 2

// #include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define pi 3.14156295

int numero = 0;

class carac
{
public:
    carac(int nro)
    {

        achicamiento = 0.1; // velocidad de
        largoInt = 4;
        velocidad = 0.2;
        tamanio = 1;
        largo = 3;
        choques = 0;
        anteriorX = 0;
        anteriorY = 0;
        NroDeBaba = 0;
        choque = false;
        choqueNro = 0;
        puntos = 0;
        switch (nro)
        {
        case 1:
            x = 0;
            y = 0;
            angulo = 180;
            color[0] = 1;
            color[1] = 1;
            color[2] = 1;
            break;
        case 2:
            x = 10;
            y = 10;
            angulo = 90;
            color[0] = 1;
            color[1] = 0.5;
            color[2] = 0;

            break;
        case 3:
            x = 20;
            y = 20;
            angulo = 0;
            color[0] = 0.1;
            color[1] = 1;
            color[2] = 0.8;

            break;
        case 4:
            x = 50;
            y = 50;
            angulo = 45;
            color[0] = 0.4;
            color[1] = 0.17;
            color[2] = 0.67;

            break;
        }
    };
    float x;
    float y;
    float masX;
    float masY;
    float color[3];
    int largo;
    float velocidad;
    double angulo;
    float tamanio;
    float largoInt;
    float achicamiento;
    int choques;
    float anteriorX;
    float anteriorY;
    int NroDeBaba;
    bool choque;
    int choqueNro;
    int puntos;
    void dib()
    {
        glColor3d(color[0], color[1], color[2]);
        if (choqueNro <= 0)
        {
            masY = sin(angulo * pi / 180) * velocidad;
            y += masY;
            masX = cos(angulo * pi / 180) * velocidad;
            x += masX;
            glPushMatrix();
            glTranslated(x, y, -4);
            glRotated(angulo, 0, 0, 1);

            // orejas
            glPushMatrix();
            glTranslated(largoInt * tamanio - tamanio * 1.7, 0, 1);
            // glRotated(5,1*largoInt,0,0);
            glScaled(tamanio * 0.2, tamanio * 0.2, tamanio * 2);
            glTranslated(0, -2, 0);
            glRotated(30, 0, 1, 0);
            glutSolidSphere(1, 16, 16);
            glRotated(-30, 0, 1, 0);
            glTranslated(0, 4, 0);
            glRotated(-30, 1, 0, 1);
            glutSolidSphere(1, 16, 16);
            glPopMatrix();
            // cuerpo 1
            glTranslated(-tamanio, 0, 0);
            glPushMatrix();
            glScaled(tamanio * largoInt, tamanio, tamanio);
            glRotated(45, 0, 1, 0);
            glutSolidSphere(1, 16, 16);
            glPopMatrix();

            // cuerpo 2
            glTranslated(-tamanio * 2, 0, 0);
            glPushMatrix();
            glScaled(tamanio * largoInt, tamanio, tamanio);
            glRotated(-45, 0, 1, 0);
            glutSolidSphere(1, 16, 16);
            glPopMatrix();

            // caparazon
            glTranslated(-tamanio * 0.5, 0, 0);
            glutSolidSphere(tamanio * 2, 16, 16);
            glPopMatrix();
            largoInt -= achicamiento;

            if (largoInt <= 1.4 || largoInt >= 4)
            {
                achicamiento = achicamiento * -1;
            };
        }
        else
        {
            y += masY;
            x += masX;
            glPushMatrix();
            glTranslated(x, y, -4);
            glTranslated(-tamanio * largoInt, 0, 0);
            glutSolidSphere(tamanio * 2, 16, 16);
            glPopMatrix();
            choqueNro--;
            puntos -= 0.0001;
        };
    };
};
class bab
{
public:
    bab()
    {
        x = 1000;
        y = 1000;
    };
    float x;
    float y;

    void dib()
    {

        glPushMatrix();
        glTranslated(x, y, 0);
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(-0.6, 0.6, -4);

        glVertex3f(-0.6, -0.6, -4);
        glVertex3f(+0.6, -0.6, -4);
        glVertex3f(+0.6, +0.6, -4);
        glEnd();

        glPopMatrix();
    };
};
int roscaX;
int roscaY;
int ff;

carac caracol[4] = {1, 2, 3, 4};

bab baba[4][1000];
int nroDeJugadores = numeroDeJugadores-1;

static int slices = 16;
static int stacks = 16;

void check()
{
    for (int a = 0; a <= nroDeJugadores; a++)
    {
        for (int b = 0; b <= nroDeJugadores; b++)
        {
            for (int c = 0; c <= caracol[b].largo; c++)
            {
                if (

                    caracol[a].x >= baba[b][c].x - 1.3 &&
                    caracol[a].x <= baba[b][c].x + 1.3 &&
                    caracol[a].y <= baba[b][c].y + 1.3 &&
                    caracol[a].y >= baba[b][c].y - 1.3)
                {
                    caracol[a].choqueNro = 400;
                    caracol[a].puntos -= 0.01;
                    break;
                }
            }
        }

        if (
            caracol[a].x >= roscaX - 2 &&
            caracol[a].x <= roscaX + 2 &&
            caracol[a].y <= roscaY + 2 &&
            caracol[a].y >= roscaY - 2)
        {
            caracol[a].largo += 25;
            roscaX = rand() % 90;
            roscaY = rand() % 90;
            caracol[a].puntos += 100;
        }
        if (
            caracol[a].x >= 100 ||
            caracol[a].x <= -100)
        {
            caracol[a].x *= -1;
        }

        if (
            caracol[a].y <= -100 ||
            caracol[a].y >= 100)
        {
            caracol[a].y *= -1;
        }
    }
}

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-120, 120, -120, 120, -10, 170);
    glMatrixMode(GL_MODELVIEW);
}
int cadacien = 10; 

int angulacion = 2;

bool tecl[20];
void specialKeys(int key, int x, int y)
{
    switch (key)
    {

    case GLUT_KEY_RIGHT:
        tecl[3] = true; // caracol[1].angulo-=angulacion;
        break;
    case GLUT_KEY_LEFT:
        tecl[2] = true; // racol[1].angulo+=angulacion;
        break;
    }
}
static void key(unsigned char key, int x, int y)
{

    switch (key)
    {

    case 27:
    case 'q':
        exit(0);
        break;

    case '+':
        slices++;
        stacks++;
        break;

    case '-':
        if (slices > 3 && stacks > 3)
        {
            slices--;
            stacks--;
        }
        break;
    case 'a':
        tecl[0] = true;
        break;
    case 'd':
        tecl[1] = true;
        break;
    case 'j':
        tecl[4] = true;
        break;
    case 'l':
        tecl[5] = true;
        break;
    case 'r':
        tecl[6] = true;
        break;
    case 'y':
        tecl[7] = true;
        break;
    }


    glutPostRedisplay();
}
const GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {2.0f, 5.0f, 5.0f, 0.0f};

const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};

static void keyup(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        tecl[0] = false;
        break;
    case 'd':
        tecl[1] = false;
        break;
    case 'j':
        tecl[4] = false;
        break;
    case 'l':
        tecl[5] = false;
        break;
    case 'r':
        tecl[6] = false;
        break;
    case 'y':
        tecl[7] = false;
        break;
    }
}
static void keyupS(int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_RIGHT:
        tecl[3] = false;

        break;
    case GLUT_KEY_LEFT:
        tecl[2] = false;
        break;
    }
}
void teclas()
{
    if (tecl[0])
        caracol[0].angulo += angulacion;
    if (tecl[1])
        caracol[0].angulo -= angulacion;
    if (tecl[2])
        caracol[1].angulo += angulacion;
    if (tecl[3])
        caracol[1].angulo -= angulacion;
    if (tecl[4])
        caracol[2].angulo += angulacion;
    if (tecl[5])
        caracol[2].angulo -= angulacion;
    if (tecl[6])
        caracol[3].angulo += angulacion;
    if (tecl[7])
        caracol[3].angulo -= angulacion;
};

static void idle(void)
{

    glutPostRedisplay();
}

static char label[100];

void inline drawString(char *s)
{
    unsigned int i;
    for (i = 0; i < strlen(s); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
}

void texto(int aa)
{


    glColor3f(1, 0, 0.1);
    sprintf(label, "%d", caracol[aa].puntos);
    glRasterPos2f((- aa * -30)-15, 100);
    drawString(label);
}

static void display(void)
{
    teclas();

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t * 90.0;
    // gluLookAt(20,20,20,0,,0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glColor3d(1,0,0);

    // baba nueva
    if (cadacien == 0)
    {
        for (int b = 0; b <= nroDeJugadores; b++)
        {
            baba[b][caracol[b].NroDeBaba].x = caracol[b].anteriorX;
            baba[b][caracol[b].NroDeBaba].y = caracol[b].anteriorY;
            caracol[b].anteriorX = caracol[b].x;
            caracol[b].anteriorY = caracol[b].y;
            caracol[b].NroDeBaba++;
            if (caracol[b].NroDeBaba == caracol[b].largo)
                caracol[b].NroDeBaba = 0;
        };

        // Entrada posicion de caracol

        cadacien = 10;
    }
    cadacien--;

    for (int b = 0; b <= nroDeJugadores; b++)
    {
        for (int a = 0; a <= caracol[b].largo; a++)
        {
            baba[b][a].dib();
        };

        glColor3f(1.0, 0.0, 0.0);
        caracol[b].dib();
        texto(b);
    };
    glBegin(GL_QUADS);
    glColor3f(100, 100, -4);
    glVertex3f(-100, 100, -6);

    glVertex3f(-100, -100, -6);
    glVertex3f(+100, -100, -6);
    glVertex3f(+100, +100, -6);
    glEnd();

    glColor3f(0, 1, 0);
    glPushMatrix();
    glTranslated(roscaX, roscaY, -4);
    glRotated(60, 1, 0, 0);
    glRotated(a, 0, 0, 1);
    glutSolidTorus(1, 2, slices, stacks);
    glPopMatrix();

    glutSwapBuffers();
    check();
}
int main(int argc, char *argv[])
{
    roscaX = rand() % 50;
    roscaY = rand() % 50;
    glutInit(&argc, argv);
    glutInitWindowSize(1640, 1480);
    glutInitWindowPosition(1, 1);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    // glutFullScreen();
    glutCreateWindow("CARRERA DE CARACOLES");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKeys);
    glutKeyboardUpFunc(keyup);
    glutSpecialUpFunc(keyupS);

    glutIdleFunc(idle);

    glClearColor(1, 1, 1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
