#include "stdafx.h"
#include "ResourcesManager.h"
#include <string>

ResourcesManager::ResourcesManager()
{
	FILE * file = fopen("..\\Resources\\RM.txt", "r");

	int NrModel, NrTexture, NrShader;
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
	
	fscanf(file, "\n#2D Textures: %d\n", &NrTexture);
	for (int i = 0; i < NrTexture; i++)
	{
		int ID;
		fscanf(file, "\nID %d\n", &ID);
		char path[50], mode[50];
		fscanf(file, "FILE %*c%s\n%[^\n]s", path, mode);
		path[strlen(path) - 1] = '\0';
		m_vTextureList.push_back(new Texture(ID, path, mode));
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
		m_vShaderList.push_back(new Shaders(ID, "..\\Resources\\Shaders\\TriangleShaderVS.vs", "..\\Resources\\Shaders\\TriangleShaderFS.fs"));
	}

}


ResourcesManager::~ResourcesManager()
{
	for (std::vector<Model *>::iterator i = m_vModelList.begin(); i != m_vModelList.end(); i++)
		delete *i;
	for (std::vector<Texture *>::iterator i = m_vTextureList.begin(); i != m_vTextureList.end(); i++)
		delete *i;
	for (std::vector<Shaders *>::iterator i = m_vShaderList.begin(); i != m_vShaderList.end(); i++)
		delete *i;
}