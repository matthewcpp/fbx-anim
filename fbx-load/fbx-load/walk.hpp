#ifndef WALK_HPP
#define WALK_HPP

#include <ostream>

#include <fbxsdk.h>

void WalkScene(FbxScene* fbxScene, std::ostream& logStream);

void WalkNode(FbxNode* node, size_t depth, std::ostream& logStream);

void Indent(size_t depth, std::ostream& logStream);

#endif