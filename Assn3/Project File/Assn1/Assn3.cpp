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
/*
	std::vector< glm::vec3 > vertices;
	bool res = loadOBJ("Eevee.obj", vertices);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	// �Ʒ��� ��ɾ���� �츮�� "vertexbuffer" ���ۿ� ���ؼ� �ٷ�̴ϴ�
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// �츮�� ���ؽ����� OpenGL�� �Ѱ��ݴϴ�
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	//vertex shader���� �̸� "MVP"�� uniform variable�� location���� ����*************************************************�������� �߰��� ��
	GLuint matrixID = glGetUniformLocation(programID, "MVP");*/
	int x = 0;
	do {
		mat4 pos(1.0f), dir(1.0f);
		pos = glm::translate(pos, vec3(x - 10, 0, 0));
		UnitRequest tr;
		tr.RotationMatrix = dir;
		tr.PositionMatrix = pos;
		tr.PolygonID = 0;
		tRM.drawObject(tr);
		/*
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// ������ ù��° �Ӽ���(attribute) : ���ؽ���
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // 0��° �Ӽ�(attribute). 0 �� �� Ư���� ������ ������, ���̴��� ���̾ƿ�(layout)�� �ݵ�� ���߾�� �մϴ�.
			3,                  // ũ��(size)
			GL_FLOAT,           // Ÿ��(type)
			GL_FALSE,           // ����ȭ(normalized)?
			0,                  // ���� ��� ���� ����(stride)
			(void*)0            // �迭 ������ ������(offset; �ű�� ��)
		);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////�������� �߰��� mvp���� ����
		GLuint width=50; //temporary variables for setting aspect ratio
		GLuint height=50;
		mat4 Model = mat4(1.0f); //identity matrix
		mat4 View = lookAt(
			glm::vec3(4, 3, 3), // ī�޶�� (4,3,3) �� �ִ�. ���� ��ǥ����
			glm::vec3(0, 0, 0), // �׸��� ī�޶� ������ ����
			glm::vec3(0, 1, 0)  // �Ӹ��� �����̴� (0,-1,0 ���� �غ���, ������ �����̴�)
		);;
		mat4 Projection=perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
		mat4 mvp = Projection * View * Model;

		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);//sending mvp information to vertex shader
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////�������� �߰��� mvp���� ��


		glUseProgram(programID);
		// �ﰢ�� �׸���!
		glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // ���ؽ� 0���� �����ؼ�; �� 3���� ���ؽ��� -> �ϳ��� �ﰢ��
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//enable wireframe mode
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		*/
		x++;
		x %= 20;
	
	} // ���� ESC Ű�� ���������� Ȥ�� â�� �������� üũ üũ
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}
