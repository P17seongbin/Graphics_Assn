#include "RenderManager.h"
#include "State.h"
#include "Const.h"
using namespace glm;

static void errorCallback(int errorCode, const char* errorDescription)
{
	fprintf(stderr, "Error: %s\n", errorDescription);
}

/**
 * @brief ObjLoader에서 Load하고 VBO에 등록까지 마친 mesh의 Offset과 ID를 입력하는 함수
 * @param GLuint ID : Mesh의 ID, 각 오브젝트에 사전에 정의한 ID를 입력해야 합니다.
 * @param UnitMesh mesh : 단일 Mesh 관련 정보를 담고 있는 struct입니다.
 * @return 정상적으로 등록 되었는가를 나타냅니다.
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
* @brief 생성자
* @param State* state: 현재 '상태'를 참고할 State 클래스를 가리키는 포인터.
* @todo 초기화 실패시 행동양식 개선 필요.
*/
RenderManager::RenderManager(State* state, GLFWwindow* &win)
{
	BGColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	WireColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glfwSetErrorCallback(errorCallback);
	// GLFW 초기화
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW 초기화 실패\n");
	}
	
	StateRef = state;
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x 안티에일리어싱
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3 을 쓸 겁니다
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// 새창을 열고, OpenGL 컨텍스트를 생성

	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "GLFW 윈도우를 여는데 실패했습니다. GLFW 3.3을 지원하지 않는 GPU를 사용할 가능성이 있습니다.");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window); // GLEW 초기화
	glewExperimental = true; // 코어 프로파일을 위해 필요함
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}
	win = window;

}

/**
* @brief 전달된 모든 오브젝트를 Render하는 함수입니다.
* @param UnitRequest reqinfo: 오브젝트의 ID, 좌표, 회전 방향 정보를 담고 있습니다.
* @return 정상적으로 Render 되었는지를 나타냅니다.
* @todo mesh 를 map에서 찾는 과정에서 map에 원하는 정보가 없을때 예외처리
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
			// Hidden Line Removal을 위한 것
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//enable wireframe mode	
			//glEnable(GL_POLYGON_OFFSET_FILL);
			glDrawArrays(GL_TRIANGLES, offset/5, mesh.len); // 버텍스 0에서 시작해서; 총 3개의 버텍스로 -> 하나의 삼각형
			//glDisable(GL_POLYGON_OFFSET_FILL);
		}

		glUniform4f(colorID, WireColor.r, WireColor.g, WireColor.b, WireColor.a);
		// 삼각형 그리기!
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//enable wireframe mode	
		glDrawArrays(GL_TRIANGLES, offset / 5, mesh.len); // 버텍스 0에서 시작해서; 총 3개의 버텍스로 -> 하나의 삼각형

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
