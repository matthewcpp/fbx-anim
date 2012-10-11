#include "rModelLoader.hpp"

rModelLoader::rModelLoader(){
	m_fbxScene = NULL;
	m_fbxManager = NULL;
}

rModelLoader::~rModelLoader(){
	Clear();
}

void rModelLoader::Clear(){
	m_logPath = wxEmptyString;
	
	//this is temporary untill we factor out fbx sdk reliance
	return;

	if (m_fbxScene){ 
		m_fbxScene->Destroy();
		m_fbxScene = NULL;
	}
	if (m_fbxManager){
		m_fbxManager->Destroy();
		m_fbxManager = NULL;
	}
}

void rModelLoader::SetLogPath(const wxString& logPath){
	m_logPath = logPath;
}

bool rModelLoader::Load(const rString& path, rModel* model){
	model->Clear();

	m_fbxManager = FbxManager::Create();
	m_fbxScene = FbxScene::Create(m_fbxManager , "fbx scene");

	model->fbxManager = m_fbxManager;
	model->fbxScene = m_fbxScene;

	FbxImporter* fbxImporter = FbxImporter::Create(m_fbxManager, "fbx importer");
	bool result = fbxImporter->Initialize(path.c_str());
	result = fbxImporter->Import(m_fbxScene);

	if (result){
		WalkScene(model);
	}

	Clear();

	return result;
}

void rModelLoader::WalkScene(rModel* model){
	WalkNode(m_fbxScene->GetRootNode(), model);
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

void rModelLoader::LoadBoneAnimations(FbxNode* node, rSkeleton* skeleton, rBone* bone){
	int stackCount = m_fbxScene->GetSrcObjectCount(FBX_TYPE(FbxAnimStack));

	for (int i = 0; i < stackCount; i++){
		FbxAnimStack* animStack = FbxCast<FbxAnimStack>(m_fbxScene->GetSrcObject(FBX_TYPE(FbxAnimStack), i));
		LoadAnimationforBone(node, skeleton, bone, animStack);
	}
}

void rModelLoader::LoadAnimationforBone(FbxNode* node, rSkeleton* skeleton, rBone* bone, FbxAnimStack* animStack){
	rString animName = animStack->GetName();
	rAnimation* animation = skeleton->GetAnimation(animName);

	if (!animation){
		animation = skeleton->CreateAnimation(animName);
		animation->animStack = animStack;
	}

	//we will need to create a keyframe set for this bone and animation here
	animation->AddFbxNode(node);
}

void rModelLoader::ProcessSkeletonRoot(FbxNode* node, rModel* model){
	rSkeleton* skeleton = model->CreateSkeleton(node->GetName());
	rBone* root = skeleton->CreateRoot(node->GetName());
	LoadBoneAnimations(node , skeleton, root);

	LogSkeleton(node);

	int childCount = node->GetChildCount();
	for (int i = 0; i < childCount; i++){
		ProcessSkeletonNode(node->GetChild(i), skeleton, root);
	}
}

void rModelLoader::ProcessSkeletonNode(FbxNode* node, rSkeleton* skeleton, rBone* parentBone){
	FbxSkeleton* bone = FbxCast<FbxSkeleton>(node->GetNodeAttribute());
	
	rBone* childBone = parentBone->AddChild(node->GetName());
	LoadBoneAnimations(node , skeleton, childBone);

	LogSkeleton(node);

	FbxAMatrix bindTransform = GetBindTransform(node);
	rAnimation::FBXAMatrixToRMatrix(bindTransform, childBone->m_bindTransform);  //convert fbx anim matrix to r matrix
	childBone->m_initialPosition = childBone->m_bindTransform.GetTranslate();

	int childCount = node->GetChildCount();
	for (int i = 0; i < childCount; i++){
		ProcessSkeletonNode(node->GetChild(i), skeleton, childBone);
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

FbxAMatrix rModelLoader::GetBindTransform(FbxNode* pNode){
	FbxAMatrix localTransform;

	localTransform.SetT(pNode->LclTranslation.Get());
    localTransform.SetR(pNode->LclRotation.Get());
    localTransform.SetS(pNode->LclScaling.Get());

	return localTransform;
}