#include "State.h"
#include "ObjLoader.hpp"
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

	float x = 0;
	do {
		tC.EnqueueRequest(0, vec3(0, 0, 0), x);
		tC.DrawAll();
		/*
		mat4 pos(1.0f), dir(1.0f);
		pos = glm::translate(pos, vec3(x - 10, 0, 0));
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
