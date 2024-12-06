#include "GrabiltBullet.h"

using namespace MathUtility;

void GrabiltBullet::Update()
{
	velocity_ .y = fallSpeed_;

	worldTransform_.translation_ += velocity_;

	worldTransform_.UpdateMatrix();

	if (worldTransform_.translation_.y < -19.3f)
	{
		isDelete_ = true;
	}
}
