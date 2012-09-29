#include "rModelLoader.hpp"

rModelLoader::rModelLoader(){
	fbxScene = NULL;
	fbxManager = NULL;
}

rModelLoader::~rModelLoader(){
	Clear();
}

void rModelLoader::Clear(){
	m_logPath = wxEmptyString;

	if (fbxScene){ 
		fbxScene->Destroy();
		fbxScene = NULL;
	}
	if (fbxManager){
		fbxManager->Destroy();
		fbxManager = NULL;
	}
}

void rModelLoader::SetLogPath(const wxString& logPath){
	m_logPath = logPath;
}

bool rModelLoader::Load(const rString& path, rModel* model){
	fbxManager = FbxManager::Create();
	fbxScene = FbxScene::Create(fbxManager , "fbx scene");

	FbxImporter* fbxImporter = FbxImporter::Create(fbxManager, "fbx importer");
	bool result = fbxImporter->Initialize(path.c_str());
	result = fbxImporter->Import(fbxScene);

	if (result){
		WalkScene(model);
	}

	Clear();

	return result;
}

void rModelLoader::WalkScene(rModel* model){
	WalkNode(fbxScene->GetRootNode(), model);
}

void rModelLoader::WalkNode(FbxNode* node, rModel* model){
	if (NodeAttributeIsType(node, FbxNodeAttribute::eSkeleton)){
		ProcessSkeletonRoot(node, model);
	}
	else{
		int childCount = node->GetChildCount();

		for (int i = 0; i < childCount; i++){
			WalkNode(node->GetChild(i), model);
		}
	}
}

void rModelLoader::ProcessSkeletonRoot(FbxNode* node, rModel* model){
	rSkeleton* skeleton = model->CreateSkeleton(node->GetName());
	rBone* root = skeleton->CreateRoot(node->GetName());

	LogSkeleton(node);

	int childCount = node->GetChildCount();
	for (int i = 0; i < childCount; i++){
		ProcessSkeletonNode(node->GetChild(i), model, root);
	}
}

void rModelLoader::ProcessSkeletonNode(FbxNode* node, rModel* model, rBone* parentBone){
	FbxSkeleton* bone = FbxCast<FbxSkeleton>(node->GetNodeAttribute());
	
	rBone* childBone = parentBone->AddChild(node->GetName());

	LogSkeleton(node);

	FbxAMatrix m = GetGlobalDefaultPosition(node);
	FbxVector4 pos = m.GetT();
	childBone->m_initialPosition = rVector3(pos[0], pos[1], pos[2]);

	int childCount = node->GetChildCount();
	for (int i = 0; i < childCount; i++){
		ProcessSkeletonNode(node->GetChild(i), model, childBone);
	}
}

bool rModelLoader::NodeAttributeIsType(FbxNode* node, FbxNodeAttribute::EType type){
	if (!node)
		return false;

	FbxNodeAttribute* attribute = node->GetNodeAttribute();

	if (!attribute)
		return false;

	return attribute->GetAttributeType() == type;
}

void rModelLoader::Indent(size_t depth, wxTextOutputStream& logStream){
		for(size_t i = 0; i < depth; i++){
			logStream << "  ";
		}
}

wxString rModelLoader::LogPathForObject(FbxObject* obj){
	wxStringOutputStream str;
	wxTextOutputStream logname(str);
	logname << m_logPath;
	logname << obj->GetName();
	logname << ".log";
	return str.GetString();
}

void rModelLoader::LogSkeleton(FbxNode* node){
	FbxSkeleton* bone = FbxCast<FbxSkeleton>(node->GetNodeAttribute());
	wxFileOutputStream file(LogPathForObject(node));
	wxTextOutputStream log(file);

	FbxDouble3 pos = node->LclTranslation;
	log << node->GetName();
	log << "\tPosition:" << pos[0] <<' ' << pos[1] << ' '<< pos[2];
	log << "\tLength:" << bone->LimbLength;
	log << "\tSize: "<< bone->Size <<'\n';
	log << "parent bone: ";

	FbxNode* parent = node->GetParent();
	if (parent && NodeAttributeIsType(parent, FbxNodeAttribute::eSkeleton))
		log << parent->GetName() << '\n';
	else
		log << "null\n";
}

FbxAMatrix rModelLoader::GetGlobalDefaultPosition(FbxNode* pNode)
{
    FbxAMatrix localPosition;
    FbxAMatrix globalPosition;
    FbxAMatrix parentGlobalPosition;

    localPosition.SetT(pNode->LclTranslation.Get());
    localPosition.SetR(pNode->LclRotation.Get());
    localPosition.SetS(pNode->LclScaling.Get());

    if (pNode->GetParent()){
        parentGlobalPosition = GetGlobalDefaultPosition(pNode->GetParent());
        globalPosition = parentGlobalPosition * localPosition;
    }
    else{
        globalPosition = localPosition;
    }

    return globalPosition;
}