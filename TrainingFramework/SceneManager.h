#include "Object.h"
#include <vector>
#pragma once

class SceneManager
{
public:
	std::vector<Object *> m_vListObject;

	SceneManager();
	~SceneManager();
};

