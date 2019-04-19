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
/*
	std::vector< glm::vec3 > vertices;
	bool res = loadOBJ("Eevee.obj", vertices);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	// 아래의 명령어들은 우리의 "vertexbuffer" 버퍼에 대해서 다룰겁니다
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// 우리의 버텍스들을 OpenGL로 넘겨줍니다
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	//vertex shader에서 이름 "MVP"인 uniform variable의 location정보 저장*************************************************손주은이 추가한 줄
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
		// 버퍼의 첫번째 속성값(attribute) : 버텍스들
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // 0번째 속성(attribute). 0 이 될 특별한 이유는 없지만, 쉐이더의 레이아웃(layout)와 반드시 맞추어야 합니다.
			3,                  // 크기(size)
			GL_FLOAT,           // 타입(type)
			GL_FALSE,           // 정규화(normalized)?
			0,                  // 다음 요소 까지 간격(stride)
			(void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
		);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////손주은이 추가한 mvp설정 시작
		GLuint width=50; //temporary variables for setting aspect ratio
		GLuint height=50;
		mat4 Model = mat4(1.0f); //identity matrix
		mat4 View = lookAt(
			glm::vec3(4, 3, 3), // 카메라는 (4,3,3) 에 있다. 월드 좌표에서
			glm::vec3(0, 0, 0), // 그리고 카메라가 원점을 본다
			glm::vec3(0, 1, 0)  // 머리가 위쪽이다 (0,-1,0 으로 해보면, 뒤집어 볼것이다)
		);;
		mat4 Projection=perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
		mat4 mvp = Projection * View * Model;

		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);//sending mvp information to vertex shader
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////손주은이 추가한 mvp설정 끝


		glUseProgram(programID);
		// 삼각형 그리기!
		glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // 버텍스 0에서 시작해서; 총 3개의 버텍스로 -> 하나의 삼각형
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//enable wireframe mode
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		*/
		x++;
		x %= 20;
	
	} // 만약 ESC 키가 눌러졌는지 혹은 창이 닫혔는지 체크 체크
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}
