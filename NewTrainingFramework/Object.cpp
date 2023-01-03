#include "stdafx.h"
#include"Object.h"
#include"Camera.h"
#include"Resource.h"

Object::Object()
{
}

Object::~Object()
{
	delete model;
	for (int i = 0; i < m_TextureCount; i++)
	{
		delete texture[i];
	}
	delete m_rotate;
	delete m_scale;
	delete m_tranform;
	delete m_final;
}

int Object::init(char *fileNFG, int numTexture, vector<int> count, char *fileVS, char *fileFS,int type)
{
	m_TextureCount = numTexture;
	m_type = type;
	Resource* res = Resource::GetInstance();
	model = new Model();
	for (int i = 0; i < m_TextureCount; i++)
	{
		texture[i] = new Texture();
	}
	m_rotate = new Matrix();
	m_scale = new Matrix();
	m_tranform = new Matrix();
	m_final = new Matrix();

	m_rotate->SetIdentity();
	m_scale->SetIdentity();
	m_tranform->SetIdentity();
	m_final->SetIdentity();

	model->InitFile(fileNFG);
	
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->listVertex[0]) * model->m_numberVertex, model->listVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vboIdx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIdx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model->listIndices[0]) * model->m_numberIndices, model->listIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		
	if (m_type == 0)
	{
		for (int i = 0; i < m_TextureCount; i++)
		{
				texture[i]->InitFile(res->getTextureById(count.at(i)));
		}
	}
	else
	{
		texture[0]->InitFileCube();
	}
	return myShaders.Init(fileVS, fileFS);
}

void Object::DrawCube(Matrix worldMatrix, Camera* cam, float time)
{
	unsigned short textureUnit = 0;
	glUseProgram(myShaders.program);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIdx);

	*m_final = (*m_scale) * (*m_rotate) * (*m_tranform);


	if (myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (myShaders.uvAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.uvAttribute);
		glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)56);
	}

	if (myShaders.l_lUniform != -1)
	{
		glUniformMatrix4fv(myShaders.l_lUniform, 1, GL_FALSE, *m_final->m);
	}
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture[textureUnit]->GetTexture());
	if (myShaders.textureUniform != -1)
	{
		glUniform1i(myShaders.textureUniform + textureUnit, textureUnit);
	}

	if (myShaders.w_WUniform != -1)
	{
		glUniformMatrix4fv(myShaders.w_WUniform, 1, GL_FALSE, &worldMatrix.m[0][0]);
	}

	if (myShaders.posCamera != -1)
	{
		glUniform3f(myShaders.posCamera, cam->m_position.x, cam->m_position.y, cam->m_position.z);
	}

	if (myShaders.fogColor != -1)
	{
		glUniform4f(myShaders.fogColor, 1, 1, 0, 1);
	}

	if (myShaders.fogStart != -1)
	{
		glUniform1f(myShaders.fogStart, 3);
	}

	if (myShaders.fogLenght != -1)
	{
		glUniform1f(myShaders.fogLenght, 5);
	}

	if (myShaders.timeUniform != -1)
	{
		glUniform1f(myShaders.timeUniform, time);
	}
	glDrawElements(GL_TRIANGLES, model->m_numberIndices, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Object::Draw(Matrix worldMatrix, Matrix invert, Camera* cam, float time, float pixel)
{
	unsigned short textureUnit = 0;
	glUseProgram(myShaders.program);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIdx);

	*m_final = (*m_scale) * (*m_rotate) * (*m_tranform);
	Matrix norm_W;
	norm_W = (worldMatrix.InvertMatrix()).Transpose();

	if (myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (myShaders.normAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.normAttribute);
		glVertexAttribPointer(myShaders.normAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)20);
	}

	if (myShaders.binormAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.binormAttribute);
		glVertexAttribPointer(myShaders.binormAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);
	}

	if (myShaders.tgtAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.tgtAttribute);
		glVertexAttribPointer(myShaders.tgtAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)44);
	}

	if (myShaders.uvAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.uvAttribute);
		glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)56);
	}

	if (myShaders.l_lUniform != -1)
	{
		glUniformMatrix4fv(myShaders.l_lUniform, 1, GL_FALSE, *m_final->m);
	}
	for (textureUnit = 0; textureUnit < m_TextureCount; textureUnit++)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D, texture[textureUnit]->GetTexture());
		if (myShaders.textureUniform != -1)
		{
			glUniform1i(myShaders.textureUniform + textureUnit, textureUnit);
		}
	}

	if (myShaders.w_WUniform != -1)
	{
		glUniformMatrix4fv(myShaders.w_WUniform, 1, GL_FALSE, &worldMatrix.m[0][0]);
	}

	if (myShaders.u_InvertMatrix != -1)
	{
		glUniformMatrix4fv(myShaders.u_InvertMatrix, 1, GL_FALSE, &invert.m[0][0]);
	}

	if (myShaders.u_normWUniform != -1)
	{
		glUniformMatrix4fv(myShaders.u_normWUniform, 1, GL_FALSE, &norm_W.m[0][0]);
	}

	if (myShaders.posCamera != -1)
	{
		glUniform3f(myShaders.posCamera, cam->m_position.x, cam->m_position.y, cam->m_position.z);
	}

	if (myShaders.fogColor != -1)
	{
		glUniform4f(myShaders.fogColor, 1, 1, 1, 1);
	}

	if (myShaders.u_LightColor != -1)
	{
		glUniform4f(myShaders.u_LightColor, 1, 1, 0, 1);
	}

	if (myShaders.u_LightPos != -1)
	{
		glUniform4f(myShaders.u_LightPos, 1, 5, 0, 1);
	}

	if (myShaders.fogStart != -1)
	{
		glUniform1f(myShaders.fogStart, 3);
	}

	if (myShaders.fogLenght != -1)
	{
		glUniform1f(myShaders.fogLenght, 5);
	}

	if (myShaders.timeUniform != -1)
	{
		glUniform1f(myShaders.timeUniform, time);
	}

	if (myShaders.pixelUniform != 1)
	{
		glUniform1f(myShaders.pixelUniform, pixel);
	}

	glDrawElements(GL_TRIANGLES, model->m_numberIndices, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	for (textureUnit = 0; textureUnit < m_TextureCount; textureUnit++)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Object::setType(int a)
{
	m_type = a;
}

int Object::getType()
{
	return m_type;
}

void Object::setPos(Vector3 pos)
{
	m_tranform->SetTranslation(pos);
}

void Object::setRota(Vector3 rota)
{
	m_rotate->SetRotationAngleAxis(180 * 3.14 / 180, rota.x, rota.y, rota.z);
}

void Object::setScale(float scale)
{
	m_scale->SetScale(scale);
}