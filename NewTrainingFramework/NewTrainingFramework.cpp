// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "Object.h"
#include "Camera.h"
#include "Resource.h"
#include "Scene.h"
#include "HeightMap.h"
#include <conio.h>


GLuint vboId, vboIdx;
Shaders myShaders;
Matrix worldMatrix;
Matrix worldMatrixScale;

Camera *camera;
Resource *res;
Scene *scene;
float time = 0;
float limit = 0;
float pixel = 0;

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	res = Resource::GetInstance();
	res->Init("../Resources/RSM/RM.txt");
	scene = Scene::GetInstance();
	scene->Init("../Resources/RSM/SM.txt");
	worldMatrix.SetIdentity();
	camera = new Camera();
	camera->projectionMatrix.SetPerspective(0.5f, Globals::screenWidth / (float)Globals::screenHeight, 0.1f, 500.0f);
	return 0;
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	worldMatrixScale.SetIdentity();
	worldMatrixScale.SetScale(0.3);
	Matrix inverseView;
	
	worldMatrix = worldMatrixScale *camera->GetMatrixView()* camera->projectionMatrix;
	inverseView = camera->GetMatrixView().InvertMatrix();

	scene->Draw(worldMatrix, inverseView, camera, time, pixel);

	//Active texture
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	camera->Update(deltaTime);
	time += deltaTime;
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case 'W':
			camera->SetDirection(camera->MOVE_FORWARD);
			break;
		case 'A':
			camera->SetDirection(camera->MOVE_LEFT);
			break;
		case 'D':
			camera->SetDirection(camera->MOVE_RIGHT);
			break;
		case 'S':
			camera->SetDirection(camera->MOVE_BACKWARD);
			break;
		case VK_UP:
			camera->SetDirection(camera->LOOK_UP);
			break;
		case VK_DOWN:
			camera->SetDirection(camera->LOOK_DOWN);
			break;
		case VK_LEFT:
			camera->SetDirection(camera->LOOK_LEFT);
			break;
		case VK_RIGHT:
			camera->SetDirection(camera->LOOK_RIGHT);
			break;
		case VK_ESCAPE:
			exit(EXIT_FAILURE);
			break;
		default:
			break;
		}
	}
	else
	{
		camera->m_direction = 0;
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
	delete camera;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;
    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Lep 3D", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;
	
	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();
	res->DestroyInstance();
	scene->DestroyInstance();
	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

