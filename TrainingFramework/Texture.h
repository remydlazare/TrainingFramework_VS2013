#pragma once
#include "..\Utilities\utilities.h"
class Texture
{
public:
	int ID;
	GLuint mTextureId;
	Texture(int ID, const char * fileTexture, const char * mode);
	void Init(const char* fileModel, const char * mode);
	void Bind();
	void Unbind();
	~Texture();
};

