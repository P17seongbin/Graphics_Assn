#include "State.h"
#include <string>
#include <vector>
#include <sstream>


GLuint loadDDS(const char* path)
{
	GLuint textureID = -1;
	glGenTextures(1, &textureID);

	unsigned char DDSheader[128];//DDSHeader는 128bytes, 32DWORDS
	int width, height, imgsize, linearsize;
	int MipmapCount,Pixformat;

	unsigned char* databuffer;
	int bufsize;
	FILE * file = fopen(path, "rb");

	if (fread(DDSheader, 1, 128, file) != 128) { // If not 54 bytes read : problem
		printf("Corrupted DDS Header, Unable to read.\n");
		return false;
	}
	char t[5];
	memcpy(t, &DDSheader[0], 4);
	if (strncmp(t, "DDS ", 4) != 0)
	{
		printf("Given file %s is not DDS format!\n", path);
		fclose(file);
		return false;
	}

	width = *((int*)(&DDSheader[0x0C]));//read 4 bytes and convert as integer.
	height = *((int*)(&DDSheader[0x10]));
	linearsize = *((int*)(&DDSheader[0x14]));
	MipmapCount = *((int*)(&DDSheader[0x1C]));
	Pixformat = *((int*)(&DDSheader[0x54]));

	//linearsize는 mipmap중 가장 큰 데이터의 크기를 나타내므로, mipmap이 1단계가 아니면 그 크기의 2배로 하면 여유롭게 모든 mipmap을 load할 수 있습니다.
	bufsize = (MipmapCount > 1) ? linearsize * 2 : linearsize;
	databuffer = new unsigned char[bufsize];
	fread(databuffer, 1, bufsize, file);
	
	//다 읽었으니 파일은 닫습니다.
	fclose(file);

	//데이터를 읽었으니 이를 OpenGL에 넘겨줍니다.

	glGenTextures(1, &textureID);
	// 새롭게 생성된 텍스처를 bind합니다.
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//wall DDS file(DXT3)의 blocksize는 16(정방형)
	int blockSize = 16;
	int offset = 0;
	int size = linearsize;
	//주어진 텍스쳐가 정사각형이라고 가정합니다.
	for (int level = 0; level < MipmapCount; level++)
	{
		glCompressedTexImage2D(GL_TEXTURE_2D, level, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, width, height, 0, size, &databuffer[offset]);
		offset += size;
		size /= 4;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	delete(databuffer);

	return textureID;
}