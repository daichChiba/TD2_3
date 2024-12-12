#pragma once
#include "EnemyBullet.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class GrabiltBullet : public EnemyBullet
{
public:
	void Update() override;

	void SetScale(const float scale) {
		worldTransform_.scale_.x = scale;
		worldTransform_.scale_.y = scale;
		worldTransform_.scale_.z = scale;
	}

private:
	void DrowImgui();
	Vector3 velocity_;
	float fallSpeed_ = -0.03f;
};

