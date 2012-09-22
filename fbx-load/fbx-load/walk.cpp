#include "walk.hpp"

void WalkAssets(FbxScene* scene, std::ostream& logStream){
	WalkTextures(scene, logStream);
	WalkMaterials(scene, logStream);
}

void WalkMaterials(FbxScene* scene, std::ostream& logStream){
	FbxArray< FbxSurfaceMaterial * > materials;
	scene->FillMaterialArray(materials);
	
	logStream << "Materials:\n";

	for (int i = 0; i < materials.Size(); i++)
		logStream << materials[i]->GetName() << "\n";

	logStream << std::endl;
}

void WalkTextures(FbxScene* scene, std::ostream& logStream){
	FbxArray< FbxTexture * > textures;
	scene->FillTextureArray(textures);
	
	logStream << "Textures:\n";

	// it seems like texture name == file name?  cant find another way to  figure this out
	for (int i = 0; i < textures.Size(); i++){
		logStream << textures[i]->GetName() << '('<<textures[i]->GetTextureType() <<")\n";
	}

	logStream << std::endl;
}

void WalkScene(FbxScene* fbxScene, std::ostream& logStream){
	logStream << "Scene Graph: Name(Type)\n";
	WalkNode(fbxScene, fbxScene->GetRootNode(), 0, logStream);
	logStream << "\n\n" << std::endl;
}

void WalkNode(FbxScene* fbxScene, FbxNode* node, size_t depth, std::ostream& logStream){
	Indent(depth, logStream);
	logStream << node->GetName() << '(' << node->GetTypeName()<< ")\n";;

	if (NodeAttributeIsType(node, FbxNodeAttribute::eSkeleton))
		ProcessSkeletonNode(fbxScene, node);

	int childCount = node->GetChildCount();

	for (int i = 0; i < childCount; i++)
		WalkNode(fbxScene, node->GetChild(i), depth + 1 , logStream);
}

void ProcessSkeletonNode(FbxScene* fbxScene, FbxNode* node){
	FbxSkeleton* bone = FbxCast<FbxSkeleton>(node->GetNodeAttribute());
	std::string logname = LogNameForObject(bone);
	std::ofstream log(logname.c_str());

	FbxDouble3 pos = node->LclTranslation;
	log << bone->GetName();
	log << "\tPosition:" << pos[0] <<' ' << pos[1] << ' '<< pos[2];
	log << "\tLength:" << bone->LimbLength;
	log << "\tSize: "<< bone->Size <<'\n';
	log << "parent bone: ";

	FbxNode* parent = node->GetParent();
	if (parent && NodeAttributeIsType(parent, FbxNodeAttribute::eSkeleton))
		log << parent->GetName() << '\n';
	else
		log << "null\n";

	WalkAnimations(node, fbxScene, log);

	log.close();
}

//each animation stack is an animation track

void WalkAnimations(FbxNode* node, FbxScene* fbxScene, std::ostream& logStream){
	logStream << "Animations:\n";
	
	int stackCount = fbxScene->GetSrcObjectCount(FBX_TYPE(FbxAnimStack));

	for (int i = 0; i < stackCount; i++){
		FbxAnimStack* animStack = FbxCast<FbxAnimStack>(fbxScene->GetSrcObject(FBX_TYPE(FbxAnimStack), i));
		WalkAnimation(node, animStack, logStream);
	}

	logStream << "\n\n" << std::endl;
}

//each stack can have any number of layers, however we are only interested in the base layer (0)

void WalkAnimation(FbxNode* node, FbxAnimStack* animStack, std::ostream& logStream){
	Indent(1,logStream);
	logStream << animStack->GetName()<< '\n';
	FbxAnimLayer* baseLayer = animStack->GetSrcObject(FBX_TYPE(FbxAnimLayer), 0);
	
	//we can extract animation curves from the node for the base animation layer now
	GetCurveData("Translate X", node->LclTranslation.GetCurve(baseLayer, FBXSDK_CURVENODE_COMPONENT_X), logStream);
	GetCurveData("Translate Y", node->LclTranslation.GetCurve(baseLayer, FBXSDK_CURVENODE_COMPONENT_Y), logStream);
	GetCurveData("Translate Z", node->LclTranslation.GetCurve(baseLayer, FBXSDK_CURVENODE_COMPONENT_Z), logStream);
	GetCurveData("Rotate X", node->LclRotation.GetCurve(baseLayer, FBXSDK_CURVENODE_COMPONENT_X), logStream);
	GetCurveData("Rotate Y", node->LclRotation.GetCurve(baseLayer, FBXSDK_CURVENODE_COMPONENT_Y), logStream);
	GetCurveData("Rotate Z", node->LclRotation.GetCurve(baseLayer, FBXSDK_CURVENODE_COMPONENT_Z), logStream);
	GetCurveData("Scale X", node->LclScaling.GetCurve(baseLayer, FBXSDK_CURVENODE_COMPONENT_X), logStream);
	GetCurveData("Scale Y", node->LclScaling.GetCurve(baseLayer, FBXSDK_CURVENODE_COMPONENT_Y), logStream);
	GetCurveData("Scale Z", node->LclScaling.GetCurve(baseLayer, FBXSDK_CURVENODE_COMPONENT_Z), logStream);
}

void GetCurveData(const std::string& label, FbxAnimCurve* animCurve, std::ostream& logStream){
	Indent(2, logStream);

	if (animCurve){
		FbxTimeSpan interval;
		animCurve->GetTimeInterval(interval);
		logStream << label <<"\t(" <<animCurve->KeyGetCount() << " keys) - " << interval.GetDuration().GetSecondDouble() << " seconds\n";
		GetKeyValues(animCurve, logStream);
	}
	else
		logStream << label <<"\t(0 keys)\n";
}

void GetKeyValues(FbxAnimCurve* animCurve, std::ostream& logStream){
	int keyCount = animCurve->KeyGetCount();

	keyArray keys;
	keyInfo key;

	FbxTime time;
	float val;

	for (int i = 0; i < keyCount; i++){
		time = animCurve->KeyGetTime(i);

		key.time = (float)time.GetSecondDouble();
		key.value = animCurve->KeyGetValue(i);

		keys.push_back(key);
	}

	PrintKeys(keys, logStream);
}

void Indent(size_t depth, std::ostream& logStream){
	for(size_t i = 0; i < depth; i++)
		logStream << "  ";
}

std::string LogNameForObject(FbxObject* obj){
	std::stringstream logname;
	logname << "log/";
	logname << obj->GetName();
	logname << ".log";
	return logname.str();
}

bool NodeAttributeIsType(FbxNode* node, FbxNodeAttribute::EType type){
	if (!node)
		return false;

	FbxNodeAttribute* attribute = node->GetNodeAttribute();

	if (!attribute)
		return false;

	return attribute->GetAttributeType() == type;
}

void PrintKeys(keyArray& keys, std::ostream& logStream){
	Indent(3, logStream);
	logStream << "Time:\t";
	for (size_t i = 0; i < keys.size(); i++)
		logStream << '\t' << keys[i].time; 
	
	logStream << "\n";

	Indent(3, logStream);
	logStream << "Value:";
	for (size_t i = 0; i < keys.size(); i++)
		logStream << '\t' << keys[i].value;

	logStream << std::endl;
}