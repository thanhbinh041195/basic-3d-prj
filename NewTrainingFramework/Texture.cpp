#include "stdafx.h"
#include "Texture.h"

Texture::Texture()
{
	m_Texture = 0;
}

Texture::~Texture()
{
	glDeleteBuffers(1, &m_Texture);
}

void Texture::InitFile(const char *file)
{
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	int width, height, bpp;
	char *bufferTGA = LoadTGA(file, &width, &height, &bpp);
	if (bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA);
	}
	delete[] bufferTGA;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);
	

}

void Texture::InitFileCube()
{
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
	int width, height, bpp;
	//char *bufferTGA = LoadTGA(file, &width, &height, &bpp);
	char *bufferTGA0 = LoadTGA("../Resources/Textures/chlorine-bay_ft.tga", &width, &height, &bpp);
	char *bufferTGA1 = LoadTGA("../Resources/Textures/chlorine-bay_bk.tga", &width, &height, &bpp);
	char *bufferTGA2 = LoadTGA("../Resources/Textures/chlorine-bay_dn.tga", &width, &height, &bpp);
	char *bufferTGA3 = LoadTGA("../Resources/Textures/chlorine-bay_up.tga", &width, &height, &bpp);
	char *bufferTGA4 = LoadTGA("../Resources/Textures/chlorine-bay_rt.tga", &width, &height, &bpp);
	char *bufferTGA5 = LoadTGA("../Resources/Textures/chlorine-bay_lf.tga", &width, &height, &bpp);
	if (bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA1);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA2);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA3);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA5);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA1);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA2);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA3);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA5);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	delete[] bufferTGA0;
	delete[] bufferTGA1;
	delete[] bufferTGA2;
	delete[] bufferTGA3;
	delete[] bufferTGA4;
	delete[] bufferTGA5;
}

GLuint Texture::GetTexture()
{
	return m_Texture;
}
