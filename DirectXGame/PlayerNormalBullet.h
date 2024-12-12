#pragma once
#include "PlayerBullet.h"
class PlayerNormalBullet : public PlayerBullet {
public:
	void Update() override;

private:
	Vector3 velocity_;
	float bulletSpeed_ = 0.05f;
	WorldTransform worldTransform_;
};
