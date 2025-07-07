#pragma once
#include "EnemyBullet.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class EnemyRevolutionBullet : public EnemyBullet {
public:
	void SetPlayerPos(Vector3 pos) override;
	void Update() override;


private:
	Vector3 targetPos;
	Vector3 direction;

	float delay;

	float speed;

	static inline const float kSpeed = 0.01f;
	static inline const float kdelay = 1.0f;
};
