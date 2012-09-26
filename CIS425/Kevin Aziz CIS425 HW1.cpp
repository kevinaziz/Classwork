/**************************************************
*
* Official Name: Kevin Aziz
* 
* Nickname: Kevin
*
* E-mail: kdaziz@syr.edu
*
* Assignment: Assignment 1
*
* Environment/Compiler: Visual Studio 2012 RC
*
* Date: September 20, 2012
*
******************************************/
#include "stdafx.h"
#include <cmath>
#include <time.h>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265

using namespace std;

// Globals
bool isWire = false;
bool ifOrtho = true;
GLsizei WIDTH=500;
GLsizei HEIGHT=500;

static int v = 10; // Number of longitudinal (verticle) slices.
static int h = 10; // Number of latitudinal (horizontal) slices 
                  //on hemisphere.
void writeBitmapString(void *font, char *string){
	char *c;
	for (c = string; *c!='\0'; c++) glutBitmapCharacter(font, *c); 
}
void drawSphere(float x, float y, float z, float a, float b, float c)//drawSphere is drawHead reworked to accept Params of r,x,y,z,a,b,c (It's really now draw ellipsoid)
{
  int i, j;
  // Based on hemisphere.cpp from Guha
  // cx, cy,cz is the center of the sphere, R is the radius.
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  for(j = 0; j < h; j++)
  {
    // One latitudinal triangle strip. top half
    glBegin(GL_TRIANGLE_STRIP);
    for(i = 0; i <= v; i++)
    {
		glVertex3f( a * cos( (float)(j+1)/h * PI/2.0 ) * cos( 2.0 * (float)i/v * PI )+x,
				b * sin( (float)(j+1)/h * PI/2.0 )+y,
                 c * cos( (float)(j+1)/h * PI/2.0 ) * sin( 2.0 * (float)i/v * PI )+z );
      glVertex3f( a * cos( (float)j/h * PI/2.0 ) * cos( 2.0 * (float)i/v * PI  )+x,
                 b * sin( (float)j/h * PI/2.0  )+y,
                 c * cos( (float)j/h * PI/2.0 ) * sin( 2.0 * (float)i/v * PI)+z );         
    }
	glEnd();
	// One latitudinal triangle strip. bottom half
    glBegin(GL_TRIANGLE_STRIP);
    for(i = 0; i <= v; i++)
    {
      glVertex3f( a * cos( (float)(j+1)/h * PI/2.0 ) * cos( 2.0 * (float)i/v * PI )+x,
				-1*b * sin( (float)(j+1)/h * PI/2.0 )+y,
                 c * cos( (float)(j+1)/h * PI/2.0 ) * sin( 2.0 * (float)i/v * PI )+z );
      glVertex3f( a * cos( (float)j/h * PI/2.0 ) * cos( 2.0 * (float)i/v * PI  )+x,
                 -1*b * sin( (float)j/h * PI/2.0  )+y,
                 c * cos( (float)j/h * PI/2.0 ) * sin( 2.0 * (float)i/v * PI)+z );         
    }
    glEnd();
  }
}
void drawSphere(float x, float y, float z, float r){ drawSphere(x,y,z,r,r,r); }
void drawCylinder(char orientation, float h, float r, float x, float y, float z){
	switch(orientation){
	case 'x':		
		glBegin(GL_TRIANGLE_STRIP);
			for(float i=0;i<19.0;i++){
				glVertex3f(x,y+r*cos(i*PI/9),z+r*sin(i*PI/9));
				glVertex3f(x-h,y+r*cos(i*PI/9),z+r*sin(i*PI/9));
			}
		glEnd();		
		glBegin(GL_LINE_LOOP);
			for(float i=0;i<19.0;i++){
				glVertex3f(x,y+r*cos(i*PI/9),z+r*sin(i*PI/9));
			}
		glEnd();		
		glBegin(GL_LINE_LOOP);
			for(float i=0;i<19.0;i++){
				glVertex3f(x-h,y+r*cos(i*PI/9),z+r*sin(i*PI/9));
			}
		glEnd();
		break;
	case 'y':
		glBegin(GL_TRIANGLE_STRIP);
			for(float i=0;i<19.0;i++){
				glVertex3f(x+r*cos(i*PI/9),y,z+r*sin(i*PI/9));
				glVertex3f(x+r*cos(i*PI/9),y-h,z+r*sin(i*PI/9));
			}
		glEnd();
		glBegin(GL_LINE_LOOP);
			for(float i=0;i<19.0;i++){
				glVertex3f(x+r*cos(i*PI/9),y,z+r*sin(i*PI/9));
			}
		glEnd();		
		glBegin(GL_LINE_LOOP);
			for(float i=0;i<37.0;i++){
				glVertex3f(x+r*cos(i*PI/9),y-h,z+r*sin(i*PI/9));
			}
		glEnd();
		break;
	default:
		break;
	}

}
void drawCone(char orientation, float h, float r, float x, float y, float z){
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x,y,z);
	switch(orientation){
		case 'x':		
			for(float i=0;i<19.0;i++){
				glVertex3f(x-h,y+r*cos(i*PI/9),z+r*sin(i*PI/9));
			}
			break;
		case 'y':
			for(float i=0;i<19.0;i++){
				glVertex3f(x+r*cos(i*PI/9),y-h,z+r*sin(i*PI/9));
			}
			break;
	}
	
	glEnd();
}
void drawVertHelix(float R, float offset){ //Unused function, was going to make a helical birdcage but was having difficulty with glfrustrum
	//This function is modified from Guha's helix.cpp
	//Modifications: Added an offset variable to change the helix start position
	//				 (trivial: switched R to being a parameter, changed t range)
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
		for(float t = -5 * PI; t <= 5 * PI; t += PI/10.0) {
			glVertex3f(R * cos(t+offset*PI), t*.25 , -1*R * sin(t+offset*PI));
		}
	glEnd();
}
void drawElephant(float size, float x, float y, float z, float r, float g, float b){
	glColor3f(r,g,b);
	//LEGS
	drawCylinder('y', size*.75, size*.175, x+size*.4, y, z+size*.25);
	drawCylinder('y', size*.75, size*.175, x-size*.6, y, z+size*.25);
	drawCylinder('y', size*.75, size*.175, x+size*.4, y, z-size*.25);
	drawCylinder('y', size*.75, size*.175, x-size*.6, y, z-size*.25);
	//Body,Trunk,Head
	drawSphere(x, y, z, size, .6*size, .6*size); //Body
	drawSphere(x+.8*size, y+.05*size, z, size*.5, .45*size, .5*size); //Head
	drawCylinder('y', size*.6, size*.1, x+size*1.2, y+size*.1, z); //Trunk
	//EYES
	glColor3f(r*0.8,g*0.8,b*0.8);
	drawCone('y',size*.35,size*.05,x-size,y,z);
	// EARS - Use triangle Fans, back of ears stick out further
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(x+.7*size,y+.5*size,z+.3*size);
		glVertex3f(x, y+.55*size,z+.65*size);
		glVertex3f(x+.1*size,y+.4*size,z+.65*size);
		glVertex3f(x+.2*size,y,z+.75*size);
		glVertex3f(x+.25*size,y-.2*size,z+.65*size);
		glVertex3f(x+.3*size,y-.3*size,z+.65*size);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(x+.7*size,y+.5*size,z-.3*size);
		glVertex3f(x, y+.55*size,z-.65*size);
		glVertex3f(x+.1*size,y+.4*size,z-.65*size);
		glVertex3f(x+.2*size,y,z-.75*size);
		glVertex3f(x+.25*size,y-.2*size,z-.65*size);
		glVertex3f(x+.3*size,y-.3*size,z-.65*size);
	glEnd();
	glColor3f(1,1,1);
	drawSphere(x+size, y, z+size*.35, size*.1, .1*size, .1*size); 
	drawSphere(x+size, y, z-size*.35, size*.1, .1*size, .1*size); 
	glColor3f(0,0,0);
	drawSphere(x+size*1.05, y, z+size*.4, size*.025, .05*size, .05*size); 
	drawSphere(x+size*1.05, y, z-size*.4, size*.025, .05*size, .05*size); 
}
void drawElephant(float size, float x, float y, float z){
	drawElephant(size,x,y,z,0.5,0.5,0.5);
}
void drawWings(float birdX, float birdY, float birdZ,float wingspan,float wingwidth){
	
	float verticesWing1[] = {
		birdX , birdY, birdZ+1,
		birdX+wingspan, birdY, birdZ+1,
		birdX+wingspan*0.95, birdY-wingwidth*.1, birdZ+1,
		birdX+wingspan*0.9 , birdY-wingwidth*.2, birdZ+1,
		birdX+wingspan*0.85, birdY-wingwidth*.3, birdZ+1,
		birdX+wingspan*0.7 , birdY-wingwidth*.4, birdZ+1,
		birdX+wingspan*0.75, birdY-wingwidth*.5, birdZ+1,
		birdX+wingspan*0.7 , birdY-wingwidth*.6, birdZ+1,
		birdX+wingspan*0.6 , birdY-wingwidth*.8, birdZ+1,
		birdX+wingspan*0.5 , birdY-wingwidth, birdZ+1
	};
	float verticesWing2[] = {
		birdX , birdY, birdZ-1,
		birdX+wingspan, birdY, birdZ-1,
		birdX+wingspan*0.95, birdY-wingwidth*.1, birdZ-1,
		birdX+wingspan*0.9 , birdY-wingwidth*.2, birdZ-1,
		birdX+wingspan*0.85, birdY-wingwidth*.3, birdZ-1,
		birdX+wingspan*0.7 , birdY-wingwidth*.4, birdZ-1,
		birdX+wingspan*0.75, birdY-wingwidth*.5, birdZ-1,
		birdX+wingspan*0.7 , birdY-wingwidth*.6, birdZ-1,
		birdX+wingspan*0.6 , birdY-wingwidth*.8, birdZ-1,
		birdX+wingspan*0.5 , birdY-wingwidth, birdZ-1
	};
	 float colors[] = {
		rand(), rand(), rand(), // More red
		rand(), rand(), rand(), // More blue
		rand(), rand(), rand()  // more green
	};
    glVertexPointer(3, GL_FLOAT, 0, verticesWing1);
    glColorPointer(3, GL_FLOAT, 0, colors);
	unsigned char fanIndices[] = {0,1,2,3,4,5,6,7,8,9};
	glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_BYTE, fanIndices);
	
    glVertexPointer(3, GL_FLOAT, 0, verticesWing2);
    glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_BYTE, fanIndices);
	
}
void drawBird(float h, float r, float x, float y, float z, float red, float g, float b){
	glColor3f(red,g,b);
	drawCylinder('y',h, r, x, y, z);
	// HEAD
	drawSphere(x,y+r,z,r*1.6,r*1.6,r*1.6); // Head
	glColor3f(.9,.9,.1); // Beak Color
	drawCone('x',-h,r*.8,x-h,y+r,z); // Beak
	glColor3f(0,0,0);
	drawSphere(x-r,y+1.7*r,z-r,r*.5); // EYES
	drawSphere(x-r,y+1.7*r,z+r,r*.5); // EYES
	drawWings(x,y-h*.1,z,2*h,r);
}
void drawBird(float h, float r, float x, float y, float z){
	drawBird(h,r,x,y,z,1,0,0);
}
// Drawing routine.
void drawScene(void)
{
  srand(time(NULL));
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  
	glColor3f(0,1,0);
	glBegin(GL_POLYGON);
		glVertex3f(-100.0,0.0,-25);
		glVertex3f(100.0,0.0,-25);
		glVertex3f(100.0,-100.0,-25);
		glVertex3f(-100.0,-100.0,-25);
	glEnd();
  glColor3f(0,0,0);
  //drawVertHelix(3,.3);
  //drawVertHelix(5,1);
  drawElephant(10,-10,0,-12);
  drawBird(4,1,7,7,-10);
  glRasterPos3f(-20,11,-10);
  writeBitmapString(GLUT_BITMAP_HELVETICA_12 ,"The elephant just wants to fly...He's no Dumbo");
  glFlush();
}

