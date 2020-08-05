#pragma once
#include "..\Utilities\utilities.h"
class Texture
{
public:
	int ID;
	GLuint m2DTextureId, mCubeTextureId;
	Texture(int ID, const char * fileTexture, const char * mode);
	Texture(int ID,  char* TextureFiles[], const char* mode);
	void Init2DTexture(const char* fileModel, const char * mode);
	void InitCubeTexture( char* textureFiles[], const char* mode);
	void Bind();
	void Unbind();
	~Texture();
};

