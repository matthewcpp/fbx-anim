#include "walk.hpp"

void WalkScene(FbxScene* fbxScene, std::ostream& logStream){
	logStream << "Scene Graph: Name(Type)\n";
	WalkNode(fbxScene->GetRootNode(), 0, logStream);
	logStream << "\n\n" << std::endl;
}

void WalkNode(FbxNode* node, size_t depth, std::ostream& logStream){
	Indent(depth, logStream);
	logStream << node->GetName() << '(' << node->GetTypeName()<< ")\n";;

	int childCount = node->GetChildCount();

	for (int i = 0; i < childCount; i++)
		WalkNode(node->GetChild(i), depth + 1 , logStream);
}

//each animation stack is an animation track

void WalkAnimations(FbxScene* fbxScene, std::ostream& logStream){
	logStream << "Animations:\n";
	
	int stackCount = fbxScene->GetSrcObjectCount(FBX_TYPE(FbxAnimStack));

	for (int i = 0; i < stackCount; i++){
		FbxAnimStack* animStack = FbxCast<FbxAnimStack>(fbxScene->GetSrcObject(FBX_TYPE(FbxAnimStack), i));
		WalkAnimation(animStack, logStream);
	}

	logStream << "\n\n" << std::endl;
}

//each stack can have any number of layers, however we are only intereste din the base layer (0)

void WalkAnimation(FbxAnimStack* animStack, std::ostream& logStream){
	logStream << animStack->GetName()<< '\n';
	FbxAnimLayer* baseLayer = animStack->GetSrcObject(FBX_TYPE(FbxAnimLayer), 0);

	/*	at this point we would need a fbx node such as a 
		joint or bone in order to get its cuve for a partiular propery, eg. Tx, Ry
	*/
}




void Indent(size_t depth, std::ostream& logStream){
	for(size_t i = 0; i < depth; i++)
		logStream << "  ";
}