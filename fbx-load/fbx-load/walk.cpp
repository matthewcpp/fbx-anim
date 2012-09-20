#include "walk.hpp"

void WalkScene(FbxScene* fbxScene, std::ostream& logStream){
	logStream << "Scene Graph:\n";
	WalkNode(fbxScene->GetRootNode(), 0, logStream);
}

void WalkNode(FbxNode* node, size_t depth, std::ostream& logStream){
	Indent(depth, logStream);
	logStream << node->GetName() << '(' << node->GetTypeName()<< ')' << std::endl;

	int childCount = node->GetChildCount();

	for (int i = 0; i < childCount; i++)
		WalkNode(node->GetChild(i), depth + 1 , logStream);
}

void Indent(size_t depth, std::ostream& logStream){
	for(size_t i = 0; i < depth; i++)
		logStream << "  ";
}