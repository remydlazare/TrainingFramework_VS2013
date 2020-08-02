#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	int ID;
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint uvAttribute;

	int Init(char * fileVertexShader, char * fileFragmentShader);
	Shaders(int ID, char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};