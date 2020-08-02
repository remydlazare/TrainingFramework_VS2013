#pragma once
#include "..\Utilities\Math.h"

class Camera
{
public:
	GLfloat mMoveSpeed = 5, mRotateSpeed = 5;
	GLfloat mFOV, mAspect, mNearPane, mFarPane;

	Matrix mWorld, mView, mProjection;
	Matrix mRotation, mTranslation;
	Matrix mRx, mRy, mRz;
	Vector3 mPosition, mTarget; 
	Vector3 mUp = Vector3(0.0f, 1.0f, 0.0f);
	
	Camera();
	~Camera();
	Matrix GetView();
	Matrix GetProjection();
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void MoveForward(float deltaTime);
	void MoveBackward(float deltaTime);
	void RotateRight(float deltaTime);
	void RotateLeft(float deltaTime);
	void RotateUp(float deltaTime);
	void RotateDown(float deltaTime);
	Matrix SetRotationAroundY(float angle);
	Matrix SetRotationAroundX(float angle);

};

