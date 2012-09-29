#include "rBone.hpp"

rBone::rBone(const rString& name){
	m_name = name;
	m_initialPosition = rVector3::ZeroVector;
}

rBone::~rBone(){
	DeleteChildren();
}

void rBone::DeleteChildren(){
	for (size_t i = 0; i < m_children.size(); i++)
		delete m_children[i];
}

rBone* rBone::AddChild(const rString& name){
	rBone* child = new rBone(name);
	m_children.push_back(child);

	return child;
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