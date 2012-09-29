#include "rModel.hpp"

rModel::rModel(){
	m_skeleton = NULL;
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
}

rSkeleton* rModel::CreateSkeleton(const rString& name){
	m_skeleton = new rSkeleton(name);
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