#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include <vector>

class ResourcesManager
{

public:
	std::vector<Model *> m_vModelList;
	std::vector<Texture *> m_v2DTextureList;
	std::vector<Texture *> m_vCubeTextureList;
	std::vector<Shaders *> m_vShaderList;

	ResourcesManager();
	~ResourcesManager();
};

