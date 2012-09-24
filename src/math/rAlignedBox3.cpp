#include "rAlignedBox3.hpp"

rAlignedBox3::rAlignedBox3(const rVector3& mmax , const rVector3& mmin){
	Set(mmax , mmin);
}

rAlignedBox3::rAlignedBox3(float maxX , float maxY , float maxZ , float minX , float minY , float minZ){
	max.Set(maxX, maxY , maxZ);
	min.Set(minX , minY , minZ);
}

rAlignedBox3::rAlignedBox3(const rVector3& center , float width , float height , float depth){
	Set(center, width, height, depth);
}

void rAlignedBox3::Set(const rVector3& mmax , const rVector3& mmin){
	max = mmax;
	min = mmin;
}

void rAlignedBox3::Set(const rVector3& center , float width , float height , float depth){

	width /= 2.0f;
	height /= 2.0f;
	depth /= 2.0f;

	max.x = center.x + width;
	max.y = center.y + height;
	max.z = center.z + depth;

	min.x = center.x - width;
	min.y = center.y - height;
	min.z = center.z - depth;
}

bool rAlignedBox3::ContainsPoint(const rVector3& p) const{
	return	p.x >= min.x && p.x <= max.x &&
			p.y >= min.y && p.y <= max.y &&
			p.z >= min.z && p.z <= max.z;
};

bool rAlignedBox3::ContainsBox(const rAlignedBox3& b) const{
	return ContainsPoint(b.max) && ContainsPoint(b.min);
}

rVector3 rAlignedBox3::Center() const{
	return (max + min) * 0.5f;
}

bool rAlignedBox3::IntersectsBox(const rAlignedBox3& b) const{
	if (min.x > b.max.x) return false;
	if (max.x < b.min.x) return false;
	if (min.y > b.max.y) return false;
	if (max.y < b.min.y) return false;
	if (min.z > b.max.z) return false;
	if (max.z < b.min.z) return false;

	return true;
}

bool rAlignedBox3::BoxPointsAreValid(const rVector3& max , const rVector3& min){
	return min.x <= max.x && min.y <= max.y && min.z <= max.z;
}

bool rAlignedBox3::IsValid() const{
	return BoxPointsAreValid(max , min);
}

float rAlignedBox3::Width() const{
	return std::abs(max.x - min.x);
}

float rAlignedBox3::Height() const{
	return  std::abs(max.y - min.y);
}

float rAlignedBox3::Depth() const{
	return  std::abs(max.z - min.z);
}

void rAlignedBox3::SetCenter(const rVector3& center){
	float w = Width() * 0.5f;
	float h = Height() * 0.5f;
	float d = Depth() * 0.5f;

	max.x = center.x + w;
	max.y = center.y + h;
	max.z = center.z + d;

	min.x = center.x - w;
	min.y = center.y - h;
	min.z = center.z - d;
}

void rAlignedBox3::GetCorners(rVector3 corners[]) const{
	corners[0].Set(min.x , max.y , max.z);
	corners[1] = max;
	corners[2].Set(max.x , min.y , max.z);
	corners[3].Set(min.x , min.y, max.z);

	corners[4].Set(min.x , max.y , min.z);
	corners[5].Set(max.x , max.y , min.z);
	corners[6].Set(max.x , min.y , min.z);
	corners[7] = min;
}

void rAlignedBox3::AddBox(const rAlignedBox3& box){
	AddPoint(box.min);
	AddPoint(box.max);
}

void rAlignedBox3::AddPoint(const rVector3& pt){
	if (pt.x < min.x) min.x = pt.x;
	if (pt.y < min.y) min.y = pt.y;
	if (pt.z < min.z) min.z = pt.z;
	
	if (pt.x > max.x) max.x = pt.x;
	if (pt.y > max.y) max.y = pt.y;
	if (pt.z > max.z) max.z = pt.z;
}

void rAlignedBox3::Empty(){
	*this = rAlignedBox3::NullBox;
}

const rAlignedBox3 rAlignedBox3::NullBox = rAlignedBox3(rVector3::ZeroVector ,rVector3::ZeroVector);