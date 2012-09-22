#ifndef R_ALIGNEDBOX3_HPP
#define R_ALIGNEDBOX3_HPP

#include <cmath>

#include "rVector3.hpp"
#include "rMathUtil.hpp"

struct rAlignedBox3{

	rAlignedBox3(){}
	rAlignedBox3(const rVector3& mmax , const rVector3& mmin);
	rAlignedBox3(float maxX , float maxY , float maxZ , float minX , float minY , float minZ);
	rAlignedBox3(const rVector3& center , float width , float height , float depth);

	float Width() const;
	float Height() const;
	float Depth() const;

	bool ContainsPoint(const rVector3& p) const;
	bool ContainsBox(const rAlignedBox3& b) const;
	bool IntersectsBox(const rAlignedBox3& b) const;
	
	void AddBox(const rAlignedBox3& box);
	void AddPoint(const rVector3& pt);

	void GetCorners(rVector3 corners[]) const;

	bool IsValid() const;
	void Empty();

	void Set(const rVector3& mmax , const rVector3& mmin);
	void Set(const rVector3& center , float width , float height , float depth);

	rVector3 Center() const;
	void SetCenter(const rVector3& center);

	rVector3 max;
	rVector3 min;

	static bool BoxPointsAreValid(const rVector3& max , const rVector3& min);
	static const rAlignedBox3 NullBox;
};

#endif