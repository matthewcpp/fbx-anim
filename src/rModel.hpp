#ifndef R_MODEL_HPP
#define R_MODEL_HPP

#include <vector>

#include "rTypes.hpp"

#include "rSkeleton.hpp"
#include "rAlignedBox3.hpp"

class rModel{
public:
	rModel();
	~rModel();

	void Clear();

	rSkeleton* CreateSkeleton(const rString& name);
	rSkeleton* GetSkeleton() const;

	rAlignedBox3 BoundingBox() const;
	void CalculateBoundingBox();

private:
	rSkeleton* m_skeleton;
	rAlignedBox3 m_boundingBox;
};

#endif