#pragma once
#include "EnemyBullet.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class GrabityBulletSecond : public EnemyBullet
{
public:
	void SetPlayerPos(Vector3 pos) override;
	void Update() override;

private:
	void DrowImgui();

	Vector3 targetPos;
	Vector3 direction;

	float speed;

	static inline const float kSpeed = 0.01f;
 };

