//Credit: http://www.opengl-tutorial.org/kr/beginners-tutorials/tutorial-7-model-loading/
#pragma once
#include "State.h"
#include "RenderManager.h"
#include <vector>
#include <map>
using namespace std;
class ObjLoader
{
public:
	ObjLoader(RenderManager* t);
	int findID(std::string name);
	bool loadOBJ(vector<string> list);
	GLuint vertexbuffer;
private:
	std::map<std::string, GLuint> MeshID;
	RenderManager* RM;

	GLuint VertexArrayID;
};

inline ObjLoader::ObjLoader(RenderManager * t)
{
	RM = t;

	vector<string> mlist;
	string spath = "Meshlist.txt";
	const char* path = spath.c_str();

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
	}

	while (true) {
		char line[127];
		// read the first word of the line
		int res = fscanf(file, "%s", line);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		else
		{
			mlist.push_back(string(line));
		}
	}
	loadOBJ(mlist);
}

inline int ObjLoader::findID(std::string name)
{
	std::map<std::string, GLuint>::iterator it = MeshID.find(name);
	if (it != MeshID.end())
		return it->second;
	else return -1;
}

bool ObjLoader::loadOBJ(vector<string> list)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec3> out_vertices(0);


	for (int i = 0; i < list.size(); i++)
	{
		UnitMesh tmesh;
		tmesh.ID = i;
		tmesh.offset = out_vertices.size();
		int len = 0;

		string t = list[i];
		t.append(".obj");

		const char* path = t.c_str();
		FILE * file = fopen(path, "r");
		if (file == NULL) {
			printf("Impossible to open the file %s !\n", path);
			return false;
		}

		while (true) {
			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					printf("File can't be read by this parser\n");
					return false;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
			}
		}	

		// For each vertex of each triangle  (각 삼각형의 각 꼭지점을 순회합니다. ) 
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			out_vertices.push_back(vertex);
			len += 3;
		}
		tmesh.len = len;
		printf("%d %d %d", tmesh.ID, tmesh.len, tmesh.offset);
		RM->enqueueMesh(tmesh);
		

	}
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	// 아래의 명령어들은 우리의 "vertexbuffer" 버퍼에 대해서 다룰겁니다
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// 우리의 버텍스들을 OpenGL로 넘겨줍니다
	glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(glm::vec3), &out_vertices[0], GL_STATIC_DRAW);
	RM->setVAO(vertexbuffer);
	return true;
}