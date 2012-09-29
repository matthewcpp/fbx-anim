#ifndef R_KEYFRAME_HPP
#define R_KEYFRAME_HPP

#include "rVector3.hpp"

struct rKeyframe{
	float time;

	rVector3 translate;
	rVector3 rotate;
	rvector3 scale;
};

#endif