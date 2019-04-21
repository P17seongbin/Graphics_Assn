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

	//vertex shader���� �̸� "MVP"�� uniform variable�� location���� ����*************************************************�������� �߰��� ��
	//GLuint matrixID = glGetUniformLocation(programID, "MVP");
	GameManager GM(window,&tC);//���� �Ⱦ�
	Player* eevee = new Player(&tC);
	//Ball* eevee = new Ball();

	float x = 0;
	do {
		eevee->update(window);
		eevee->DrawSelf();
		tC.DrawAll();

	} // ���� ESC Ű�� ���������� Ȥ�� â�� �������� üũ üũ
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}
