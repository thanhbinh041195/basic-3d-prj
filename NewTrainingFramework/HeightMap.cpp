#include "stdafx.h"
#include "HeightMap.h"
#include "Resource.h"



HeightMap::HeightMap()
{
	vboId12 = 0;
	vboIdx12 = 0;
}

HeightMap::~HeightMap()
{
	delete verticesData;
	delete listIndices1;
	delete m_rotateMap;
	delete m_finalMap;
	delete m_scaleMap;
	delete m_tranformMap;
	for (int i = 0; i < m_TextureCount; i++)
	{
		delete texture[i];
	}
}

void HeightMap::init(int vertRows, int vertCols, float dx, float dz, char* rawFile, int numTexture, vector<int> count,char *fileVS,char *fileFS)
{
	Resource* res = Resource::GetInstance();
	m_TextureCount = numTexture;
	m_rotateMap = new Matrix();
	m_scaleMap = new Matrix();
	m_tranformMap = new Matrix();
	m_finalMap = new Matrix();
	for (int i = 0; i < m_TextureCount; i++)
	{
		texture[i] = new Texture();
	}

	m_rotateMap->SetIdentity();
	m_scaleMap->SetIdentity();
	m_tranformMap->SetIdentity();
	m_finalMap->SetIdentity();
	m_tranformMap->SetTranslation(1, -3, 1);
	m_scaleMap->SetScale(0.1f);
	float w = (vertCols - 1) * dx;
	float d = (vertRows - 1) * dz;


	GenTriGrip(vertRows, vertCols, dx, dz,
		Vector3(0.0f, 0.0f, 0.0f), verts, indices);
	loadRAW(vertRows, vertCols, rawFile, 0.1f, 0.0f);


	int mNumVertices = vertRows * vertCols;
	mNumTriangles = (vertRows - 1) * (vertCols - 1) * 2;
	verticesData = new Vertex[mNumVertices];
	listIndices1 = new unsigned short[mNumTriangles * 3];

	for (int i = 0; i < vertRows; ++i)
	{
		for (int j = 0; j < vertCols; ++j)
		{
			DWORD index = i * vertCols + j;
			verticesData[index].pos = verts.at(index);
			verticesData[index].pos.y = mHeightMap(i, j);;
			verticesData[index].norm = Vector3(0.0f, 1.0f, 0.0f);
			verticesData[index].uv.x = (verticesData[index].pos.x + (0.5f*w)) / w;
			verticesData[index].uv.y = (verticesData[index].pos.z - (0.5f*d)) / -d;
		}
	}
	for (int i = 0; i < mNumTriangles; i++)
	{
		//listIndices1[i] = (unsigned short)indices.at(i);
		listIndices1[i * 3 + 0] = (unsigned short)indices.at(i * 3 + 0);
		listIndices1[i * 3 + 1] = (unsigned short)indices.at(i * 3 + 1);
		listIndices1[i * 3 + 2] = (unsigned short)indices.at(i * 3 + 2);
	}
	glGenBuffers(1, &vboId12);
	glBindBuffer(GL_ARRAY_BUFFER, vboId12);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mNumVertices, verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vboIdx12);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIdx12);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(listIndices1[0])* mNumTriangles * 3, listIndices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	for (int i = 0; i < m_TextureCount; i++)
	{
		texture[i]->InitFile(res->getTextureById(count.at(i)));
	}
	myShaders.Init(fileVS, fileFS);
}

