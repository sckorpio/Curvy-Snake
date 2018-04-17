#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

GLfloat A=30;
GLfloat B=300;

GLfloat a=0;
GLfloat b=0;

GLfloat ax=0;
GLfloat by=0;

GLfloat ang=0;

GLfloat ta;
GLfloat tb;

float w=0;
float k=0;
float s=0;
int j=1;
int Z=0;

int c=0;

GLfloat arr[2][150];



void makesquare()
{
  glColor3f(0,0,1);

  glBegin(GL_POLYGON);
  glVertex2f(A+ax*5,B+by*5);
  glVertex2f(A+by*10,B+ax*10);
  glVertex2f(A+ax*25,B+by*25);
  glVertex2f(A-by*10,B-ax*10);
  glEnd();
}

void maketail()
{
  int ta,tb;

  glPointSize(5);
  glColor3f(0,1,1);

    glBegin(GL_POINTS);
  for(int i=0;i<150;i++)
  {
    
       ta=arr[0][i];
       tb=arr[1][i];
  
      glVertex2f(ta,tb);
  
  }

  glEnd();

  glPointSize(1);
}


void mydisplay()
{

  glClear(GL_COLOR_BUFFER_BIT);

  glClearColor(1,1,1,0);

    makesquare();
    maketail();

  glFlush();

  
}



void passivemotion(int x,int y)
{

  if(Z==0)
  {  
    a=x;
    b=y;
  }

  else
  {
     Z=0;
  }

  glutPostRedisplay();
}

void init()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glClearColor(1,1,1,0);

    
  glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();

    glOrtho(0,500,500,0,-1,1);

    glMatrixMode(GL_MODELVIEW);

    for(int i=0;i<150;i++)
    {
      arr[0][i]=0;
      arr[1][i]=0;
    }

}

void fril()
{
    arr[0][c]=a;
    arr[1][c]=b;

     c++;

    if(c>149)
      c=0;

    float D=sqrt(((ta-A)*(ta-A))+(tb-B)*(tb-B));

    by=-(ta-A)/D;
    ax=(tb-B)/D;

    A=a;
    B=b;

    a=ta+40*cos(ang);
    b=tb+40*sin(ang);

    
    ang=ang+0.03;

   
  
    glutPostRedisplay();


}


void chase()
{
  
    arr[0][c]=A;
    arr[1][c]=B;


     c++;

    if(c>149)
      c=0;

    float D=sqrt(((a-A)*(a-A))+(b-B)*(b-B));

    ax=(a-A)/D;
    by=(b-B)/D;

    A=A+ax;
    B=B+by;

    if(A>=a-10&&A<=a+10&&B<=b+10&&B>=b-10)
    {  
      ta=a;  tb=b;
      
        Z=1;
        ang=0;
    }
  
    glutPostRedisplay();
}


void Time(int value)
{
     if(Z==0)
     chase();

     else
      fril();
  
  glutTimerFunc(3,Time,0);
}



int main(int argc,char **argv)
{
   
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
   glutInitWindowSize(500,500);
   glutInitWindowPosition(100,100);
   glutCreateWindow("KARTIK");

   init();

   glutDisplayFunc(mydisplay);
   glutTimerFunc(1000,Time,0);
   glutSetCursor(9);
   glutPassiveMotionFunc(passivemotion);

   glutMainLoop();

   return 0;

}