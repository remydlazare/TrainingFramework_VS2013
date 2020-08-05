#include "stdafx.h"
#include "ResourcesManager.h"
#include <string>

ResourcesManager::ResourcesManager()
{
	FILE * file = fopen("..\\Resources\\RM.txt", "r");

	int NrModel, Nr2DTexture, NrCubeTexture, NrShader;
	fscanf(file, "#Models: %d\n", &NrModel);
	for (int i = 0; i < NrModel; i++)
	{
		int ID;
		fscanf(file, "ID %d\n", &ID);
		char link[50];
		fscanf(file, "FILE %*c%s\n", link);
		link[strlen(link) - 1] = '\0';
		m_vModelList.push_back(new Model(ID, link));
	}
	
	fscanf(file, "\n#2D Textures: %d\n", &Nr2DTexture);
	for (int i = 0; i < Nr2DTexture; i++)
	{
		int ID;
		fscanf(file, "\nID %d\n", &ID);
		char path[50], mode[50];
		fscanf(file, "FILE %*c%s\n%[^\n]s", path, mode);
		path[strlen(path) - 1] = '\0';
		m_v2DTextureList.push_back(new Texture(ID, path, mode));
	}

	fscanf(file, "\n#Cube Textures: %d\n", &NrCubeTexture);
	for (int i = 0; i < NrCubeTexture; i++)
	{
		int ID;
		fscanf(file, "\nID %d\n", &ID);
		char right[50], left[50], top[50], bottom[50], back[50], front[50];
		fscanf(file, "FILE %*c%s\n", right);
		fscanf(file, "FILE %*c%s\n", left);
		fscanf(file, "FILE %*c%s\n", top);
		fscanf(file, "FILE %*c%s\n", bottom);
		fscanf(file, "FILE %*c%s\n", back);
		fscanf(file, "FILE %*c%s\n", front);
		right[strlen(right) - 1] = '\0';
		left[strlen(left) - 1] = '\0';
		top[strlen(top) - 1] = '\0';
		bottom[strlen(bottom) - 1] = '\0';
		back[strlen(back) - 1] = '\0';
		front[strlen(front) - 1] = '\0';
		char* TextureFiles[] = { right, left, top, bottom, back, front };
		/*for (int j = 0; j < 6; j++)
		{
			fscanf(file, "FILE %*c%s\n", path[j]);
			path[j][strlen(path[j]) - 1] = '\0';
		}*/
		char mode[50];
		fscanf(file, "%[^\n]s", mode);
		m_vCubeTextureList.push_back(new Texture(ID, TextureFiles, mode));

	}

	fscanf(file, "\n#Shaders: %d\n", &NrShader);
	for (int i = 0; i < NrShader; i++)
	{
		int ID;
		fscanf(file, "ID %d\n", &ID);
		char vs[50], fs[50];
		fscanf(file, "VS %*c%s\n", vs);
		fscanf(file, "FS %*c%s\n", fs);
		vs[strlen(vs) - 1] = '\0';
		fs[strlen(fs) - 1] = '\0';
		m_vShaderList.push_back(new Shaders(ID, vs, fs));
	}
}


ResourcesManager::~ResourcesManager()
{
	for (std::vector<Model *>::iterator i = m_vModelList.begin(); i != m_vModelList.end(); i++)
		delete *i;
	for (std::vector<Texture *>::iterator i = m_v2DTextureList.begin(); i != m_v2DTextureList.end(); i++)
		delete *i;
	for (std::vector<Texture*>::iterator i = m_vCubeTextureList.begin(); i != m_vCubeTextureList.end(); i++)
		delete* i;
	for (std::vector<Shaders *>::iterator i = m_vShaderList.begin(); i != m_vShaderList.end(); i++)
		delete *i;
}