void HeightMap::Draw(Matrix worldMatrix, Camera* cam, float time)
{
	unsigned short textureUnit = 0;
	glUseProgram(myShaders.program);
	glBindBuffer(GL_ARRAY_BUFFER, vboId12);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIdx12);


	*m_finalMap = (*m_scaleMap) * (*m_rotateMap) * (*m_tranformMap);

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
		glUniformMatrix4fv(myShaders.l_lUniform, 1, GL_FALSE, *m_finalMap->m);
	}

	if (myShaders.w_WUniform != -1)
	{
		glUniformMatrix4fv(myShaders.w_WUniform, 1, GL_FALSE, &worldMatrix.m[0][0]);
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

	glDrawElements(GL_TRIANGLES, mNumTriangles * 3, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void HeightMap::loadRAW(int m, int n,
	const std::string& filename,
	float heightScale, float heightOffset)
{
	//std::ifstream is;
	// A height for each vertex
	std::vector<unsigned char> in(m * n);

	// Open the file.
	std::ifstream inFile;
	inFile.open(filename.c_str(), ios_base::binary);

	// Read all the RAW bytes in one go.
	inFile.read((char*)&in[0], (std::streamsize)in.size());

	// Done with file.
	inFile.close();

	// Copy the array data into a float table format, and scale
	// and offset the heights.
	mHeightMap.resize(m, n,0);
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int k = i * n + j;
			mHeightMap(i, j) = (float)in[k] * heightScale + heightOffset;
		}
	}
	filter3x3();
}

void HeightMap::filter3x3()
{
	Table<float> temp(mHeightMap.numRows(), mHeightMap.numCols());

	for (int i = 0; i < mHeightMap.numRows(); ++i)
		for (int j = 0; j < mHeightMap.numCols(); ++j)
			temp(i, j) = sampleHeight3×3(i, j);

	mHeightMap = temp;
}

float HeightMap::sampleHeight3×3(int i,int j)
{
	float avg = 0.0f;
	float num = 0.0f;
	for (int m = i - 1; m <= i + 1; ++m)
	{
		for (int n = j - 1; n <= j + 1; ++n)
		{
			if (inBounds(m, n))
			{
				avg += mHeightMap(m, n);
				num += 1.0f;
			}
		}
	}
	return avg / num;
}

bool HeightMap::inBounds(int i, int j)
{
	return
		i >= 0 &&
		i < (int)mHeightMap.numRows() &&
		j >= 0 &&
		j < (int)mHeightMap.numCols();
}

void HeightMap::GenTriGrip(int numVertRows, int numVertCols,
	float dx, float dz,
	const Vector3& center,
	vector<Vector3>& verts,
	vector<unsigned short>& indices)
{
	int numVertices = numVertRows*numVertCols;
	int numCellRows = numVertRows - 1;
	int numCellCols = numVertCols - 1;

	int numTris = numCellRows*numCellCols * 2;

	float width = (float)numCellCols * dx;
	float depth = (float)numCellRows * dz;

	verts.resize(numVertices);

	float xOffset = -width * 0.5f;
	float zOffset = depth * 0.5f;

	int k = 0;
	for (float i = 0; i < numVertRows; ++i)
	{
		for (float j = 0; j < numVertCols; ++j)
		{
			verts[k].x = j * dx + xOffset;
			verts[k].z = -i * dz + zOffset;
			verts[k].y = 0.0f;

			Matrix T;
			T.SetIdentity();
			T.SetTranslation(center.x, center.y, center.z);
			Vector4 temp = Vector4(verts[k].x, verts[k].y, verts[k].z, 1.0f);
			temp = T * temp;

			++k;
		}
	}
	indices.resize(numTris * 3);

	// Generate indices for each quad.
	k = 0;
	for (DWORD i = 0; i < (DWORD)numCellRows; ++i)
	{
		for (DWORD j = 0; j < (DWORD)numCellCols; ++j)
		{
			indices[k] = i   * numVertCols + j;
			indices[k + 1] = i   * numVertCols + j + 1;
			indices[k + 2] = (i + 1) * numVertCols + j;

			indices[k + 3] = (i + 1) * numVertCols + j;
			indices[k + 4] = i   * numVertCols + j + 1;
			indices[k + 5] = (i + 1) * numVertCols + j + 1;

			k += 6;
		}
	}

}

void HeightMap::setPos(Vector3 pos)
{
	m_tranformMap->SetTranslation(pos);
}

void HeightMap::setRota(Vector3 rota)
{
	m_rotateMap->SetRotationAngleAxis(180 * 3.14 / 180, rota.x, rota.y, rota.z);
}

void HeightMap::setScale(float scale)
{
	m_scaleMap->SetScale(scale);
}