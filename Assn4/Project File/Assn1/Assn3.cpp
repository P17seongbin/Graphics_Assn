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

	printf("������ ����Ǿ����ϴ�. �ٽ� �����Ͻ÷��� ������ �����Ͻ� �� �ٽ� �������ּ���.");

}
