#pragma once
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
// GLFW 도 포함
#include <GLFW/glfw3.h>
#include <fstream>
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

/**
 * @brief 현재 게임 상황을 저장하는 State Machine
 */
class State
{
public:
	enum CameraMovement { CAM_FRONT, CAM_BACK, CAM_LEFT, CAM_RIGHT };

	GLuint getCameraID();
	GLuint getShaderID();

	int getPlayerScore();
	int getAIScore();

	bool setCameraID(GLuint ID);
	bool setShaderID(GLuint ID);

	bool CameraControl(CameraMovement dir);
	
private:
	GLuint CameraID;
	GLuint ShaderID;
	int PlayerScore;
	int AIScore;
};