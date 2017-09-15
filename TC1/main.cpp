#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
#include <math.h>

#define PI 3.14
//Key status
int keyStatus[256];

GLfloat gX = 0;
GLfloat gY = 0;

int larguraDaJanela;
int alturaDaJanela;
int fundoR, fundoG, fundoB;

const char* nomeDaJanela;
int raio;
float circuloR, circuloG, circuloB;;
void display(void)
{
   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

   /* Desenhar um polígono branco (retângulo) */
   glColor3f (circuloR, circuloG, circuloB);
   int i;
   int triangleAmount = 20; //# of triangles used to draw circle
   
   //GLfloat raio = 0.8f; //raio
   GLfloat twicePi = 2.0f * PI;
   
   glBegin(GL_TRIANGLE_FAN);
       glVertex2f(gX+0.74, gY+0.74); // center of circle
       for(i = 0; i <= triangleAmount;i++) { 
           glVertex2f(
                   gX + (raio * cos(i *  twicePi / triangleAmount)), 
               gY + (raio * sin(i * twicePi / triangleAmount))
           );
       }
glEnd();

   /* Não esperar! */
   glutSwapBuffers ();
}

void drawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}

void init (void)
{
  /* selecionar cor de fundo (preto) */
  glClearColor (fundoR, fundoG, fundoB, 0.0);

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

void mouse(int button, int state, int x, int y){
    y = alturaDaJanela - y;
    printf("x:%d y:%d\n", x, y);
    gX = (GLfloat)x/larguraDaJanela;
    gY = (GLfloat)y/alturaDaJanela;
}

void motion(int x, int y){
    y = alturaDaJanela - y;
    printf("x:%d y:%d\n", x, y);
    gX = (GLfloat)x/larguraDaJanela;
    gY = (GLfloat)y/alturaDaJanela;
}

void loadXml(const char* pFilename, int *a, int *b){
    printf("%s\n", pFilename);
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


    printf("largura da janela: %d\n", larguraDaJanela = atof(janela->FirstChildElement("largura")->GetText()));
    printf("altura da janela: %d\n", alturaDaJanela = atof(janela->FirstChildElement("altura")->GetText()));
    printf("cor fundo da janela R:%d G:%d B:%d\n", fundoR = atof(janela->FirstChildElement("fundo")->Attribute("corR")), fundoG = atof(janela->FirstChildElement("fundo")->Attribute("corG")), fundoB = atof(janela->FirstChildElement("fundo")->Attribute("corB")));
    printf("nome da janela: %s\n", nomeDaJanela = janela->FirstChildElement("titulo")->GetText());
        
    circulo = janela->NextSiblingElement();
    printf("raio: %s\n", circulo->Attribute("raio"));
    circuloR = atof((circulo->Attribute("corR")));
    printf("corG: %f\n", circuloG = atof(circulo->Attribute("corG")));
    printf("corB: %f\n", circuloB = atof(circulo->Attribute("corB")));
    
    // }

}

int main(int argc, char** argv)
{

    const char* teste = "config.xml";
    int var1 = 1;
    int var2 = 2;
    loadXml(teste, &var1, &var2);
    printf("%s", nomeDaJanela);
    char* string = (char*)nomeDaJanela;
    printf("%s", string);

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (alturaDaJanela, larguraDaJanela);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("asd");
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
