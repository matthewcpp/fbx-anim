#ifndef R_SKELETON_HPP
#define R_SKELETON_HPP

#include "rTypes.hpp"
#include "rBone.hpp"

#include "rAlignedBox3.hpp"


class rSkeleton{
public:
	rSkeleton(const rString& name);
	~rSkeleton();

	rBone* CreateRoot(const rString& rootName);
	rBone* CreateBone(rBone* parentBone, const rString& childName);
	rBone* GetBone(const rString& boneName);
	void GetBones(rBoneList& bones) const;
	rBone* GetRoot();

	void Clear();

	rAlignedBox3 CalculateBoundingBox() const;

private:

	void AddBoneAndChildrenToList(rBone* bone, rBoneList& boneList) const;

	rBone* m_rootBone;
	rString m_name;
};

#endif