#include <stdafx.h>
#include "Model.h"

Model::Model()
{

}

Model::~Model()
{
	delete listVertex;
	delete listIndices;
}

void Model::InitFile(char *file)
{
	FILE * fp;
	fp = fopen(file, "r");
	if (fp == NULL)
	{
		printf("Can't open file");
	}
	else
	{
		char nameElement[50];
		fscanf(fp, "%s", nameElement);
		fscanf(fp, "%d", &m_numberVertex);
		listVertex = new Vertex[m_numberVertex];
		for (int i = 0; i<m_numberVertex; i++)
		{
			fscanf_s(fp, "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", 
				&listVertex[i].pos.x, &listVertex[i].pos.y, &listVertex[i].pos.z,
				&listVertex[i].norm.x, &listVertex[i].norm.y, &listVertex[i].norm.z, 
				&listVertex[i].binorm.x, &listVertex[i].binorm.y, &listVertex[i].binorm.z, 
				&listVertex[i].tgt.x, &listVertex[i].tgt.y, &listVertex[i].tgt.z,
				&listVertex[i].uv.x, &listVertex[i].uv.y);
			//listVertex[i].pos /= 150;
		}
		fscanf(fp, "%s", nameElement);
		fscanf(fp, "%d", &m_numberIndices);
		listIndices = new unsigned short[m_numberIndices];
		for (int i = 0; i<m_numberIndices; i = i + 3)
		{
			fscanf_s(fp, "   %*d. %hd, %hd, %hd", &listIndices[i], &listIndices[i + 1], &listIndices[i + 2]);
		}
	}
	fclose(fp);
}
