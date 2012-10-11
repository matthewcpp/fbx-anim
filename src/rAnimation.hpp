#ifndef R_ANIMATION_HPP
#define R_ANIMATION_HPP

#include <map>

#include "rTypes.hpp"
#include "rMatrix4.hpp"
#include "rMathUtil.hpp"

#include <fbxsdk.h>

typedef std::map<rString , FbxNode*> rBoneKeyframeSetMap;
typedef rBoneKeyframeSetMap::iterator rBoneKeyframeItr;

class rAnimation{
public:
	rAnimation(const rString& name);
	~rAnimation();

	bool Evaluate(const rString& boneName, float time, rMatrix4& matrix);
	bool DeleteBoneData(const rString& boneName);

	rString Name() const;

	static void FBXAMatrixToRMatrix(const FbxAMatrix& transform, rMatrix4& result);

private:
	static void HarvestFbxAMatrixData(const FbxAMatrix& matrix, rVector3& translate, rQuaternion& rotate, rVector3& scale);
	
private:
	rString m_name;

	rBoneKeyframeSetMap m_keyframeSets;

public: //temp while using fbx sdk
	void AddFbxNode(FbxNode* node);
	FbxAnimStack* animStack;
	FbxAnimEvaluator* fbxEvaluator;
};

#endif