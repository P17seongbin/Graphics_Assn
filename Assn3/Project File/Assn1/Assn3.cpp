#include "State.h"
// �̰��� �츮�� ���ؽ� ���۸� ����ŵ�ϴ�.
GLuint vertexbuffer;
GLuint VertexArrayID;

using namespace glm;
static void errorCallback(int errorCode, const char* errorDescription)
{
	fprintf(stderr, "Error: %s\n", errorDescription);
}

int main(int argc, char **argv)
{
	glfwSetErrorCallback(errorCallback);
	// GLFW ��
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW �ʱ�ȭ ����\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x ��Ƽ���ϸ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3 �� �� �̴ϴ�
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// ��â�� ����, OpenGL ���ؽ�Ʈ�� ����
	GLFWwindow* window; // (�ļ��Ǵ� �ڵ带 ����, �� ������ ����(Global)�Դϴ�.)
	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "GLFW �����츦 ���µ� �����߽��ϴ�. Intel GPU �� ����Ѵٸ�, 3.3 ������ ���� �ʽ��ϴ�. 2.1 ������ Ʃ�丮���� �õ��ϼ���.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // GLEW �ʱ�ȭ
	glewExperimental = true; // �ھ� ���������� ���� �ʿ���
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	GLuint programID = LoadShaders("vertex.glsl", "fragment.glsl");

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	// �ؿ��� Escape Ű�� �������� ���� ������ �� �ֵ��� �� ��


	glGenBuffers(1, &vertexbuffer);
	// �Ʒ��� ��ɾ���� �츮�� "vertexbuffer" ���ۿ� ���ؼ� �ٷ�̴ϴ�
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// �츮�� ���ؽ����� OpenGL�� �Ѱ��ݴϴ�
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//vertex shader���� �̸� "MVP"�� uniform variable�� location���� ����*************************************************�������� �߰��� ��
	GLuint matrixID = glGetUniformLocation(programID, "MVP");
	do {
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//enable wireframe mode
		glDrawArrays(GL_TRIANGLES, 0, 3); // ���ؽ� 0���� �����ؼ�; �� 3���� ���ؽ��� -> �ϳ��� �ﰢ��
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} // ���� ESC Ű�� ���������� Ȥ�� â�� �������� üũ üũ
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}
