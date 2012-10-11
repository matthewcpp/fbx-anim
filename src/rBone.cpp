#include "rBone.hpp"

rBone::rBone(const rString& name, rBone* parent){
	m_name = name;
	m_parent = parent;

	m_initialPosition = rVector3::ZeroVector;
	m_currentPosition = rVector3::ZeroVector;
}

rBone::~rBone(){
	DeleteChildren();
}

void rBone::DeleteChildren(){
	for (size_t i = 0; i < m_children.size(); i++)
		delete m_children[i];
}

rBone* rBone::AddChild(const rString& name){
	rBone* child = new rBone(name, this);
	m_children.push_back(child);

	return child;
}

bool rBone::DeleteChild(const rString& name){
	for (size_t i = 0; i < m_children.size(); i++){
		if (m_children[i]->Name() == name){
			delete m_children[i];
			m_children.erase(m_children.begin() + i);
			return true;
		}
	}

	return false;
}

rBone* rBone::FindChild(const rString& name){
	rBone* child = NULL;

	for (size_t i = 0; i < m_children.size(); i++){
		child = m_children[i];

		if (child->Name() == name){
			return child;
		}
		else{
			child = child->FindChild(name);
			if (child)
				break;
		}
	}

	return child;
}

size_t rBone::NumChildren() const{
	return m_children.size();
}

rBone* rBone::GetChild(size_t i) const{
	if (i >= m_children.size())
		return NULL;
	else
		return m_children[i];
}

rString rBone::Name() const{
	return m_name;
}

void rBone::Update(float animationTime, rAnimation* animation, const rMatrix4& parentTransform){
	rMatrix4 localTransform , globalTransform;
	animation->Evaluate(m_name,animationTime , localTransform);
	globalTransform = localTransform * parentTransform;

	//need to xform geometry
	m_currentPosition = globalTransform.GetTransformedVector3(rVector3::ZeroVector);

	size_t numChildren = m_children.size();
	for (size_t i = 0; i < numChildren; i++)
		m_children[i]->Update(animationTime, animation, globalTransform);
}

rBone* rBone::Parent() const{
	return m_parent;
}