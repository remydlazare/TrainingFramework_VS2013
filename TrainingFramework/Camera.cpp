#include "stdafx.h"
#include "Camera.h"
#define PI 3.141592

Camera::Camera()
{
	mPosition.x = 0.0f;		mPosition.y = 0.0f;		mPosition.z = -0.9f;
	mTarget.x = 0.0f;		mTarget.y = 0.0f;		mTarget.z = 1.0f;
	mFOV = 45 * PI / 180;	mAspect = 4.0f / 3.0f;	mNearPane = 0.1f;	mFarPane = 100.0f;
}

Camera::~Camera()
{
}

Matrix Camera::GetView()
{
	Vector3 zaxis = (mPosition - mTarget).Normalize();
	Vector3 xaxis = (mUp.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();
	mRotation.SetIdentity();
	mRotation.m[0][0] = xaxis.x; mRotation.m[0][1] = xaxis.y; mRotation.m[0][2] = xaxis.z;
	mRotation.m[1][0] = yaxis.x; mRotation.m[1][1] = yaxis.y; mRotation.m[1][2] = yaxis.z;
	mRotation.m[2][0] = zaxis.x; mRotation.m[2][1] = zaxis.y; mRotation.m[2][2] = zaxis.z;

	mTranslation.SetIdentity();
	mTranslation.SetTranslation(mPosition);

	mWorld = mRotation * mTranslation;

	Matrix RotationInverse = mRotation, TranslationInverse = mTranslation;
	RotationInverse.Transpose();
	TranslationInverse.m[3][0] = -TranslationInverse.m[3][0];
	TranslationInverse.m[3][1] = -TranslationInverse.m[3][1];
	TranslationInverse.m[3][2] = -TranslationInverse.m[3][2];
	mView = TranslationInverse * RotationInverse;
	return mView;
}

Matrix Camera::GetProjection()
{
	mProjection.SetPerspective(mFOV, mAspect, mNearPane, mFarPane);
	return mProjection;
}

void Camera::MoveLeft(float deltaTime)
{
	Vector3 deltaMove = mUp.Cross((mPosition - mTarget)).Normalize()*deltaTime*mMoveSpeed;
	mPosition -= deltaMove;
	mTarget -= deltaMove;
	
}

void Camera::MoveRight(float deltaTime)
{
	Vector3 deltaMove = mUp.Cross((mPosition - mTarget)).Normalize()*deltaTime*mMoveSpeed;
	mPosition += deltaMove;
	mTarget += deltaMove;
}

void Camera::MoveForward(float deltaTime)
{
	Vector3 deltaMove = (mPosition - mTarget).Normalize()*deltaTime*mMoveSpeed;
	mPosition -= deltaMove;
	mTarget -= deltaMove;
}

void Camera::MoveBackward(float deltaTime)
{
	Vector3 deltaMove = (mPosition - mTarget).Normalize()*deltaTime*mMoveSpeed;
	mPosition += deltaMove;
	mTarget += deltaMove;
}

void Camera::RotateRight(float deltaTime)
{
	float rotateAngle = deltaTime * mRotateSpeed;
	Vector4 localTarget = Vector4(0, 0, -(mPosition - mTarget).Length(), 1);
	Vector4 localNewTarget = localTarget * SetRotationAroundY(rotateAngle);
	Vector4 worldNewTarget = localNewTarget * mWorld;
	mTarget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::RotateLeft(float deltaTime)
{
	float rotateAngle = deltaTime * mRotateSpeed;
	Vector4 localTarget = Vector4(0, 0, -(mPosition - mTarget).Length(), 1);
	Vector4 localNewTarget = localTarget * SetRotationAroundY(-rotateAngle);
	Vector4 worldNewTarget = localNewTarget * mWorld;
	mTarget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::RotateUp(float deltaTime)
{
	float rotateAngle = deltaTime * mRotateSpeed;
	Vector4 localTarget = Vector4(0, 0, -(mPosition - mTarget).Length(), 1);
	Vector4 localNewTarget = localTarget * SetRotationAroundX(-rotateAngle);
	Vector4 worldNewTarget = localNewTarget * mWorld;
	mTarget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::RotateDown(float deltaTime)
{
	float rotateAngle = deltaTime * mRotateSpeed;
	Vector4 localTarget = Vector4(0, 0, -(mPosition - mTarget).Length(), 1);
	Vector4 localNewTarget = localTarget * SetRotationAroundX(rotateAngle);
	Vector4 worldNewTarget = localNewTarget * mWorld;
	mTarget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

Matrix Camera::SetRotationAroundY(float angle)
{
	Matrix rotation;
	Vector4 rotateAxis = Vector4(0, 1, 0, 0);
	rotateAxis = rotateAxis * mView;
	return rotation.SetRotationAngleAxis(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);
}

Matrix Camera::SetRotationAroundX(float angle)
{
	Matrix rotation;
	Vector4 rotateAxis = Vector4(1, 0, 0, 0);
	rotateAxis = rotateAxis * mView;
	return rotation.SetRotationAngleAxis(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);
}