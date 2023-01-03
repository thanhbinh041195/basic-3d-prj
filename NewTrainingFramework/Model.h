#pragma once
#include <cstdio> 
#include "Vertex.h"
using namespace std;

class Model
{
public:
	Model();
	~Model();

	Vertex *listVertex;
	unsigned short  *listIndices;
	int m_numberVertex;
	int m_numberIndices;

	void InitFile(char *file);
};
