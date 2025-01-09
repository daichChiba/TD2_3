#include "math/MathUtility.h"

namespace KamataEngine {

namespace MathUtility {

Vector3 Vector3Lerp(Vector3 a, Vector3 b, float t) { 
	Vector3 c = {}; 
	c.x = Lerp(a.x, b.x, t);
	c.y = Lerp(a.y, b.y, t);
	c.z = Lerp(a.z, b.z, t);

	return c;
}


}
} // namespace KamataEngine