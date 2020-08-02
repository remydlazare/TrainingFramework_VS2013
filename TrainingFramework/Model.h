#pragma once
#include "..\Utilities\utilities.h"
class Model
{
public:
	int ID;
	GLuint mVBO;
	GLuint mIBO;
	int mNumberOfIndices;
	void Init(const char * modelFile);
	Model(int ID, const char * modelFile);
	~Model();
};