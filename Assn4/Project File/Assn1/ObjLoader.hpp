//Reference : http://www.opengl-tutorial.org/kr/beginners-tutorials/tutorial-7-model-loading/
#pragma once
#include "State.h"
#include "RenderManager.h"
#include <vector>
#include <map>
#include "Const.h"

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

	std::vector<float> out_vertices(0);
	//Obj������ �ణ �����ؼ� Texture File�� �̸��� t��� prefix�� �Բ� ������.
	//����Ʈ�� ��� OBJ������ �ϳ��ϳ� �ε�����
	for (int i = 0; i < list.size(); i++)
	{
		std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		std::vector< glm::vec3 > temp_vertices;
		std::vector<glm::vec2> temp_uvs;
		UnitMesh tmesh;
		tmesh.ID = i;
		tmesh.offset = out_vertices.size();
		int len = 0;

		string t = list[i];
		t.append(".obj");
		const char* path = t.c_str();
		FILE* file;
		if (path[0] == '#')
			file = fopen(path + 1, "r");
		else
			file = fopen(path, "r");

		if (file == NULL) {
			printf("Impossible to open the file %s !\n", path);
			return false;
		}
		tmesh.TextureID = -1;
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
			else if (strcmp(lineHeader, "tdds") == 0)
			{
				char* path = new char[128];
				fscanf(file, "%s", path);
				tmesh.TextureID = (GLuint)loadDDS(path);
			}
			else if (strcmp(lineHeader, "tbmp") == 0)
			{
				char* path = new char[128];
				fscanf(file, "%s", path);
				tmesh.TextureID = (GLuint)loadBMP(path);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "f") == 0) {

				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				if (path[0] != '#')
				{
					int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
					if (matches != 9) {
						printf("File can't be read by this parser\n");
						return false;
					}
				}
				else
				{
					int matches = fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
					if (matches != 6) {
						printf("File can't be read by this parser\n");
						return false;
					}
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
			}
		}

		// For each vertex of each triangle  (�� �ﰢ���� �� �������� ��ȸ�մϴ�.) 
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			//save vertex data
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			out_vertices.push_back(vertex.x);
			out_vertices.push_back(vertex.y);
			out_vertices.push_back(vertex.z);

			//save uv data
			unsigned int uvindex = uvIndices[i];
			glm::vec2 uv = temp_uvs[uvindex - 1];
			out_vertices.push_back(uv.x);
			out_vertices.push_back(uv.y);
			len++;
		}
		tmesh.len = len;
		printf("%d %d %d %d\n", tmesh.ID, tmesh.len, tmesh.offset, tmesh.TextureID	);
		RM->enqueueMesh(tmesh);
	}
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &vertexbuffer);
	// �Ʒ��� ��ɾ���� "vertexbuffer" ���ۿ� ���ؼ� �ٷ�ϴ�.
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Vertex�� OpenGL�� �Ѱ��ݴϴ�
	glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(float), &out_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		5 * sizeof(float),
		(void*)(3 * sizeof(float))
	);

	// ������ ù��° �Ӽ���(attribute) : ���ؽ���
	glVertexAttribPointer(
		0,                  // 0��° �Ӽ�(attribute)
		3,                  // ũ��(size)
		GL_FLOAT,           // Ÿ��(type)
		GL_FALSE,           // ����ȭ(normalized)?
		5 * sizeof(float), // ���� ��� ���� ����(stride)
		(void*)0           // �迭 ������ ������(offset; �ű�� ��)
	);

	RM->setVAO(VAO);
	RM->setVBO(vertexbuffer);
	return true;
}