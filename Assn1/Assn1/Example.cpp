#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h> 
//#include <GL/glfw3.h>
#include "System.h"

using namespace std;
void myReshape(int w, int h);
GameManager GM;
class ExampleObject : public Object
{
public:
	ExampleObject()
	{
		tag = "Example";
	}
	void Step(int dt) override//매 Step마다 이동과 움직임을 구현
	{
		//Bad Code!
		if (pos.first < 0 || pos.first > 100) speed = make_pair(speed.first * -1,speed.second);
		if (pos.second < 0 || pos.second > 100)  speed = make_pair(speed.first,speed.second * -1);
		addPos(speed.first * dt, speed.second * dt);
	}
	void onCollide(Object* other, AABB* selfAABB, AABB* otherAABB) override//지금은 충돌 안함
	{

	}
	void Draw() override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(pos.first, pos.second);
		glVertex2f(pos.first, pos.second + size.first);
		glVertex2f(pos.first + size.second, pos.second + size.first);
		glVertex2f(pos.first + size.second, pos.second);
		glEnd();
	}
	void setSize(float x, float y) {
		size = make_pair(x, y);
	}
private:
	std::pair<float, float> size;//width,height
};

void StepCaller(int dt)
{
	GM.Step(dt);
	glutTimerFunc(16, StepCaller, 16);
	glutPostRedisplay();
}
void DrawCaller()
{
	GM.Draw();
}
void InitScene(void) 
{
	//Create Window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Example");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

} 
void RegisterCallback()
{
	glutReshapeFunc(myReshape);
	glutDisplayFunc(DrawCaller);
	glutTimerFunc(16, StepCaller, 16);
}

int main(int argc, char **argv)
{
	ExampleObject obj;
	obj.setSize(10, 10);
	obj.setSpeed(0.2,0.3);
	GM.addObject("Template",&obj);
	glutInit(&argc,argv);

	InitScene();

	RegisterCallback();
	//기타등등 시작하기 전에 필요한 것들
	//DoSomeThing();

	//앱 시작!
	glutMainLoop();
}

void myReshape(int w, int h) 
{
	glLoadIdentity(); //Stack matrix = I
	glViewport(0, 0, w, h); 
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}

