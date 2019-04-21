#pragma once
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
// GLFW �� ����
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>



GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

/**
 * @brief ���� ���� ��Ȳ�� �����ϴ� State Machine
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

	void setCameraID(GLuint ID) { CameraID = ID; }
	void setShaderID(GLuint ID) { ShaderID = ID; }

	bool CameraControl(CameraMovement dir);	
	bool IsHiddenLineRemovalMode() { return HLR; }
	void ToggleHiddenLineRemovalMode() { HLR = !HLR; }
	
private:
	GLuint CameraID;
	GLuint ShaderID;
	int PlayerScore;
	int AIScore;
	bool HLR = false;//Hidden Line Removal

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
