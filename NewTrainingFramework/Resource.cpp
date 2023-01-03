#include "stdafx.h"
#include "Resource.h"

Resource::Resource()
{

}

Resource* Resource::instance = 0;

Resource* Resource::GetInstance()
{
	if (instance == 0)
	{
		instance = new Resource();
	}
	return instance;
}


void Resource::Init(const char *path)
{
	FILE *fptr;
	fptr = fopen(path, "r");
	int numID, numModel, numTexture, numFile, numFileRaw;
	char m_Path[50], m_Path2[50];
	if (fptr == NULL)
	{
		printf("Can't open file");
	}
	//Models
	fscanf(fptr, "#Models: %d\n", &numModel);
	for (int i = 0; i < numModel; i++)
	{
		char *buf = new char[50];
		fscanf(fptr, "ID %d\n", &numID);
		fscanf(fptr, "FILE %s\n", m_Path);
		m_model[numID] = strcpy(buf, m_Path);
	}
	//Textures
	fscanf(fptr, "#2D Textures: %d\n", &numTexture);
	for (int i = 0; i < numTexture; i++)
	{
		char *buf = new char[50];
		fscanf(fptr, "ID %d\n", &numID);
		fscanf(fptr, "FILE %s\n", m_Path);
		m_texture[numID] = strcpy(buf, m_Path);
	}
	//Raw
	fscanf(fptr, "#Raw files: %d\n", &numFileRaw);
	for (int i = 0; i < numFileRaw; i++)
	{
		char *buf = new char[50];
		fscanf(fptr, "ID %d\n", &numID);
		fscanf(fptr, "FILE %s\n", m_Path);
		m_fileRaw[numID] = strcpy(buf, m_Path);
	}
	//Shader programs
	fscanf(fptr, "#Shaders: %d\n", &numFile);
	for (int i = 0; i < numFile; i++)
	{
		char *buf = new char[50];
		char *buf2 = new char[50];
		fscanf(fptr, "ID %d\n", &numID);
		fscanf(fptr, "VS %s\n", m_Path);
		fscanf(fptr, "FS %s\n", m_Path2);
		m_fileVS[numID] = strcpy(buf, m_Path);
		m_fileFS[numID] = strcpy(buf2, m_Path2);
	}
	fclose(fptr);
	int a = 0;
}

char* Resource::getModelById(int id)
{
	return m_model[id];
}

char* Resource::getTextureById(int id)
{
	return m_texture[id];
}

char* Resource::getFileVSById(int id)
{
	return m_fileVS[id];
}

char* Resource::getFileFSById(int id)
{
	return m_fileFS[id];
}

char* Resource::getFileRawById(int id)
{
	return m_fileRaw[id];
}

Resource::~Resource()
{
	for (map<int, char*>::iterator i = m_model.begin(); i != m_model.end(); i++)
	{
		delete i->second;
	}
	for (map<int, char*>::iterator i = m_texture.begin(); i != m_texture.end(); i++)
	{
		delete i->second;
	}
	for (map<int, char*>::iterator i = m_fileVS.begin(); i != m_fileVS.end(); i++)
	{
		delete i->second;
	}
	for (map<int, char*>::iterator i = m_fileFS.begin(); i != m_fileFS.end(); i++)
	{
		delete i->second;
	}
	for (map<int, char*>::iterator i = m_fileRaw.begin(); i != m_fileRaw.end(); i++)
	{
		delete i->second;
	}
}

void Resource::DestroyInstance()
{
	delete instance;
}