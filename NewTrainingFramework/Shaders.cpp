#include <stdafx.h>
#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	normAttribute = glGetAttribLocation(program, "a_norm");
	binormAttribute = glGetAttribLocation(program, "a_binorm");
	tgtAttribute = glGetAttribLocation(program, "a_tgt");

	//Fog
	posCamera = glGetUniformLocation(program, "u_posCamera");
	fogColor = glGetUniformLocation(program, "u_fogColor");
	fogStart = glGetUniformLocation(program, "u_fogStar");
	fogLenght = glGetUniformLocation(program, "u_fogLenght");

	//light
	u_LightColor = glGetAttribLocation(program, "u_lcolor");
	u_LightPos = glGetAttribLocation(program, "u_lpos");

	//matrix
	w_WUniform = glGetUniformLocation(program, "u_w");
	l_lUniform = glGetUniformLocation(program, "u_l");
	u_normWUniform = glGetUniformLocation(program, "u_normW");


	//update uniform
	timeUniform = glGetUniformLocation(program, "u_time");
	pixelUniform = glGetUniformLocation(program, "u_pixel");
	u_InvertMatrix = glGetUniformLocation(program, "u_invertMax");

	//texture
	textureUniform = glGetUniformLocation(program, "u_s_texture");
	

	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}