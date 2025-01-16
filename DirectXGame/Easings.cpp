#include "Easings.h"


namespace Easings {
float EaselnQuart(float t) { 
	return t * t * t * t; }

float EaseInTime(float t, float time) {
	return (t / time); }

Vector3 EaseInTime(Vector3 t, Vector3 time_) {
	Vector3 result;
	result.x = t.x / time_.x;
	result.y = t.y / time_.y;
	result.z = t.z / time_.z;
	return result;
}


} // namespace Easings