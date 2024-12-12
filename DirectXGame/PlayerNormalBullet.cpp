#include "PlayerNormalBullet.h"
using namespace MathUtility;
void PlayerNormalBullet::Update() {
	velocity_.x = bulletSpeed_;
	worldTransform_.translation_ += velocity_;
}
