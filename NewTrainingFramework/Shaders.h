#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute, 
		normAttribute, 
		binormAttribute, 
		uvAttribute, 
		tgtAttribute, 
		textureUniform, 
		w_WUniform,
		l_lUniform,
		posCamera,
		fogColor,
		fogStart,
		fogLenght,
		timeUniform,
		u_LightColor,
		u_LightPos,
		u_InvertMatrix,
		u_normWUniform,
		pixelUniform;

	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};