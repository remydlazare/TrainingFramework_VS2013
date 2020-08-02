// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "Object.h"
#include "Camera.h"
#include "ResourcesManager.h"
#include "SceneManager.h"
#include "Singleton.h"
#include <conio.h>
#include <bitset>


GLuint textureID;


void Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);

}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::vector<Object *>::iterator i = Singleton<SceneManager>::GetInstance()->m_vListObject.begin(); i != Singleton<SceneManager>::GetInstance()->m_vListObject.end(); i++)
	{
		(*i)->Draw();
	}

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );


}

std::bitset<8> foo;

void Update ( ESContext *esContext, float deltaTime )
{
	switch (foo.to_ulong()) {
	case 1:
		Singleton<Camera>::GetInstance()->MoveForward(deltaTime);
		break;
	case 2:
		Singleton<Camera>::GetInstance()->MoveBackward(deltaTime);
		break;
	case 4:
		Singleton<Camera>::GetInstance()->MoveLeft(deltaTime);
		break;
	case 8:
		Singleton<Camera>::GetInstance()->MoveRight(deltaTime);
		break;
	case 16:
		Singleton<Camera>::GetInstance()->RotateUp(deltaTime);
		break;
	case 32:
		Singleton<Camera>::GetInstance()->RotateDown(deltaTime);
		break;
	case 64:
		Singleton<Camera>::GetInstance()->RotateLeft(deltaTime);
		break;
	case 128:
		Singleton<Camera>::GetInstance()->RotateRight(deltaTime);
		break;
	}
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (!bIsPressed)
		foo.reset();
	else
	{
		if (key == 'W') // Up arrow
			foo.set(0, 1);
		if (key == 'S') // Down arrow
			foo.set(1, 1);
		if (key == 'A') // Left arrow
			foo.set(2, 1);
		if (key == 'D') // Down arrow
			foo.set(3, 1);
		if (key == '&')
			foo.set(4, 1);
		if (key == '(')
			foo.set(5, 1);
		if (key == '%')
			foo.set(6, 1);
		if (key == '\'')
			foo.set(7, 1);
	}
}

void CleanUp()
{
	//glDeleteBuffers(1, &vboId);
	delete Singleton<SceneManager>::GetInstance();
	delete Singleton<ResourcesManager>::GetInstance();
	delete Singleton<Camera>::GetInstance();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	Init ( &esContext );

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

