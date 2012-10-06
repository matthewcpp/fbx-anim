#include "rSkeleton.hpp"

rSkeleton::rSkeleton(const rString& name){
	m_rootBone = NULL;
	m_name = name;
	m_currentAnimation = NULL;
	m_animationTime = 0.0f;
	m_isPlaying = false;
}

rSkeleton::~rSkeleton(){
	Clear();
}

void rSkeleton::Clear(){
	delete m_rootBone;
	m_rootBone = NULL;

	for (rAnimationItr it = m_animations.begin(); it != m_animations.end(); ++it)
		delete it->second;

	m_animations.clear();
}

rBone* rSkeleton::CreateRoot(const rString& rootName){
	if (m_rootBone)
		return NULL;

	m_rootBone = new rBone(rootName, NULL);
	return m_rootBone;
}

rBone* rSkeleton::CreateBone(rBone* parentBone, const rString& childName){
	if (!parentBone)
		return NULL;
	else
		return parentBone->AddChild(childName);
}

bool rSkeleton::DeleteBone(const rString& name){
	rBone* bone = GetBone(name);

	if (bone){
		if (bone->Parent())
			return bone->Parent()->DeleteChild(name);
		else{
			delete bone;
			return true;
		}
	}

	return false;
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

void rSkeleton::Update(const rGameTime& gameTime){
	if (m_currentAnimation && m_isPlaying){
		m_animationTime += gameTime.TimeDeltaSeconds();
		m_rootBone->Update(m_animationTime, m_currentAnimation, rMatrix4::IdentityMatrix);
	}
}

void rSkeleton::PauseAnimation(){
	m_isPlaying = false;
}

void rSkeleton::StopAnimation(){
	m_animationTime = 0.0f;
	m_isPlaying = false;
}

bool rSkeleton::PlayAnimation(const rString& name){
	rAnimation* anim = GetAnimation(name);

	if (anim){
		fbxEvaluator->SetContext(anim->animStack);
		return ActivateAnimation(anim);
	}
	else
		return false;
}

bool rSkeleton::ActivateAnimation(rAnimation* animation){
	m_currentAnimation = animation;
	m_animationTime = 0.0f;
	m_isPlaying = true;

	return true;
}

rAnimation* rSkeleton::CreateAnimation(const rString& name){
	if (GetAnimation(name))
		return NULL;

	rAnimation* anim = new rAnimation(name);

	anim->fbxEvaluator = fbxEvaluator; //temp for now

	m_animations[name] = anim;
	return anim;
}

rAnimation* rSkeleton::GetAnimation(const rString& name) const{
	rAnimationConstItr result = m_animations.find(name);

	if (result == m_animations.end())
		return NULL;
	else
		return result->second;

}

size_t rSkeleton::NumAnimations() const{
	return m_animations.size();
}

void rSkeleton::GetAnimationNames(rArrayString& names) const{
	names.clear();

	for (rAnimationConstItr it = m_animations.begin(); it != m_animations.end(); ++it)
		names.push_back(it->first);
}

rAnimation* rSkeleton::CurrentAnimation() const{
	return m_currentAnimation;
}

bool rSkeleton::IsPlayingAnimation() const{
	return m_isPlaying;
}