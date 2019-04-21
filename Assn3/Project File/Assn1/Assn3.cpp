#include "State.h"
#include "ObjLoader.hpp"
// 이것이 우리의 버텍스 버퍼를 가리킵니다.
GLuint vertexbuffer;
GLuint VertexArrayID;
State state;
using namespace glm;
static void errorCallback(int errorCode, const char* errorDescription)
{
	fprintf(stderr, "Error: %s\n", errorDescription);
}

int main(int argc, char **argv)
{
	glfwSetErrorCallback(errorCallback);
	// GLFW 초기화
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW 초기화 실패\n");
	}
	GLFWwindow* window;
	
	RenderManager tRM(&state,window);

	GLuint programID = LoadShaders("vertex.glsl", "fragment.glsl");
	state.setShaderID(programID);

	ObjLoader tObjLoader(&tRM);

	int x = 0;
	do {
		mat4 pos(1.0f), dir(1.0f);
		pos = glm::translate(pos, vec3(x - 10, 0, 0));
		UnitRequest tr;
		tr.RotationMatrix = dir;
		tr.PositionMatrix = pos;
		tr.PolygonID = 0;
		tRM.drawObject(tr);
		
		x++;
		x %= 20;
	
	} // 만약 ESC 키가 눌러졌는지 혹은 창이 닫혔는지 체크 체크
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}
