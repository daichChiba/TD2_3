#pragma once
#include "../DirectXGame/EnemyBullet.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class GrabityBulletSecond : public EnemyBullet
{
public:
	void GetPlayerPos(Vector3 pos) override;
	void Update() override;

private:
	void DrowImgui();

	Vector3 targetPos;

	float speed = 0.04f;
 };

