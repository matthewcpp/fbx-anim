#include "rAnimation.hpp"

rAnimation::rAnimation(const rString& name){
	m_name = name;
}

rAnimation::~rAnimation(){
}

rString rAnimation::Name() const{
	return m_name;
}

bool rAnimation::Evaluate(const rString& boneName, float time, rMatrix4& matrix){
	//this will change completely when we remove reliance on fbx sdk for animation

	rBoneKeyframeItr it = m_keyframeSets.find(boneName);
	if (it == m_keyframeSets.end())
		return false;

	FbxNode* node = it->second;
	FbxTime animTime;
	animTime.SetSecondDouble(time);
	
	FbxAMatrix transform = fbxEvaluator->GetNodeLocalTransform(node, animTime);
	FBXAMatrixToRMatrix(transform, matrix);

	return true;
}

bool rAnimation::DeleteBoneData(const rString& boneName){
	//this will need to do more when not relying on FBX
	m_keyframeSets.erase(boneName);
	return true;
}

void rAnimation::AddFbxNode(FbxNode* node){
	rString boneName = node->GetName();
	m_keyframeSets[boneName] = node;
}

void rAnimation::FBXAMatrixToRMatrix(const FbxAMatrix& transform, rMatrix4& result){
	rVector3 translate, scale;
	rQuaternion rotate;
	HarvestFbxAMatrixData(transform, translate, rotate, scale);
	rMath::SetTransformMatrix(translate,rotate,scale, result);
}

void rAnimation::HarvestFbxAMatrixData(const FbxAMatrix& matrix, rVector3& translate, rQuaternion& rotate, rVector3& scale){
	FbxVector4 v4;
	FbxQuaternion q;

	v4 = matrix.GetT();
	translate.x = v4[0]; translate.y = v4[1]; translate.z = v4[2];
	v4 = matrix.GetS();
	scale.x = v4[0]; scale.y = v4[1]; scale.z = v4[2];
	q = matrix.GetQ();
	rotate.x = q[0], rotate.y = q[1], rotate.z = q[2], rotate.w = q[3];
}