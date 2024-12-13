#pragma once
#include "EnemyBullet.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class GrabiltBullet : public EnemyBullet
{
public:
	void Update() override;

private:
	void DrowImgui();
	Vector3 velocity_;
	float gravity = -0.07f;
};

