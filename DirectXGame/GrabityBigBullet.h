#pragma once
#include "../DirectXGame/EnemyBullet.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class GrabityBigBullet : public EnemyBullet
{
	public:
	void Update() override;

private:
	void PlayerSuction();

	void DrowImgui();

	float gravity = -0.1f;
	static inline const float Suction = 20.0f;
	static inline const float PlayerSuctionSpeed = 0.001f;
	Vector3 playerPos;
};

