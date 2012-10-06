#ifndef R_MODEL_HPP
#define R_MODEL_HPP

#include <vector>
#include <fbxsdk.h>

#include "rTypes.hpp"

#include "rSkeleton.hpp"
#include "rAlignedBox3.hpp"
#include "rGameTime.hpp"

class rModel{
public:
	rModel();
	~rModel();

	void Clear();

	rSkeleton* CreateSkeleton(const rString& name);
	rSkeleton* GetSkeleton() const;

	rAlignedBox3 BoundingBox() const;
	void CalculateBoundingBox();

	void Update(const rGameTime& gameTime);

	void GetAnimationNames(rArrayString& names) const;
	bool PlayAnimation(const rString& name);
	void StopAnimation();

	rAnimation* CurrentAnimation() const;

private:
	rSkeleton* m_skeleton;
	rAlignedBox3 m_boundingBox;

public: //temp fbx anim
	FbxManager* fbxManager;
	FbxScene* fbxScene;

	void ClearFBX();
};

#endif