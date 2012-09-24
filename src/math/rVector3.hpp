#ifndef R_VECTOR3_HPP
#define R_VECTOR3_HPP

#include <cmath>

struct rVector3{
	rVector3(){}
	rVector3(float xx, float yy , float zz) : x(xx) , y (yy) , z (zz){}

	float Distance(const rVector3& v) const;
	float Length() const;
	float LengthSquared() const;

	rVector3& Normalize();
	rVector3 GetNormalized() const;

	rVector3 Cross(const rVector3& v) const;
	float Dot(const rVector3& v) const;


	void Set(float xx, float yy , float zz);

	rVector3 operator +(const rVector3& v) const;
	rVector3& operator +=(const rVector3& v);
	rVector3 operator -(const rVector3& v) const;
	rVector3& operator -=(const rVector3& v);
	rVector3 operator *(float k) const;
	rVector3& operator *=(float k);

	rVector3 operator-() const;

	bool operator==(const rVector3& v) const;
	bool operator!=(const rVector3& v) const;

	static  const rVector3 ZeroVector;
	static  const rVector3 OneVector;

	static const rVector3 UpVector;
	static const rVector3 DownVector;
	static const rVector3 ForwardVector;
	static const rVector3 BackwardVector;
	static const rVector3 RightVector;
	static const rVector3 LeftVector;

	float x;
	float y;
	float z;
};



#endif