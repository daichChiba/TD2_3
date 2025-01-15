#include "MathUtliltyForText.h"

using namespace MathUtility;

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	Matrix4x4 ret = scaleMatrix * rotateXYZMatrix * translateMatrix;

	return ret;
}

// 当たり判定
Vector3 Sphere(Vector3 v1, Vector3 v2) {
	Vector3 result;
	result.x = (v2.x - v1.x) * (v2.x - v1.x);
	result.y = (v2.y - v1.y) * (v2.y - v1.y);
	result.z = (v2.z - v1.z) * (v2.z - v1.z);
	return {result.x + result.y + result.z};
}
