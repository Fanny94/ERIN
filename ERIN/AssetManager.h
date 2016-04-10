#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "Mesh.h"

/*
	Shall handle all assets and then to be associated with a GameObject
	then to be rendered by Graphics.

	Importer will be implemented in this class.
*/

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

private:
	Mesh* meshes;
};

#endif // !ASSETMANAGER_H

