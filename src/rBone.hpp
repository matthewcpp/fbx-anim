#ifndef R_BONE_HPP
#define R_BONE_HPP

#include <vector>

#include "rTypes.hpp"
#include "rVector3.hpp"

struct rBone;
typedef std::vector <rBone*> rBoneList;

struct rBone{
public:
	rBone(const rString& name);
	~rBone();

	rBone* AddChild(const rString& name);
	rBone* FindChild(const rString& name);
	rString Name() const;

	rString m_name;
	rVector3 m_initialPosition;

	size_t NumChildren() const;
	rBone* GetChild(size_t i) const;

	
private:
	void DeleteChildren();

	rBoneList m_children;
};

#endif