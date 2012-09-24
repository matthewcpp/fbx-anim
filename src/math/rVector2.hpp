#ifndef R_POINT2_T_HPP
#define R_POINT2_T_HPP

#include <cmath>

struct rVector2{

	rVector2(){}
	rVector2(float xx , float yy) : x(xx) , y(yy) {}

	void Set(float xx , float yy);

	float Distance(const rVector2& p) const;
	float DistanceSquared(const rVector2& p) const;

	static rVector2 Normalize(const rVector2& v);

	float Dot(const rVector2& v) const;
	float Cross(const rVector2 v) const;

	float Length() const;
	float LengthSquared() const;

	void Normalize();

	rVector2 operator+(const rVector2& p) const;
	rVector2& operator+=(const rVector2& p);
	rVector2 operator-(const rVector2& p) const;
	rVector2& operator-=(const rVector2& p);
	rVector2 operator*(float k) const;
	rVector2& operator*=(float k);

	bool operator==(const rVector2& v) const;
	bool operator!=(const rVector2& v) const;

	static const rVector2 ZeroVector;

	float x;
	float y;
};

#endif