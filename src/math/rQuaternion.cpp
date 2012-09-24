#include "rQuaternion.hpp"

rQuaternion::rQuaternion(const rVector3& eulerAngles){
	SetFromEulerAngles(eulerAngles.x , eulerAngles.y, eulerAngles.z);
}

rQuaternion::rQuaternion(float tx , float ty, float tz){
	SetFromEulerAngles(tx,ty,tz);
}

void rQuaternion::SetFromEulerAngles(const rVector3& angles){
	SetFromEulerAngles(angles.x , angles.y , angles.z);
}

void rQuaternion::SetFromEulerAngles(float tx , float ty, float tz){

	//convert to radian
	tz = rMath::DegreeToRad(tz)* 0.5f;
	ty = rMath::DegreeToRad(ty)* 0.5f;
	tx = rMath::DegreeToRad(tx)* 0.5f;

	//get half angles
	float cos_z_2 = std::cos(tz);
	float cos_y_2 = std::cos(ty);
	float cos_x_2 = std::cos(tx);

	float sin_z_2 = std::sin(tz);
	float sin_y_2 = std::sin(ty);
	float sin_x_2 = std::sin(tx);

	//assign quaternion members
	w = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
	x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
	y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
	z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
}

void rQuaternion::TransformVector3(rVector3& v) const{
    rVector3 quatVec(x, y , z);
	rVector3 uv = quatVec.Cross(v);
	rVector3 uuv = quatVec.Cross(uv);

	uv *= (2.0f * w);
	uuv *= 2.0f;

	v= v + uv + uuv;
}

rVector3 rQuaternion::GetTransformedVector3(const rVector3& v) const{
	rVector3 returnVec = v;
	TransformVector3(returnVec);
	return returnVec;
}