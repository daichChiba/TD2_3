#pragma once
#include "EnemyManager.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class EnemyGravity : public EnemyManager
{
public:
	void Update() override;

private:
	float miniBulletTimer_ = 0.0f;
	static inline const float kMiniBulletTime_ = 1.5f;
	static inline const int kMiniBulletMaxShot = 5;

	
};

