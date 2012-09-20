#include "rVector2.hpp"


float rVector2::Length() const{
	return std::sqrt(x * x + y * y);
}


float rVector2::LengthSquared() const{
	return x * x + y * y;
}


rVector2 rVector2::Normalize(const rVector2& v){
	float l = v.Length();
	return rVector2(v.x / l , v.y / l);
}


void rVector2::Normalize(){
	float l = Length();
	x /= l;
	y /= l;
}


float rVector2::Dot(const rVector2& v) const{
	return x * v.x + y *v.y;
}


float rVector2::Distance(const rVector2& p) const{
	rVector2 d = p - *this;
	return std::sqrt(d.x * d.x + d.y * d.y);
}


float rVector2::DistanceSquared(const rVector2& p) const{
	rVector2 d = p - *this;
	return d.x * d.x + d.y * d.y;
}


void rVector2::Set(float xx , float yy){
	x = xx;
	y = yy;
}


rVector2 rVector2::operator+(const rVector2& p) const{
	return rVector2(x + p.x , y + p.y);
}


rVector2& rVector2::operator+=(const rVector2& p){
	x += p.x;
	y += p.y;

	return *this;
}


rVector2 rVector2::operator-(const rVector2& p) const{
	return rVector2(x - p.x , y - p.y);
}


rVector2& rVector2::operator-=(const rVector2& p){
	x -= p.x;
	y -= p.y;

	return *this;
}


rVector2 rVector2::operator*(float k) const{
	return rVector2( x * k , y * k);
}


rVector2& rVector2::operator*=(float k){
	x *= k;
	y *= k;

	return *this;
}


bool rVector2::operator==(const rVector2& v)const{
	return x == v.x && y == v.y;
}


bool rVector2::operator!=(const rVector2& v)const{
	return !(*this == v);
}

float rVector2::Cross(const rVector2 v) const{
	return x * v.y - v.x * y;
}

const rVector2 rVector2::ZeroVector = rVector2(0,0);
