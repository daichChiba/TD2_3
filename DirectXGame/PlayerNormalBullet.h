#pragma once
#include "EnemyBullet.h"
#include "KamataEngine.h"

using namespace KamataEngine;
using namespace MathUtility;
class PlayerNormalBullet : public EnemyBullet {
public:
	void Update() override;

private:
	Vector3 startPos;
	Vector3 tagetPos;
	bool start = false;
	static inline const int kMoveTimer = 60;
	int moveTimer;

	static inline const int kDeleteTimer = 300;
	int deleteTimer;

	static inline const float kIncreasingSpeed = 0.000001f; // スピードの上がる速さ
	static inline const float kMaxSpeed = 0.25f;             // 最高速度
};
