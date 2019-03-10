#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h> 
#include <GL/glfw3.h>
#include "System.h"

using namespace std;
void display(void);
void myReshape(int w, int h);
void renderScene(void) 
{

} 

int main(int argc, char **argv)
{  
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Example");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMainLoop();



}
void myReshape(int w, int h) 
{
	glLoadIdentity(); //Stack matrix = I
	glViewport(0, 0, w, h); 
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0.0, 1.0, 1.0); 
	glRectf(10.0, 10.0, 90.0, 90.0); 
	glutSwapBuffers();
}