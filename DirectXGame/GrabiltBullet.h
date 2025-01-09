#pragma once
#include "../DirectXGame/EnemyBullet.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class GrabiltBullet : public EnemyBullet
{
public:
	void Update() override;

private:
	void DrowImgui();

	float gravity = -0.2f;
	float BigBulletGrabity = -0.1f;
 };

