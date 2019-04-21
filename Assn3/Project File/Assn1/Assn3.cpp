#include "State.h"
#include "ObjLoader.hpp"
// �̰��� �츮�� ���ؽ� ���۸� ����ŵ�ϴ�.
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
	// GLFW �ʱ�ȭ
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW �ʱ�ȭ ����\n");
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
	
	} // ���� ESC Ű�� ���������� Ȥ�� â�� �������� üũ üũ
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}
