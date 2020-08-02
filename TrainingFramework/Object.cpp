#include "stdafx.h"
#include "Object.h"
#include "Camera.h"
#include "Vertex.h"
#include "Singleton.h"


Object::Object()
{
	mScale.SetIdentity();
	mTranslation.SetIdentity();
	mRx.SetIdentity();
	mRy.SetIdentity();
	mRz.SetIdentity();
}

Object::~Object()
{
}

Matrix Object::GetWVP()
{
	mView = Singleton<Camera>::GetInstance()->GetView();
	mProjection = Singleton<Camera>::GetInstance()->GetProjection();
	mRotation = mRz * mRx * mRy;
	mWorld = mScale * mRotation * mTranslation;
	return mWorld * mView * mProjection;
}

void Object::Draw()
{
	mTexture->Bind();

	int iTextureLoc = glGetUniformLocation(mShader->program, "u_texture");
	glUniform1i(iTextureLoc, 0);

	glUseProgram(mShader->program);
	Matrix mvp = GetWVP();

	GLuint MatrixID = glGetUniformLocation(mShader->program, "MVP");

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp.m[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, mModel->mVBO);
	glEnableVertexAttribArray(mShader->positionAttribute);
	glVertexAttribPointer(mShader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(mShader->uvAttribute);
	glVertexAttribPointer(mShader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mModel->mIBO);
	glDrawElements(GL_TRIANGLES, mModel->mNumberOfIndices, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mTexture->Unbind();
}
