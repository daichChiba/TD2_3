#include "EnemyGravity.h"

#include "EnemyBullet.h"
#include "GrabiltBullet.h"

void EnemyGravity::Update()
{
	if (!isStart_)
	{
	{
		miniBulletTimer_ = kMiniBulletTime_;
	}

	miniBulletTimer_ -= flameTime;
	
	if (miniBulletTimer_ < 0.0f)
	{
		for(int i = 0; i < kMiniBulletMaxShot; ++i)
		{
			std::shared_ptr<EnemyBullet> grabityBullet_(new GrabiltBullet);
			grabityBullet_->Initialize(bulletModel_, Vector3{ static_cast<float>(kMiniBulletMaxShot * i), 19.3, 0});
		}
	}
}
