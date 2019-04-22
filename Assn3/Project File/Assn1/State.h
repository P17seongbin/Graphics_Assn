#pragma once
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
// GLFW 도 포함
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>



GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

/**
 * @brief 현재 게임 상황을 저장하는 State Machine
 */
enum CameraMovement { CAM_FRONT, CAM_BACK, CAM_LEFT, CAM_RIGHT };

class State
{
public:

	State();

	GLuint getCameraID() { return CameraID;	}
	GLuint getShaderID() { return ShaderID; }

	int getPlayerScore() { return PlayerScore; }
	int getAIScore() { return AIScore;  }

	void setPlayerScore(int score) { PlayerScore = score; }
	void setAIScore(int score) { AIScore = score; }

	void addPlayerScore(int ds) { PlayerScore += ds; }
	void addAIScore(int ds) { AIScore += ds; }

	void setCameraID(GLuint ID) { CameraID = ID; }
	void setShaderID(GLuint ID) { ShaderID = ID; }

	glm::mat4 getLookAt();

	bool CameraControl(CameraMovement dir);	
	bool IsHiddenLineRemovalMode() { return HLR; }
	void ToggleHiddenLineRemovalMode() { HLR = !HLR; }
	
	void UpdatePlayerPos(glm::vec3 p);
	void UpdatePlayerDir(float d) { PlayerDir = d; }

private:
	GLuint CameraID;
	GLuint ShaderID;

	glm::vec3 PlayerPos;
	float PlayerDir;

	int PlayerScore;
	int AIScore;
	bool HLR = false;//Hidden Line Removal
	glm::vec3 CamPos;

};

struct UnitRequest
{
	unsigned int PolygonID;
	glm::mat4 PositionMatrix;
	glm::mat4 RotationMatrix;
};
struct UnitMesh
{
	GLuint ID;
	GLuint offset;
	unsigned int len;
};
