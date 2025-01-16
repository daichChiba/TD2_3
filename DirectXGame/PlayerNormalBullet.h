#pragma once
#include "EnemyBullet.h"
#include "KamataEngine.h"

using namespace KamataEngine;
using namespace MathUtility;
class PlayerNormalBullet : public EnemyBullet {
public:
	void Update() override;
	void GetTagetPos(Vector3 pos) override { tagetPos = pos; }

private:
	Vector3 startPos;
	Vector3 tagetPos;
	bool start = false;
	static inline const int kMoveTimer = 60;
	int moveTimer;

	static inline const int kDeleteTimer = 60;
	int deleteTimer;

	static inline const float kIncreasingSpeed = 0.000001f; // スピードの上がる速さ
	static inline const float kMaxSpeed = 0.25f; // 最高速度

	private:
	void DrowImgui();
};
