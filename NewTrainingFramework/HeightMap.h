#pragma once
#include<vector>
#include"Shaders.h"
#include"Vertex.h"
#include "Camera.h"
#include <fstream>
#include <iostream>
#include "Texture.h"
#include "Table.h"
#include "../Utilities/utilities.h"

using namespace std;

class HeightMap
{
public:
	HeightMap();
	~HeightMap();
	void init(int vertRows, int vertCols, float dx, 
		float dz, char* rawFile, 
		int numTexture, vector<int> count,
	    char *fileVS, char *fileFS);
	void GenTriGrip(int numVertRows,int numVertCols,
						float dx, float dz,
						const Vector3& center, 
						vector<Vector3>& verts,
						vector<unsigned short>& indices);
	void loadRAW(int m, int n,
		const std::string& filename,
		float heightScale, float heightOffset);
	void Draw(Matrix worldMatrix, Camera* cam, float time);
	void setRota(Vector3 rota);
	void setPos(Vector3 pos);
	void setScale(float scale);
private:
	Matrix *m_scaleMap, *m_rotateMap, *m_tranformMap, *m_finalMap;
	GLuint vboId12, vboIdx12;
	Vertex* verticesData;
	unsigned short* listIndices1;
	vector<Vector3> verts;
	vector<unsigned short> indices;
	Shaders myShaders;
	int mNumTriangles, m_TextureCount;
	Texture* texture[50];
	Table<float> mHeightMap;
	void  filter3x3();
	bool  inBounds(int i, int j);
	float sampleHeight3×3(int i, int j);
};