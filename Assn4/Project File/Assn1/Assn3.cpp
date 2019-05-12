#include "State.h"
//#include "IObject.h"
#include "ObjLoader.hpp"
#include "GameManager.h"
#include "Player.h"
#include "ball.h"
#include "RenderChannel.h"

#include <ctime>

using namespace glm;

int main(int argc, char **argv)
{
	State state;

	srand((unsigned int)time(0));
	GLFWwindow* window;	

	RenderManager tRM(&state,window);
	RenderChannel tC(&tRM,window);



	ObjLoader tObjLoader(&tRM);
	glutInit(&argc, argv);

	//GLuint matrixID = glGetUniformLocation(programID, "MVP");
	GameManager GM(window,&tC,&state);

	GM.Update(window);

	printf("게임이 종료되었습니다. 다시 시작하시려면 게임을 종료하신 후 다시 시작해주세요.");

}
