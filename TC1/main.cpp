#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
#include <math.h>
#include <string.h>

#define PI 3.14
//Key status
int keyStatus[256];

const float DEG2RAD = 3.14159/180;
GLfloat gX = 0;
GLfloat gY = 0;

int larguraDaJanela;
int alturaDaJanela;
int fundoR, fundoG, fundoB;

std::string nomeDaJanela;
float raio;
float circuloR, circuloG, circuloB;;
void display(void)
{
   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

   /* Desenhar um polígono branco (retângulo) */
   glColor3f (circuloR, circuloG, circuloB);

float x2;
float y2;
   glBegin(GL_TRIANGLE_FAN);
   for(float angle=0.0f ; angle<2*3.14159 ; angle+=0.2){
    x2 = (gX+sin(angle))*raio;
    y2 = (gY+cos(angle))*raio;
    glVertex3f(x2,y2, 0);
   }
   glEnd();

   /* Não esperar! */
   glutSwapBuffers ();
}


void init (void)
{
  /* selecionar cor de fundo (preto) */
  glClearColor (fundoR, fundoG, fundoB, 0.0);

  /* inicializar sistema de viz. */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
    
  glOrtho(0.0, larguraDaJanela, alturaDaJanela, 0.0, -1.0, 1.0);
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

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
    y = alturaDaJanela + y;
    x = larguraDaJanela + x;
    gX = (GLfloat)x/larguraDaJanela;
    gY = (GLfloat)y/alturaDaJanela;
}

void motion(int x, int y){
    y = alturaDaJanela + y;
    x = larguraDaJanela + x;
    gX = (GLfloat)x/larguraDaJanela;
    gY = (GLfloat)y/alturaDaJanela;
}

void loadXml(const char* pFilename, int *a, int *b){
    TiXmlDocument document("config.xml");
    bool loadOkay = document.LoadFile();
    if (loadOkay)
      printf("okay!\n");
      else
        printf ("not okay\n");
    

    TiXmlHandle xmlHandler (&document);
    TiXmlElement *aplicacao, *janela, *circulo;

    aplicacao = document.FirstChildElement("aplicacao");
    janela = aplicacao->FirstChildElement("janela");


    larguraDaJanela = atof(janela->FirstChildElement("largura")->GetText());
    alturaDaJanela = atof(janela->FirstChildElement("altura")->GetText());
    fundoR = atof(janela->FirstChildElement("fundo")->Attribute("corR")), fundoG = atof(janela->FirstChildElement("fundo")->Attribute("corG")), fundoB = atof(janela->FirstChildElement("fundo")->Attribute("corB"));
    nomeDaJanela = janela->FirstChildElement("titulo")->GetText();
        
    circulo = janela->NextSiblingElement();
    raio =  atof(circulo->Attribute("raio"));
    circuloR = atof(circulo->Attribute("corR"));
    circuloG = atof(circulo->Attribute("corG"));
    circuloB = atof(circulo->Attribute("corB"));
    

}

int main(int argc, char** argv)
{

    char* teste = argv[argc-1];
    printf("%s\n", teste);
    int var1 = 1;
    int var2 = 2;
    loadXml(teste, &var1, &var2);
    
    const char* janela = nomeDaJanela.c_str();


    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (alturaDaJanela, larguraDaJanela);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (janela);
    init ();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0;
}
