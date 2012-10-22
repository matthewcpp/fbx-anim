#ifndef R_BONE_HPP
#define R_BONE_HPP

#include <vector>
#include <fbxsdk.h>

#include "rTypes.hpp"
#include "rVector3.hpp"

#include "rAnimation.hpp"
#include "rMatrix4.hpp"

struct rBone;
typedef std::vector <rBone*> rBoneList;

struct rBone{
public:
	rBone(const rString& name, rBone* parent);
	~rBone();

	rBone* AddChild(const rString& name);
	bool DeleteChild(const rString& name);
	rBone* FindChild(const rString& name);
	
	rBone* Parent() const;
	rString Name() const;

	rString m_name;
	
	rMatrix4 m_bindTransform;
	rVector3 m_initialPosition;
	rVector3 m_currentPosition;

	size_t NumChildren() const;
	rBone* GetChild(size_t i) const;

	rVector3 GetGlobalPosition();
	virtual void Update(float animationTime, rAnimation* animation, const rMatrix4& parentTransform);
	
private:
	void DeleteChildren();

	rBoneList m_children;
	rBone* m_parent;

public: //temp while we are using fbx sdk
	FbxNode* fbxNode;
};

#endif