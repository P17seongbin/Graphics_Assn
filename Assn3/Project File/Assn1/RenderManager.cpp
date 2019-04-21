#include "RenderManager.h"
using namespace glm;
/**
 * @brief ObjLoader에서 Load하고 VAO에 등록까지 마친 mesh의 Offset과 ID를 입력하는 함수
 * @param GLuint ID : Mesh의 ID, 각 오브젝트에 사전에 정의한 ID를 입력해야 합니다.
 * @param UnitMesh mesh : 단일 Mesh 관련 정보를 담고 있는 struct입니다.
 * @return 정상적으로 등록 되었는가를 나타냅니다.
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
* @brief 생성자
* @param State* state: 현재 '상태'를 참고할 State 클래스를 가리키는 포인터.
* @todo 초기화 실패시 행동양식 개선 필요.
*/
RenderManager::RenderManager(State* state, GLFWwindow* &win)
{
	StateRef = state;
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x 안티에일리어싱
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3 을 쓸 겁니다
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// 새창을 열고, OpenGL 컨텍스트를 생성

	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "GLFW 윈도우를 여는데 실패했습니다. Intel GPU 를 사용한다면, 3.3 지원을 하지 않습니다. 2.1 버전용 튜토리얼을 시도하세요.\n");
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
* @brief 단일 오브젝트를 Render하는 함수입니다.
* @param UnitRequest reqinfo: 오브젝트의 ID, 좌표, 회전 방향 정보를 담고 있습니다.
* @return 정상적으로 Render 되었는지를 나타냅니다.
* @todo mesh 를 map에서 찾는 과정에서 map에 원하는 정보가 없을때 예외처리
*/
bool RenderManager::drawObject(UnitRequest reqinfo)
{
	std::map<GLuint, UnitMesh>::iterator it = Meshqueue.find((GLuint)reqinfo.PolygonID);

	if (it != Meshqueue.end())
	{
		UnitMesh mesh = Meshqueue[reqinfo.PolygonID];
		glBindBuffer(GL_ARRAY_BUFFER, VAO);
		//vertex shader에서 이름 "MVP"인 uniform variable의 location정보 저장*************************************************손주은이 추가한 줄
		GLuint matrixID = glGetUniformLocation(StateRef->getShaderID(), "MVP");
			glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// 버퍼의 첫번째 속성값(attribute) : 버텍스들
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(
				0,                  // 0번째 속성(attribute). 0 이 될 특별한 이유는 없지만, 쉐이더의 레이아웃(layout)와 반드시 맞추어야 합니다.
				3,                  // 크기(size)
				GL_FLOAT,           // 타입(type)
				GL_FALSE,           // 정규화(normalized)?
				0,                  // 다음 요소 까지 간격(stride)
				(void*)mesh.offset            // 배열 버퍼의 오프셋(offset; 옮기는 값)
			);

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////손주은이 추가한 mvp설정 시작
			GLuint width = 50; //temporary variables for setting aspect ratio
			GLuint height = 50;
			mat4 Model = reqinfo.RotationMatrix * reqinfo.PositionMatrix; //identity matrix
			mat4 View = lookAt(
				glm::vec3(0, 10, 70), // 카메라는 (4,3,3) 에 있다. 월드 좌표에서
				glm::vec3(0, 0, 0), // 그리고 카메라가 원점을 본다
				glm::vec3(0, 1, 0)  // 머리가 위쪽이다 (0,-1,0 으로 해보면, 뒤집어 볼것이다)
			);
			mat4 Projection = perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
			mat4 mvp = Projection * View * Model;

			glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);//sending mvp information to vertex shader
																  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////손주은이 추가한 mvp설정

			glUseProgram(StateRef->getShaderID());
			// 삼각형 그리기!
			glDrawArrays(GL_TRIANGLES, 0, mesh.len); // 버텍스 0에서 시작해서; 총 3개의 버텍스로 -> 하나의 삼각형
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//enable wireframe mode
			glDisableVertexAttribArray(0);

			glfwSwapBuffers(window);
			glfwPollEvents();
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