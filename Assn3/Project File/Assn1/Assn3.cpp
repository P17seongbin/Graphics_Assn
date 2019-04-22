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
	RenderChannel tC(&tRM,window);
	GLuint programID = LoadShaders("vertex.glsl", "fragment.glsl");
	state.setShaderID(programID);
	ObjLoader tObjLoader(&tRM);


	//GLuint matrixID = glGetUniformLocation(programID, "MVP");
	GameManager GM(window,&tC,&state);//���� �Ⱦ�
	

	GM.Update(window);

	//Ball* eevee = new Ball();
	/*

	bool IsPressed = false;

	float x = 0;
	do {
		eevee->update(window);
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
		*/
}
