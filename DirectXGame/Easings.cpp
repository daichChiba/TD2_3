#include "Easings.h"


namespace Easings {
float EaselnQuart(float t) { 
	return t * t * t * t; }

float EaseInTime(float t, float time) {
	return (t / time); }

Vector3 EaseInTime(Vector3 t, int time_) {
	Vector3 result;
	result.x = t.x / time_;
	result.y = t.y / time_;
	result.z = t.z / time_;
	return result;
}


} // namespace Easings