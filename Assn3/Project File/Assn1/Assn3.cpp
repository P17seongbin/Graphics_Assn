#include "State.h"
//#include "IObject.h"
#include "ObjLoader.hpp"
#include "GameManager.h"
#include "AIPlayer.h"
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

	//vertex shader���� �̸� "MVP"�� uniform variable�� location���� ����*************************************************�������� �߰��� ��
	//GLuint matrixID = glGetUniformLocation(programID, "MVP");
	GameManager GM(window,&tC);//���� �Ⱦ�
	
	AIPlayer* eevee = new AIPlayer(&tC);
	//Ball* ball = new Ball(&tC);
	//Ball* eevee = new Ball();


	bool IsPressed = false;

	float x = 0;
	do {
		eevee->update(window, 0);
		eevee->DrawSelf();
		tC.DrawAll();

		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && !IsPressed)
		{
			IsPressed = true;
			state.ToggleHiddenLineRemovalMode();
		}
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE)
			IsPressed = false;

	} // ���� ESC Ű�� ���������� Ȥ�� â�� �������� üũ üũ
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}
