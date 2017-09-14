#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"

//Key status
int keyStatus[256];

GLfloat gX = 0;
GLfloat gY = 0;




void display(void)
{
   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

   /* Desenhar um polígono branco (retângulo) */
   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_POLYGON);
      glVertex3f (0.25+gX, 0.25+gY, 0.0);
      glVertex3f (0.75+gX, 0.25+gY, 0.0);
      glVertex3f (0.75+gX, 0.75+gY, 0.0);
      glVertex3f (0.25+gX, 0.75+gY, 0.0);
   glEnd();

   /* Não esperar! */
   glutSwapBuffers ();
}

void init (void)
{
  /* selecionar cor de fundo (preto) */
  glClearColor (0.0, 0.0, 0.0, 0.0);

  /* inicializar sistema de viz. */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
             gY += 0.01;
             break;
        case 's':
        case 'S':
             gY -= 0.01;
             break;
        case 'a':
        case 'A':
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             break;
        case 27 :
             exit(0);
    }
    glutPostRedisplay();
}

void idle(void)
{
    //Treat keyPress
    if(keyStatus[(int)('a')])
    {
        gX -= 0.001;
    }
    if(keyStatus[(int)('d')])
    {
        gX += 0.001;
    }

    glutPostRedisplay();
}

int tamanhoDaJanela = 500;
void mouse(int button, int state, int x, int y){
    y = tamanhoDaJanela - y;
    printf("x:%d y:%d\n", x, y);
    gX = (GLfloat)x/tamanhoDaJanela;
    gY = (GLfloat)y/tamanhoDaJanela;
}

void motion(int x, int y){
    y = tamanhoDaJanela - y;
    printf("x:%d y:%d\n", x, y);
    gX = (GLfloat)x/tamanhoDaJanela;
    gY = (GLfloat)y/tamanhoDaJanela;
}

int main(int argc, char** argv)
{
    TiXmlDocument document("config.xml");
    bool loadOkay = document.LoadFile();
    if (loadOkay)
      printf("okay!\n");
      else
      printf ("not okay\n");
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (tamanhoDaJanela, tamanhoDaJanela);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello");
    init ();
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyup);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0;
}
