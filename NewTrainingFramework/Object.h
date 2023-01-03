#pragma once
#include"Texture.h"
#include"Model.h"
#include"Shaders.h"
#include "Camera.h"
#include<vector>

class Object
{
public:
	Object();
	~Object();

	int init(char *fileNFG, int numTexture, vector<int> count, char *fileVS, char *fileFS,int type);
	void Draw(Matrix worldMatrix, Matrix invert, Camera* cam, float time, float pixel);
	void DrawCube(Matrix worldMatrix, Camera* cam, float time);
	void setType(int a);
	int getType();
	void setPos(Vector3 pos);
	void setRota(Vector3 rota);
	void setScale(float scale);
private:
	Matrix *m_scale, *m_rotate, *m_tranform, *m_final,
		 *mtRotZ, *mtRotX, *mtRotY;
	Model* model;
	Shaders myShaders;
	Texture* texture[50];
	GLuint vboId, vboIdx, textureHandle;
	Matrix worldMatrixScale;
	Camera *camera;
	int m_TextureCount = 0, m_type;
};