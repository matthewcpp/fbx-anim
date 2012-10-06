#ifndef R_SKELETON_HPP
#define R_SKELETON_HPP

#include <fbxsdk.h>

#include <map>

#include "rTypes.hpp"
#include "rBone.hpp"

#include "rAlignedBox3.hpp"
#include "rAnimation.hpp"
#include "rGameTime.hpp"

typedef std::map<rString, rAnimation*> rAnimationMap;
typedef rAnimationMap::iterator rAnimationItr;
typedef rAnimationMap::const_iterator rAnimationConstItr;

class rSkeleton{
public:
	rSkeleton(const rString& name);
	~rSkeleton();

	rBone* CreateRoot(const rString& rootName);
	rBone* CreateBone(rBone* parentBone, const rString& childName);
	rBone* GetBone(const rString& boneName);
	void GetBones(rBoneList& bones) const;
	rBone* GetRoot();
	bool DeleteBone(const rString& name);

	void Update(const rGameTime& gameTime);

	void Clear();

	rAlignedBox3 CalculateBoundingBox() const;

	bool PlayAnimation(const rString& name);
	void StopAnimation();
	void PauseAnimation();

	bool IsPlayingAnimation() const;

	rAnimation* CreateAnimation(const rString& name);
	rAnimation* GetAnimation(const rString& name) const;
	rAnimation* CurrentAnimation() const;
	size_t NumAnimations() const;
	void GetAnimationNames(rArrayString& names) const;

private:

	bool ActivateAnimation(rAnimation* animation);
	void AddBoneAndChildrenToList(rBone* bone, rBoneList& boneList) const;

	rBone* m_rootBone;
	rString m_name;

	rAnimationMap m_animations;
	rAnimation* m_currentAnimation;
	float m_animationTime;
	bool m_isPlaying;

public: //temporary while we are using FBX
	FbxAnimEvaluator* fbxEvaluator;
};

#endif