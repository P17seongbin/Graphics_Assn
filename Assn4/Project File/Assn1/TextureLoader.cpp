#include "State.h"
#include <string>
#include <vector>
#include <sstream>


GLuint loadDDS(const char* path)
{
	GLuint textureID = -1;
	glGenTextures(1, &textureID);

	unsigned char DDSheader[128];//DDSHeader�� 128bytes, 32DWORDS
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

	//linearsize�� mipmap�� ���� ū �������� ũ�⸦ ��Ÿ���Ƿ�, mipmap�� 1�ܰ谡 �ƴϸ� �� ũ���� 2��� �ϸ� �����Ӱ� ��� mipmap�� load�� �� �ֽ��ϴ�.
	bufsize = (MipmapCount > 1) ? linearsize * 2 : linearsize;
	databuffer = new unsigned char[bufsize];
	fread(databuffer, 1, bufsize, file);
	
	//�� �о����� ������ �ݽ��ϴ�.
	fclose(file);

	//�����͸� �о����� �̸� OpenGL�� �Ѱ��ݴϴ�.

	glGenTextures(1, &textureID);
	// ���Ӱ� ������ �ؽ�ó�� bind�մϴ�.
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//wall DDS file(DXT3)�� blocksize�� 16(������)
	int blockSize = 16;
	int offset = 0;
	int size = linearsize;
	//�־��� �ؽ��İ� ���簢���̶�� �����մϴ�.
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