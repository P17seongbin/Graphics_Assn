#include "State.h"
//#include "IObject.h"
#include "ObjLoader.hpp"
#include "GameManager.h"
#include "Player.h"
#include "ball.h"
#include "RenderChannel.h"

// �̰��� �츮�� ���ؽ� ���۸� ����ŵ�ϴ�.
GLuint vertexbuffer;
GLuint VertexArrayID;
State state;
using namespace glm;

int main(int argc, char **argv)
{
	GLFWwindow* window;	
	RenderManager tRM(&state,window);
	RenderChannel tC(&tRM);

	GLuint programID = LoadShaders("vertex.glsl", "fragment.glsl");
	state.setShaderID(programID);
	ObjLoader tObjLoader(&tRM);

/*<<<<<<< HEAD
	GLuint matrixID = glGetUniformLocation(programID, "MVP");
	GameManager GM(window);//���� �Ⱦ�
	Player* eevee = new Player();
	//Ball* eevee = new Ball();
	

	float x = 0;
	do {
		eevee->update(window);
=======*/
	float x = 0;
	do {
		tC.EnqueueRequest(0, vec3(0, 0, 0), x);
		tC.DrawAll();
		/*
>>>>>>> f06c0ead5338f09c5d3441f5fea9033eb3b93c86
		mat4 pos(1.0f), dir(1.0f);
		pos = glm::translate(pos, eevee->getPos());
		//pos = glm::translate(pos, vec3(x - 10.0, 0, 0));
		
		UnitRequest tr;
		tr.RotationMatrix = dir;
		tr.PositionMatrix = pos;
		tr.PolygonID = 0;
		tRM.drawObject(tr);
		*/
		
		x += 0.1;
		if (x > 360) x -= 360;	
	} // ���� ESC Ű�� ���������� Ȥ�� â�� �������� üũ üũ
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}
