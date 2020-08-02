#include "stdafx.h"
#include "Model.h"
#include "Vertex.h"
#include "..\Utilities\utilities.h"

void Model::Init(const char * modelFile)
{
	FILE * file = fopen(modelFile, "r");
	int numberOfVertices;
	fscanf(file, "NrVertices: %d\n", &numberOfVertices);
	Vertex * vertices = new Vertex[numberOfVertices];
	for (int i = 0; i < numberOfVertices; ++i)
	{
		fscanf(file, "   %*d. pos:[%f, %f, %f]; norm:[%*f, %*f, %*f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];\n",
			&vertices[i].pos.x, &vertices[i].pos.y, &vertices[i].pos.z,
			&vertices[i].uv.x, &vertices[i].uv.y);
	}
	glGenBuffers(1, &this->mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numberOfVertices, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete vertices;

	int numberOfIndices;
	fscanf(file, "NrIndices: %d\n", &numberOfIndices);
	int * indices = new int[numberOfIndices];
	for (int i = 0; i < numberOfIndices; i += 3)
	{
		fscanf(file, "   %*d.    %d,    %d,    %d\n", &indices[i], &indices[i + 1], &indices[i + 2]);
	}

	glGenBuffers(1, &this->mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * numberOfIndices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete indices;

	mNumberOfIndices = numberOfIndices;
}

Model::Model(int ID, const char * modelFile)
{
	this->ID = ID;
	Init(modelFile);
}

//Model::Model(const char * modelFile)
//{
//	FILE * file = fopen(modelFile, "r");
//	Init(file);
//}

Model::~Model()
{
}
