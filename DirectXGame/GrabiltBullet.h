#pragma once
#include "EnemyBullet.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class GrabiltBullet : public EnemyBullet
{
public:
	void Update() override;

private:
	Vector3 velocity_;
	float fallSpeed_ = 0.03f;
};

