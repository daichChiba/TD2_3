#pragma once
#include"KamataEngine.h"
using namespace KamataEngine;
namespace Easings {
float EaselnQuart(float t);

float EaseInTime(float t, float time);

// EaseInTime の引数を変更
Vector3 EaseInTime(const Vector3& startPos, const Vector3& targetPos, float currentTime, float duration);

//    // 追加：EaseInQuad関数
//float EaseInQuad(float t);

// 追加：加速度イージング用
Vector3 EaseInAcceleration(const Vector3& startVelocity, const Vector3& maxVelocity, float currentTime, float duration);
}