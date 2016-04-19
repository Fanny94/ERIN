#include "CustomImport.h"

CustomImport::CustomImport(){}

CustomImport::~CustomImport(){}

void CustomImport::LoadCustomFormat(string filePath)
{
	ifstream fileIn(filePath, ios::in | ios::binary);
	
	fileIn.read((char*)&MeshCount, sizeof(unsigned int));
	fileIn.read((char*)&MaterialCount, sizeof(unsigned int));

	for (int i = 0; i < MeshCount; i++)
	{
		fileIn.read((char*)&VertexCount, sizeof(unsigned int));
		fileIn.read((char*)&MaterialID, sizeof(unsigned int));
		fileIn.read((char*)&MeshID, sizeof(unsigned int));
		fileIn.read((char*)&ParentID, sizeof(unsigned int));
		fileIn.read((char*)&MeshName, sizeof(char) * 256);
		fileIn.read((char*)&AttributeCount, sizeof(unsigned int));
		fileIn.read((char*)&Translation, sizeof(float) * 3);
		fileIn.read((char*)&Roatation, sizeof(float) * 3);
		fileIn.read((char*)&Scale, sizeof(float) * 3);

		for (int j = 0; j < VertexCount; j++)
		{

		}
	}
}