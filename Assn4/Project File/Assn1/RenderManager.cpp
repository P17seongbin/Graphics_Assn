#include "RenderManager.h"
#include "State.h"
#include "Const.h"
using namespace glm;

static void errorCallback(int errorCode, const char* errorDescription)
{
	fprintf(stderr, "Error: %s\n", errorDescription);
}

/**
 * @brief ObjLoader���� Load�ϰ� VBO�� ��ϱ��� ��ģ mesh�� Offset�� ID�� �Է��ϴ� �Լ�
 * @param GLuint ID : Mesh�� ID, �� ������Ʈ�� ������ ������ ID�� �Է��ؾ� �մϴ�.
 * @param UnitMesh mesh : ���� Mesh ���� ������ ��� �ִ� struct�Դϴ�.
 * @return ���������� ��� �Ǿ��°��� ��Ÿ���ϴ�.
 */
bool RenderManager::enqueueMesh(UnitMesh mesh)
{
	//printf("\n%d", mesh.ID);
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
	BGColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
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
* @brief ���޵� ��� ������Ʈ�� Render�ϴ� �Լ��Դϴ�.
* @param UnitRequest reqinfo: ������Ʈ�� ID, ��ǥ, ȸ�� ���� ������ ��� �ֽ��ϴ�.
* @return ���������� Render �Ǿ������� ��Ÿ���ϴ�.
* @todo mesh �� map���� ã�� �������� map�� ���ϴ� ������ ������ ����ó��
*/
bool RenderManager::drawObject(std::vector<UnitRequest> &reqlist)
{

	//std::map<GLuint, UnitMesh>::iterator it = Meshqueue.find((GLuint)reqinfo.PolygonID);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint matrixID = glGetUniformLocation(StateRef->getShaderID(), "MVP");
	GLuint colorID = glGetUniformLocation(StateRef->getShaderID(), "vertexColor");
	GLuint textureID = glGetUniformLocation(StateRef->getShaderID(), "Texture");
	glClearColor(BGColor.r, BGColor.g, BGColor.b, BGColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(StateRef->getShaderID());

	glBindVertexArray(VAO);

	for (int i = 0; i < reqlist.size(); i++)
	{
		glEnableVertexAttribArray(0);

		glEnableVertexAttribArray(1);
		UnitRequest reqinfo = reqlist[i];
		UnitMesh mesh = Meshqueue[(GLuint)reqinfo.PolygonID];
		glUniform1i(textureID,0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh.TextureID);
		int offset = mesh.offset;
	//	glBindTexture(GL_TEXTURE_2D,mesh.TextureID);
		//printf("%d %d %d\n", mesh.ID, mesh.offset, mesh.len);

		mat4 Model = reqinfo.PositionMatrix * reqinfo.RotationMatrix; //Model Matrix
		mat4 View = getLookAt();
		mat4 Projection = perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
		mat4 mvp = Projection * View * Model;

		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);//sending mvp information to vertex shader

		if (StateRef->IsHiddenLineRemovalMode())
		{
			glUniform4f(colorID, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
			// Hidden Line Removal�� ���� ��
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//enable wireframe mode	
			//glEnable(GL_POLYGON_OFFSET_FILL);
			glDrawArrays(GL_TRIANGLES, offset/5, mesh.len); // ���ؽ� 0���� �����ؼ�; �� 3���� ���ؽ��� -> �ϳ��� �ﰢ��
			//glDisable(GL_POLYGON_OFFSET_FILL);
		}

		glUniform4f(colorID, WireColor.r, WireColor.g, WireColor.b, WireColor.a);
		// �ﰢ�� �׸���!
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//enable wireframe mode	
		glDrawArrays(GL_TRIANGLES, offset / 5, mesh.len); // ���ؽ� 0���� �����ؼ�; �� 3���� ���ؽ��� -> �ϳ��� �ﰢ��

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		glfwPollEvents();
	}

	glfwSwapBuffers(window);

	//}
	return true;
	//	else return false;
}
glm::mat4 RenderManager::getLookAt()
{
	return StateRef->getLookAt();

}
