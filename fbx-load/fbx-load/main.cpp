#include <iostream>
#include <string>

#include "walk.hpp"

int main (int argc, char** argv){

	std::string path = "C:/development/fbx-anim/assets/turtle/turtle.fbx";

	FbxManager* fbxManager = FbxManager::Create();
	FbxImporter* fbxImporter = FbxImporter::Create(fbxManager, "fbx importer");
    FbxScene* fbxScene = FbxScene::Create(fbxManager , "fbx scene");

	bool result = fbxImporter->Initialize(path.c_str());
	result = fbxImporter->Import(fbxScene);

	if (result){
		std::cout << "Import succeeded!" << std::endl;
		WalkAssets(fbxScene, std::cout);
		WalkScene(fbxScene, std::cout);
	}
	else{
		std::cout << "Import failed!" << std::endl;
		return 1;
	}

	fbxScene->Destroy();
    fbxManager->Destroy();

	return 0;
}