#include "stdafx.h"
#include "Texture.h"

Texture::Texture(int ID, const char * fileTexture, const char * mode)
{
	this->ID = ID;
	Init2DTexture(fileTexture, mode);
}

Texture::Texture(int ID,  char* TextureFiles[], const char* mode)
{
	this->ID = ID;
	InitCubeTexture(TextureFiles, mode);
}

void Texture::Init2DTexture(const char * fileModel, const char * mode)
{
	glGenTextures(1, &m2DTextureId);
	glBindTexture(GL_TEXTURE_2D, m2DTextureId);
	int width, height, bpp;	char* imageData = LoadTGA(fileModel, &width, &height, &bpp);
	if (bpp == 24)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);	else		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);	delete [] imageData;	if (strcmp(mode, "TILING REPEAT") == 0)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}

void Texture::InitCubeTexture( char* textureFiles[], const char* mode)
{
	glGenTextures(1, &mCubeTextureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mCubeTextureId);
	int width, height, bpp;
	char* imageData;
	for (unsigned int i = 0; i < 6; i++)
	{
		imageData = LoadTGA(textureFiles[i], &width, &height, &bpp);
		if (bpp == 24)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);		else			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}	delete[] imageData;	if (strcmp(mode, "TILING REPEAT") == 0)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m2DTextureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mCubeTextureId);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


Texture::~Texture()
{
}
