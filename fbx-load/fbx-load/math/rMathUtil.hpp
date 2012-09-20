#ifndef R_MATH_UTILS_HPP
#define R_MATH_UTILS_HPP

#ifndef M_PI
	#define M_PI 3.141592653589793238462643f
#endif

#define rMATH_ZERO_TOLERANCE 1e-06f

namespace rMath{
	
	float DegreeToRad(float deg);
};

#endif