// Initialization routine.
void setup(void) 
{

  glClearColor(0, 1.0, 1.0, 0.0);
  //Followed Guha's framework for using vertex and color arrays
   // Enable two vertex arrays: co-ordinates and color.
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   
	srand(time(NULL));
}
// OpenGL window reshape routine.
void resize(int w, int h)
{
	WIDTH=(GLsizei)w;
	HEIGHT=(GLsizei)h;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if(ifOrtho){
	  glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);
  } else {
	  glFrustum(-10.0,10.0,-10.0,10.0,5,30.0);
  }
  glMatrixMode(GL_MODELVIEW);
}
// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
  switch(key) 
  {
	case 'w':
		isWire = !isWire;
		if(isWire) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glutPostRedisplay();
		break;
	case 'v':
		ifOrtho=!ifOrtho;
		resize(WIDTH,HEIGHT);
		glutPostRedisplay();
		break;
    case 27:
      exit(0);
      break;
    default:
      break;
  }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
  cout << "Interaction:" << endl;
  cout << "\t w: Toggle Wire Frame Mode" << endl;
  cout << "\t v: Toggle View (Ortho/Frustum)" << endl;
}

// Main routine.
int main(int argc, char **argv) 
{
  printInteraction();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100); 
  glutCreateWindow("Kevin Aziz CIS425 HW1 - Animal Scene");
  setup(); 
  glutDisplayFunc(drawScene); 
  glutReshapeFunc(resize);  
  glutKeyboardFunc(keyInput);
  glutMainLoop(); 
  
  return 0;  
}


