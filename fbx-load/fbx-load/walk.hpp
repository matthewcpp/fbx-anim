#ifndef WALK_HPP
#define WALK_HPP

#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>

struct keyInfo{
	float time;
	float value;
};

typedef std::vector<keyInfo> keyArray;

#include <fbxsdk.h>

void WalkScene(FbxScene* fbxScene, std::ostream& logStream);
void WalkNode(FbxScene* fbxScene, FbxNode* node, size_t depth, std::ostream& logStream);

void WalkAssets(FbxScene* scene, std::ostream& logStream);
void WalkMaterials(FbxScene* scene, std::ostream& logStream);
void WalkTextures(FbxScene* scene, std::ostream& logStream);

void ProcessSkeletonNode(FbxScene* fbxScene, FbxNode* node);
void WalkAnimations(FbxNode* node, FbxScene* fbxScene, std::ostream& logStream);
void WalkAnimation(FbxNode* node, FbxAnimStack* animStack, std::ostream& logStream);
void GetCurveData(const std::string& label, FbxAnimCurve* animCurve, std::ostream& logStream);
void GetKeyValues(FbxAnimCurve* animCurve, std::ostream& logStream);

bool NodeAttributeIsType(FbxNode* node, FbxNodeAttribute::EType type);
void Indent(size_t depth, std::ostream& logStream);
std::string LogNameForObject(FbxObject* obj);
void PrintKeys(keyArray& keys, std::ostream& logStream);

#endif