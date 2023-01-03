#include "stdafx.h"
#include "Scene.h"
#include "Resource.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	for (int i = 0; i < numObject; i++)
	{
		delete m_listObject.at(i);
	}
	delete m_map;
}

Scene* Scene::instance = 0;

Scene* Scene::GetInstance()
{
	if (instance == 0)
	{
		instance = new Scene();
	}
	return instance;
}

void Scene::OnInit(const char *path)
{
	Resource* re = Resource::GetInstance();
	m_map = new HeightMap();
	FILE *fptr;
	char type[10];
	fptr = fopen(path, "r");
	if (fptr == NULL)
	{
		printf("Can't open file");
	}
	//Create objects
	fscanf(fptr, "#Object: %d\n", &numObject);
	for (int i = 0; i < numObject; i++)
	{
		m_listObject.push_back(new Object());
		fscanf(fptr, "ID %d\n", &m_ID);
		fscanf(fptr, "MODEL %d\n", &m_Model);
		fscanf(fptr, "TEXTURES %d\n", &numTexture);
		for (int j = 0; j < numTexture; j++)
		{
			fscanf(fptr, "TEXTURE %d\n", &m_NumberTexture);
			countTexure.push_back(m_NumberTexture);
		}
		fscanf(fptr, "CUBETEXTURES %d\n", &m_CubeTexture);
		fscanf(fptr, "SHADER %d\n", &numShader);
		fscanf(fptr, "POSITION %f %f %f\n", &pos.x, &pos.y, &pos.z);
		fscanf(fptr, "ROTATION %f %f %f\n", &rota.x, &rota.y, &rota.z);
		fscanf(fptr, "SCALE %f\n", &scale);
		m_listObject.at(i)->init(re->getModelById(m_Model), numTexture, countTexure, re->getFileVSById(numShader), re->getFileFSById(numShader), m_CubeTexture);
		m_listObject.at(i)->setScale(scale);
		m_listObject.at(i)->setRota(rota);
		m_listObject.at(i)->setPos(pos);
		m_listObject.at(i)->setType(m_CubeTexture);
		countTexure.clear();
	}
	//Create height map
	fscanf(fptr, "#Height map: %d\n", &tmp);
	fscanf(fptr, "NumCol %d\n", &numCols);
	fscanf(fptr, "NumRow %d\n", &numRows);
	fscanf(fptr, "DX %f\n", &dx);
	fscanf(fptr, "DZ %f\n", &dz);
	fscanf(fptr, "RawFile %d\n", &m_RawFile);
	fscanf(fptr, "TEXTURES %d\n", &numTexture);
	for (int j = 0; j < numTexture; j++)
	{
		fscanf(fptr, "TEXTURE %d\n", &m_NumberTexture);
		countTexure.push_back(m_NumberTexture);
	}
	fscanf(fptr, "SHADER %d\n", &numShader);
	fscanf(fptr, "POSITION %f %f %f\n", &pos.x, &pos.y, &pos.z);
	fscanf(fptr, "ROTATION %f %f %f\n", &rota.x, &rota.y, &rota.z);
	fscanf(fptr, "SCALE %f\n", &scale);
	m_map->init(numCols, numRows, dx, dz, re->getFileRawById(m_RawFile), numTexture, countTexure, re->getFileVSById(numShader), re->getFileFSById(numShader));
	m_map->setPos(pos);
	m_map->setRota(rota);
	m_map->setScale(scale);
	countTexure.clear();
	fclose(fptr);
}

void Scene::Init(const char *path)
{
	OnInit(path);
}

void Scene::Draw(Matrix worldMatrix, Matrix invert, Camera* cam, float time, float pixel)
{
	for (int i = 0; i < numObject; i++)
	{
		if (m_listObject.at(i)->getType() == 0)
		{
			m_listObject.at(i)->Draw(worldMatrix, invert, cam, time, pixel);
		}
		else
		{
			m_listObject.at(i)->DrawCube(worldMatrix, cam, time);
		}
	}
	m_map->Draw(worldMatrix, cam, time);
}

void Scene::DestroyInstance()
{
	delete instance;
}

