#pragma once

#include "../Utilities/utilities.h"
#include"Shaders.h"

class Texture
{
private:
	GLuint m_Texture;
public:
	Texture();
	~Texture();
	
	GLuint GetTexture();	
	void InitFile(const char *file);
	void InitFileCube();
};
