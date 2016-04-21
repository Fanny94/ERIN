#include "CustomImport.h"

CustomImport::CustomImport(){}

CustomImport::~CustomImport(){}

void CustomImport::LoadCustomFormat(string filePath)
{
	ifstream fileIn(filePath, ios::in | ios::binary);
	
	fileIn.read((char*)&MeshCount, sizeof(unsigned int));
	fileIn.read((char*)&MaterialCount, sizeof(unsigned int));
	//fileIn.read((char*)&GroupCount, sizeof(unsigned int));
	//fileIn.read((char*)&LightCount, sizeof(unsigned int));
	//fileIn.read((char*)&CameraCount, sizeof(unsigned int));
	//fileIn.read((char*)&SkeletonAnimationCount, sizeof(unsigned int));
	//fileIn.read((char*)&KeyFrameCount, sizeof(unsigned int));
	//fileIn.read((char*)&MorphAnimationCount, sizeof(unsigned int));
	//fileIn.read((char*)&CustomAttributesCount, sizeof(unsigned int));

	for (int i = 0; i < MeshCount; i++)
	{
		fileIn.read((char*)&VertexCount, sizeof(unsigned int));
		fileIn.read((char*)&MaterialID, sizeof(unsigned int));
		fileIn.read((char*)&MeshID, sizeof(unsigned int));
		fileIn.read((char*)&ParentID, sizeof(unsigned int));
		fileIn.read((char*)&MeshName, sizeof(char) * 256);
		fileIn.read((char*)&AttributeCount, sizeof(unsigned int));
		fileIn.read((char*)&Translation, sizeof(float) * 3);
		fileIn.read((char*)&Rotation, sizeof(float) * 3);
		fileIn.read((char*)&Scale, sizeof(float) * 3);

		for (int j = 0; j < VertexCount; j++)
		{
			fileIn.read((char*)&vertexTemp.pos, sizeof(float) * 3);
			fileIn.read((char*)&vertexTemp.nor, sizeof(float) * 3);
			fileIn.read((char*)&vertexTemp.uv, sizeof(float) * 2);
			fileIn.read((char*)&vertexTemp.tan, sizeof(float) * 3);
			fileIn.read((char*)&vertexTemp.bitan, sizeof(float) * 3);
			vertex->push_back(vertexTemp);
		}
	}

	for (int i = 0; i < MaterialCount; i++)
	{
		fileIn.read((char*)&diffuseColor, sizeof(float) * 3);
		fileIn.read((char*)&ambientColor, sizeof(float) * 3);
		fileIn.read((char*)&specularColor, sizeof(float) * 3);
		fileIn.read((char*)&transparency, sizeof(float));
		fileIn.read((char*)&shininess, sizeof(float));
		fileIn.read((char*)&reflection, sizeof(float));
		fileIn.read((char*)&DiffuseMap, sizeof(char) * 256);
		fileIn.read((char*)&NormalMap, sizeof(char) * 256);
		fileIn.read((char*)&SpecularMap, sizeof(char) * 256);
	}

	/*for (int i = 0; i < GroupCount; i++)
	{
		fileIn.read((char*)&GroupID, sizeof(unsigned int));
		fileIn.read((char*)&GGroupCount, sizeof(unsigned int));
		fileIn.read((char*)&GroupParentID, sizeof(unsigned int));
		fileIn.read((char*)&GroupMeshID, sizeof(unsigned int));
	}*/

	/*for (int i = 0; i < LightCount; i++)
	{
		fileIn.read((char*)&PointLightCount, sizeof(unsigned int));
		fileIn.read((char*)&SpotLightCount, sizeof(unsigned int));
		fileIn.read((char*)&DirectionalLightCount, sizeof(unsigned int));
		fileIn.read((char*)&AreaLightCount, sizeof(unsigned int));

		for (int j = 0; j < PointLightCount; j++)
		{
			fileIn.read((char*)&pointLightTemp.intensity, sizeof(float));
			fileIn.read((char*)&pointLightTemp.color, sizeof(float) * 3);
			fileIn.read((char*)&pointLightTemp.position, sizeof(float) * 3);
			pointLight->push_back(pointLightTemp);
		}

		for (int k = 0; k < SpotLightCount; k++)
		{
			fileIn.read((char*)&spotLightTemp.intensity, sizeof(float));
			fileIn.read((char*)&spotLightTemp.color, sizeof(float) * 3);
			fileIn.read((char*)&spotLightTemp.position, sizeof(float) * 3);
			fileIn.read((char*)&spotLightTemp.rotation, sizeof(float) * 3);
			fileIn.read((char*)&spotLightTemp.scale, sizeof(float) * 3);
			spotLight->push_back(spotLightTemp);
		}

		for (int l = 0; l < DirectionalLightCount; l++)
		{
		   fileIn.read((char*)&directionalLightTemp.intensity, sizeof(float));
		   fileIn.read((char*)&directionalLightTemp.color, sizeof(float) * 3);
		   fileIn.read((char*)&directionalLightTemp.rotation, sizeof(float) * 3);
		   directionalLight->push_back(directionalLightTemp);
		}

		for (int m = 0; m < AreaLightCount; m++)
		{
			fileIn.read((char*)&areaLightTemp.intensity, sizeof(float));
			fileIn.read((char*)&areaLightTemp.color, sizeof(float) * 3);
			fileIn.read((char*)&areaLightTemp.position, sizeof(float) * 3);
			fileIn.read((char*)&areaLightTemp.rotation, sizeof(float) * 3);
			fileIn.read((char*)&areaLightTemp.height, sizeof(float));
			fileIn.read((char*)&areaLightTemp.width, sizeof(float));
			areaLight->push_back(areaLightTemp);
		}
	}*/

	/*for (int i = 0; i < CameraCount; i++)
	{
		fileIn.read((char*)&camPosition, sizeof(float) * 4);
		fileIn.read((char*)&camTarget, sizeof(float) * 4);
		fileIn.read((char*)&camUp, sizeof(float) * 4);
		fileIn.read((char*)&camRight, sizeof(float) * 4);
		fileIn.read((char*)&camForward, sizeof(float) * 4);
		fileIn.read((char*)&camYaw, sizeof(float));
		fileIn.read((char*)&camPitch, sizeof(float));
	}*/

	/*for (int i = 0; i < SkeletonAnimationCount; i++)
	{

	}*/

	/*for (int i = 0; i < KeyFrameCount; i++)
	{
		 fileIn.read((char*)&KeyFrameID, sizeof(float));
		 fileIn.read((char*)&KeyFrameTime, sizeof(float));
		 fileIn.read((char*)&KeyFramePosition, sizeof(float) * 3);
	}*/

	/*for (int i = 0; i < MorphAnimationCount; i++)
	{

	}*/

	/*for (int i = 0; i < CustomAttributesCount; i++)
	{
		fileIn.read((char*)&CustomVectorCount, sizeof(unsigned int));
		fileIn.read((char*)&CustomFloatCount, sizeof(unsigned int));
		fileIn.read((char*)&CustomIntCount, sizeof(unsigned int));
		fileIn.read((char*)&CustomBoolCount, sizeof(unsigned int));
		fileIn.read((char*)&CustomStringCount, sizeof(unsigned int));

		for (int j = 0; j < CustomVectorCount; j++)
		{
			fileIn.read((char*)&customVectorTemp.cVector, sizeof(float) * 3);
			customVector->push_back(customVectorTemp);
		}

		for (int k = 0; k < CustomFloatCount; k++)
		{
			fileIn.read((char*)&customFloatTemp.cFloat, sizeof(float));
			customFloat->push_back(customFloatTemp);
		}

		for (int l = 0; l < CustomIntCount; l++)
		{
			fileIn.read((char*)&customIntTemp.cInt, sizeof(int));
			customInt->push_back(customIntTemp);
		}

		for (int m = 0; m < CustomBoolCount; m++)
		{
			fileIn.read((char*)&customBoolTemp.cBool, sizeof(bool));
			customBool->push_back(customBoolTemp);
		}

		for (int n = 0; n < CustomStringCount; n++)
		{
			fileIn.read((char*)&customStringTemp.cString, sizeof(char) * 256);
			customString->push_back(customStringTemp);
		}
	}*/
	fileIn.close();
}