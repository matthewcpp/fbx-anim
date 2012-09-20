#include <iostream>
#include <string>

#include <fbxsdk.h>

int main (int argc, char** argv){

	std::string path = "C:/development/content/turtle/turtle.fbx";

	FbxManager* fbxManager = FbxManager::Create();
	FbxImporter* fbxImporter = FbxImporter::Create(fbxManager, "fbx importer");
    FbxScene* fbxScene = FbxScene::Create(fbxManager , "fbx scene");

	bool result = fbxImporter->Initialize(path.c_str());

	result = fbxImporter->Import(fbxScene);

	if (result)
		std::cout << "Import succeeded!" << std::endl;
	else
		std::cout << "Import failed!" << std::endl;

	fbxScene->Destroy();
    fbxManager->Destroy();

	return 0;
}