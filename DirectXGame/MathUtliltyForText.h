#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

//アフィン変換
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
//当たり判定
Vector3 Sphere(Vector3 v1, Vector3 v2);