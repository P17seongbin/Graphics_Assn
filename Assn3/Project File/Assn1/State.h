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
enum CameraMovement { CAM_FRONT, CAM_BACK, CAM_LEFT, CAM_RIGHT };

class State
{
public:
	GLuint getCameraID() {		return CameraID;	}
	GLuint getShaderID() { return ShaderID; }

	int getPlayerScore() { return PlayerScore; }
	int getAIScore() { return AIScore;  }

	void setPlayerScore(int score) { PlayerScore = score; }
	void setAIScore(int score) { AIScore = score; }

	void addPlayerScore(int ds) { PlayerScore += ds; }
	void addAIScore(int ds) { AIScore += ds; }

	bool setCameraID(GLuint ID) { CameraID = ID; }
	bool setShaderID(GLuint ID) { ShaderID = ID; }

	bool CameraControl(CameraMovement dir);	
	
private:
	GLuint CameraID;
	GLuint ShaderID;
	int PlayerScore;
	int AIScore;
};
