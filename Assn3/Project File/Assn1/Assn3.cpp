#include "State.h"
//#include "IObject.h"
#include "ObjLoader.hpp"
#include "GameManager.h"
#include "Player.h"
#include "ball.h"
#include "RenderChannel.h"

// 이것이 우리의 버텍스 버퍼를 가리킵니다.
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

	//vertex shader에서 이름 "MVP"인 uniform variable의 location정보 저장*************************************************손주은이 추가한 줄
	//GLuint matrixID = glGetUniformLocation(programID, "MVP");
	GameManager GM(window,&tC);//아직 안씀
	Player* eevee = new Player(&tC);
	//Ball* eevee = new Ball();

	float x = 0;
	do {
		eevee->update(window);
		eevee->DrawSelf();
		tC.DrawAll();

	} // 만약 ESC 키가 눌러졌는지 혹은 창이 닫혔는지 체크 체크
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}
