#pragma once
#include"KamataEngine.h"
using namespace KamataEngine;
namespace Easings {
float EaselnQuart(float t);

float EaseInTime(float t, float time);

// EaseInTime の引数を変更
Vector3 EaseInTime(const Vector3& startPos, const Vector3& targetPos, float currentTime, float duration);
}