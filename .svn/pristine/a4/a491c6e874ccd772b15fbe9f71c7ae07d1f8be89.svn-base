#pragma once
#include "..\Utilities\Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include <vector>
#define PI 3.141592

class Object
{
private:
	
public:
	Matrix mWorld, mView, mProjection;
	Matrix mScale, mRotation, mTranslation;
	Matrix mRx, mRy, mRz;
	Model * mModel;
	Texture * mTexture;
	Shaders * mShader;

	Object();
	~Object();

	Matrix GetWVP();

	void Draw();
};

