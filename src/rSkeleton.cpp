#include "rSkeleton.hpp"

rSkeleton::rSkeleton(const rString& name){
	m_rootBone = NULL;
	m_name = name;
}

rSkeleton::~rSkeleton(){
	Clear();
}

void rSkeleton::Clear(){
	delete m_rootBone;
	m_rootBone = NULL;
}

rBone* rSkeleton::CreateRoot(const rString& rootName){
	if (m_rootBone)
		return NULL;

	m_rootBone = new rBone(rootName);
	return m_rootBone;
}

rBone* rSkeleton::CreateBone(rBone* parentBone, const rString& childName){
	if (!parentBone)
		return NULL;
	else
		return parentBone->AddChild(childName);
}

rBone* rSkeleton::GetBone(const rString& boneName){
	if (m_rootBone->Name() == boneName)
		return m_rootBone;
	else
		return m_rootBone->FindChild(boneName);
}

rBone* rSkeleton::GetRoot(){
	return m_rootBone;
}

void rSkeleton::GetBones(rBoneList& bones) const{
	bones.clear();

	AddBoneAndChildrenToList(m_rootBone, bones);
}

void rSkeleton::AddBoneAndChildrenToList(rBone* bone, rBoneList& boneList) const{
	boneList.push_back(bone);

	size_t numChildren = bone->NumChildren();
	for (size_t i =0; i < numChildren; i++){
		AddBoneAndChildrenToList(bone->GetChild(i), boneList);
	}
}

rAlignedBox3 rSkeleton::CalculateBoundingBox() const{
	rAlignedBox3 boundingBox;
	rBoneList bones;
	GetBones(bones);

	for (size_t i = 0; i < bones.size(); i++)
		boundingBox.AddPoint(bones[i]->m_initialPosition);

	return boundingBox;
}