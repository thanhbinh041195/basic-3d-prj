#pragma once
#include <vector>
#include <map>
#include "Object.h"
#include "HeightMap.h"

using namespace std;

class Scene
{
public:
	static Scene* GetInstance();
	static void DestroyInstance();
	void OnInit(const char *path);
	void Init(const char *path);
	void Draw(Matrix worldMatrix, Matrix invert, Camera* cam, float time, float pixel);
private:
	Scene();
	~Scene();
	int numObject, numTexture, numShader, m_ID, m_Model, m_NumberTexture, m_CubeTexture, m_type,
		numCols, numRows, tmp, m_RawFile;
	float scale, dx, dz;
	Vector3 pos,rota;
	vector<Object*> m_listObject;
	vector<int> countTexure;
	HeightMap* m_map;
	static Scene *instance;
};