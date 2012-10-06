#include "rModel.hpp"

rModel::rModel(){
	m_skeleton = NULL;

	fbxScene = NULL;
	fbxManager = NULL;
}

rModel::~rModel(){
	Clear();
}

void rModel::Clear(){
	if (m_skeleton){
		delete m_skeleton;
		m_skeleton = NULL;
	}

	m_boundingBox.Empty();

	ClearFBX();
}

rSkeleton* rModel::CreateSkeleton(const rString& name){
	m_skeleton = new rSkeleton(name);
	m_skeleton->fbxEvaluator = fbxScene->GetEvaluator(); // temp for now
	return m_skeleton;
}

rSkeleton* rModel::GetSkeleton() const{
	return m_skeleton;
}

rAlignedBox3 rModel::BoundingBox() const{
	return m_boundingBox;
}

void rModel::CalculateBoundingBox(){
	//this is only temporary
	if (m_skeleton)
		m_boundingBox = m_skeleton->CalculateBoundingBox();
}

void rModel::GetAnimationNames(rArrayString& names) const{
	names.clear();
	int stackCount = fbxScene->GetSrcObjectCount(FBX_TYPE(FbxAnimStack));

	for (int i = 0; i < stackCount; i++){
		FbxAnimStack* animStack = FbxCast<FbxAnimStack>(fbxScene->GetSrcObject(FBX_TYPE(FbxAnimStack), i));
		names.push_back(animStack->GetName());
	}
}

void rModel::Update(const rGameTime& gameTime){
	if (m_skeleton)
		return m_skeleton->Update(gameTime);
}

bool rModel::PlayAnimation(const rString& name){
	if (m_skeleton)
		return m_skeleton->PlayAnimation(name);
	else
		return false;
}

void rModel::StopAnimation(){
	if (m_skeleton)
		m_skeleton->StopAnimation();
}

rAnimation* rModel::CurrentAnimation() const{
	if (m_skeleton)
		return m_skeleton->CurrentAnimation();
	else
		return NULL;
}

void rModel::ClearFBX(){
	if (fbxScene){ 
		fbxScene->Destroy();
		fbxScene = NULL;
	}
	if (fbxManager){
		fbxManager->Destroy();
		fbxManager = NULL;
	}
}