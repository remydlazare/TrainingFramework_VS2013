#include "stdafx.h"
#include "SceneManager.h"
#include "ResourcesManager.h"
#include "Camera.h"
#include "Singleton.h"

SceneManager::SceneManager()
{
	FILE* file = fopen("..\\Resources\\SM.txt", "r");
	int iObjectCount;
	fscanf(file, "#Objects: %d\n", &iObjectCount);
	for (int i = 0; i < iObjectCount; ++i)
	{
		m_vListObject.push_back(new Object());
		int ModelID;
		fscanf(file, "\nID %*d\nMODEL %d\n", &ModelID);
		for (std::vector<Model *>::iterator i = Singleton<ResourcesManager>::GetInstance()->m_vModelList.begin(); i != Singleton<ResourcesManager>::GetInstance()->m_vModelList.end(); i++)
			if ((*i)->ID == ModelID)
				m_vListObject.back()->mModel = (*i);
		int NrTexture;
		fscanf(file, "TEXTURES %d\n", &NrTexture);
		if (NrTexture != 0)
		{
			int TextureID;
			fscanf(file, "TEXTURE %d\n", &TextureID);
			for (std::vector<Texture*>::iterator i = Singleton<ResourcesManager>::GetInstance()->m_v2DTextureList.begin(); i != Singleton<ResourcesManager>::GetInstance()->m_v2DTextureList.end(); i++)
				if ((*i)->ID == TextureID)
					m_vListObject.back()->mTexture = (*i);
		}
		int NrCubeTexture;
		fscanf(file, "CUBETEXTURES %d\n", &NrCubeTexture);
		if (NrCubeTexture != 0)
		{
			int CubeTextureID;
			fscanf(file, "CUBETEXTURE %d\n", &CubeTextureID);
			for (std::vector<Texture*>::iterator i = Singleton<ResourcesManager>::GetInstance()->m_vCubeTextureList.begin(); i != Singleton<ResourcesManager>::GetInstance()->m_vCubeTextureList.end(); i++)
				if ((*i)->ID == CubeTextureID)
					m_vListObject.back()->mTexture = (*i);
		}
		int ShaderID;
		fscanf(file, "SHADER %d\n", &ShaderID);
		for (std::vector<Shaders *>::iterator i = Singleton<ResourcesManager>::GetInstance()->m_vShaderList.begin(); i != Singleton<ResourcesManager>::GetInstance()->m_vShaderList.end(); i++)
			if ((*i)->ID == ShaderID)
				m_vListObject.back()->mShader = (*i);
		GLfloat PosX, PosY, PosZ,
			RotX, RotY, RotZ,
			ScaX, ScaY, ScaZ;
		fscanf(file, "POSITION %f, %f, %f\n", &PosX, &PosY, &PosZ);
		fscanf(file, "ROTATION %f, %f, %f\n", &RotX, &RotY, &RotZ);
		fscanf(file, "SCALE %f, %f, %f\n", &ScaX, &ScaY, &ScaZ);
		m_vListObject.back()->mTranslation.SetTranslation(PosX, PosY, PosZ);
		m_vListObject.back()->mRx.SetRotationX(RotX);
		m_vListObject.back()->mRy.SetRotationY(RotY);
		m_vListObject.back()->mRz.SetRotationZ(RotZ);
		m_vListObject.back()->mScale.SetScale(ScaX, ScaY, ScaZ);
	}
	fscanf(file, "\n#CAMERA\nNEAR %f\n", &Singleton<Camera>::GetInstance()->mNearPane);
	fscanf(file, "FAR %f\n", &Singleton<Camera>::GetInstance()->mFarPane);
	fscanf(file, "FOV %f\n", &Singleton<Camera>::GetInstance()->mFOV);
	fscanf(file, "SPEED %f", &Singleton<Camera>::GetInstance()->mMoveSpeed);
	Singleton<Camera>::GetInstance()->mRotateSpeed = Singleton<Camera>::GetInstance()->mMoveSpeed;
}


SceneManager::~SceneManager()
{
	for (std::vector<Object *>::iterator i = m_vListObject.begin(); i != m_vListObject.end(); i++)
		delete *i;
}