#include "RenderManager.h"
using namespace glm;

static void errorCallback(int errorCode, const char* errorDescription)
{
	fprintf(stderr, "Error: %s\n", errorDescription);
}

/**
 * @brief ObjLoader���� Load�ϰ� VAO�� ��ϱ��� ��ģ mesh�� Offset�� ID�� �Է��ϴ� �Լ�
 * @param GLuint ID : Mesh�� ID, �� ������Ʈ�� ������ ������ ID�� �Է��ؾ� �մϴ�.
 * @param UnitMesh mesh : ���� Mesh ���� ������ ��� �ִ� struct�Դϴ�.
 * @return ���������� ��� �Ǿ��°��� ��Ÿ���ϴ�.
 */
bool RenderManager::enqueueMesh(UnitMesh mesh)
{
	printf("\n%d", mesh.ID);
	std::map<GLuint, UnitMesh>::iterator it = Meshqueue.find(mesh.ID);
	if (it == Meshqueue.end())
	{
		Meshqueue.insert(std::pair<GLuint, UnitMesh>(mesh.ID, mesh));
		return true;
	}
	else return false;
}
/**
* @brief ������
* @param State* state: ���� '����'�� ������ State Ŭ������ ����Ű�� ������.
* @todo �ʱ�ȭ ���н� �ൿ��� ���� �ʿ�.
*/
RenderManager::RenderManager(State* state, GLFWwindow* &win)
{
	BGColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	WireColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glfwSetErrorCallback(errorCallback);
	// GLFW �ʱ�ȭ
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW �ʱ�ȭ ����\n");
	}

	StateRef = state;
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x ��Ƽ���ϸ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3 �� �� �̴ϴ�
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// ��â�� ����, OpenGL ���ؽ�Ʈ�� ����

	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "GLFW �����츦 ���µ� �����߽��ϴ�. GLFW 3.3�� �������� �ʴ� GPU�� ����� ���ɼ��� �ֽ��ϴ�.");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window); // GLEW �ʱ�ȭ
	glewExperimental = true; // �ھ� ���������� ���� �ʿ���
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}
	win = window;

}


/**
* @brief ���� ������Ʈ�� Render�ϴ� �Լ��Դϴ�.
* @param UnitRequest reqinfo: ������Ʈ�� ID, ��ǥ, ȸ�� ���� ������ ��� �ֽ��ϴ�.
* @return ���������� Render �Ǿ������� ��Ÿ���ϴ�.
* @todo mesh �� map���� ã�� �������� map�� ���ϴ� ������ ������ ����ó��
*/
bool RenderManager::drawObject(UnitRequest reqinfo)
{
	std::map<GLuint, UnitMesh>::iterator it = Meshqueue.find((GLuint)reqinfo.PolygonID);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	if (it != Meshqueue.end())
	{
		UnitMesh mesh = Meshqueue[reqinfo.PolygonID];
		glBindBuffer(GL_ARRAY_BUFFER, VAO);
		//vertex shader���� �̸� "MVP"�� uniform variable�� location���� ����*************************************************�������� �߰��� ��
		GLuint matrixID = glGetUniformLocation(StateRef->getShaderID(), "MVP");
		GLuint colorID = glGetUniformLocation(StateRef->getShaderID(),"vertexColor");

		glClearColor(BGColor.r, BGColor.g, BGColor.b, BGColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// ������ ù��° �Ӽ���(attribute) : ���ؽ���
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(
				0,                  // 0��° �Ӽ�(attribute). 0 �� �� Ư���� ������ ������, ���̴��� ���̾ƿ�(layout)�� �ݵ�� ���߾�� �մϴ�.
				3,                  // ũ��(size)
				GL_FLOAT,           // Ÿ��(type)
				GL_FALSE,           // ����ȭ(normalized)?
				0,                  // ���� ��� ���� ����(stride)
				(void*)mesh.offset            // �迭 ������ ������(offset; �ű�� ��)
			);


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////�������� �߰��� mvp���� ����
			GLuint width = 50; //temporary variables for setting aspect ratio
			GLuint height = 50;
			mat4 Model = reqinfo.RotationMatrix * reqinfo.PositionMatrix; //Model Matrix
			mat4 View = lookAt(
				glm::vec3(4, 3 ,3), // ī�޶�� (4,3,3) �� �ִ�. ���� ��ǥ����
				glm::vec3(0, 0, 0), // �׸��� ī�޶� ������ ����
				glm::vec3(0, 1, 0)  // �Ӹ��� �����̴� (0,-1,0 ���� �غ���, ������ �����̴�)
			);
			mat4 Projection = perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
			mat4 mvp = Projection * View * Model;

			glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);//sending mvp information to vertex shader
											  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////�������� �߰��� mvp����
			glUseProgram(StateRef->getShaderID());

			if (StateRef->IsHiddenLineRemovalMode())
			{
				glUniform4f(colorID, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
				// Hidden Line Removal�� ���� ��
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//enable wireframe mode	
				glEnable(GL_POLYGON_OFFSET_FILL);
				glDrawArrays(GL_TRIANGLES, 0, mesh.len); // ���ؽ� 0���� �����ؼ�; �� 3���� ���ؽ��� -> �ϳ��� �ﰢ��
				glDisable(GL_POLYGON_OFFSET_FILL);
			}

			glUniform4f(colorID, WireColor.r,WireColor.g,WireColor.b,WireColor.a);
			// �ﰢ�� �׸���!
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//enable wireframe mode	
			glDrawArrays(GL_TRIANGLES, 0, mesh.len); // ���ؽ� 0���� �����ؼ�; �� 3���� ���ؽ��� -> �ϳ��� �ﰢ��

			glfwSwapBuffers(window);
			glfwPollEvents();
			glDisableVertexAttribArray(0);

	}
	else return false;
}
/*
vector<string> mlist;
string spath = "Meshlist.txt";
const char* path = spath.c_str();

FILE * file = fopen(path, "r");
if (file == NULL) {
printf("Impossible to open the file !\n");
}

while (true) {
string line;
// read the first word of the line
int res = fscanf(file, "%s", &line);
if (res == EOF)
break; // EOF = End Of File. Quit the loop.
else
{
mlist.push_back(line);
}
Loader = new ObjLoader(mlist);
}
*/