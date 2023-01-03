#pragma once
#include <map>
#include "Object.h"

using namespace std;

class Resource
{
public:
	static Resource* GetInstance();
	static void DestroyInstance();
	void Init(const char *path);
	char* getModelById(int id);
	char* getTextureById(int id);
	char* getFileVSById(int id);
	char* getFileFSById(int id);
	char* getFileRawById(int id);
private:
	Resource();
	~Resource();
	static Resource *instance;
	map<int, char*> m_model;
	map<int, char*> m_texture;
	map<int, char*> m_fileVS;
	map<int, char*> m_fileFS;
	map<int, char*> m_fileRaw;
};