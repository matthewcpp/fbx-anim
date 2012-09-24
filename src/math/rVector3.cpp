#include "rVector3.hpp"

void rVector3::Set(float xx, float yy , float zz){
	x = xx;
	y = yy;
	z = zz;
}

rVector3 rVector3::operator +(const rVector3& v) const{
	return rVector3(x + v.x , y + v.y , z + v.z);
}

rVector3& rVector3::operator +=(const rVector3& v){
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

rVector3 rVector3::operator -(const rVector3& v) const{
	return rVector3(x - v.x , y - v.y , z - v.z);
}

rVector3& rVector3::operator -=(const rVector3& v){
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

rVector3 rVector3::operator *(float k) const{
	return rVector3(x * k , y * k , z * k);
}

rVector3& rVector3::operator *=(float k){
	x *= k;
	y *= k;
	z *= k;

	return *this;
}

bool rVector3::operator==(const rVector3& v)const{
	return x == v.x && y == v.y && z == v.z;
}

bool rVector3::operator!=(const rVector3& v)const{
	return !(*this == v);
}

float rVector3::Distance(const rVector3& v) const{
	rVector3 d = v - *this;
	return std::sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
}

float rVector3::Length() const{
	return std::sqrt ( (x * x) + (y * y) + (z * z ) );
}

float rVector3::LengthSquared() const{
	return (x * x) + (y * y) + (z * z );
}

rVector3& rVector3::Normalize(){
	float l = Length();

	x /= l;
	y /= l;
	z /= l;

	return *this;
}

rVector3 rVector3::GetNormalized() const{
	rVector3 v = *this;
	v.Normalize();
	return v;
}

rVector3 rVector3::Cross(const rVector3& v) const{
	return rVector3	(	y * v.z - z * v.y,
						z * v.x - x * v.z,
						x * v.y - y * v.x);
}

float rVector3::Dot(const rVector3& v) const{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

rVector3 rVector3::operator-() const{
	return rVector3(-x , -y , -z);
}

const rVector3 rVector3::ZeroVector = rVector3(0.0f,0.0f,0.0f);
const rVector3 rVector3::OneVector = rVector3(1.0f,1.0f,1.0f);
const rVector3 rVector3::UpVector = rVector3(0.0f,1.0f,0.0f);
const rVector3 rVector3::DownVector = rVector3(0.0f,-1.0f,0.0f);
const rVector3 rVector3::ForwardVector = rVector3(0.0f , 0.0f , -1.0f);
const rVector3 rVector3::BackwardVector = rVector3(0.0f , 0.0f , 1.0f);
const rVector3 rVector3::RightVector = rVector3(1.0f , 0.0f , 0.0f);
const rVector3 rVector3::LeftVector= rVector3(-1.0f , 0.0f ,0.0f);