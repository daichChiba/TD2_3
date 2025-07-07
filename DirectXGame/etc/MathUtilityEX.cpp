#include "math/MathUtility.h"
#include <corecrt_math.h>

namespace KamataEngine {

namespace MathUtility {

Vector3 Vector3Lerp(Vector3 a, Vector3 b, float t) { 
	Vector3 c = {}; 
	c.x = Lerp(a.x, b.x, t);
	c.y = Lerp(a.y, b.y, t);
	c.z = Lerp(a.z, b.z, t);

	return c;
}
float FloatLength(float a) {
	float result;
	result = float(sqrt(a * a));
	return result;
}

float FloatNormalize(float a) {
	return a / FloatLength(a);
}

Vector3 Sphere(Vector3 v1, Vector3 v2) {
	Vector3 result;
	result.x = (v2.x - v1.x) * (v2.x - v1.x);
	result.y = (v2.y - v1.y) * (v2.y - v1.y);
	result.z = (v2.z - v1.z) * (v2.z - v1.z);
	return {result.x + result.y + result.z};
}


}
} // namespace KamataEngine