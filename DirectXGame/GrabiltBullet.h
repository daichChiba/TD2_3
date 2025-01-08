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

	
	float startSpeed = -0.0001f;
	float gravity = -0.007f;
};

