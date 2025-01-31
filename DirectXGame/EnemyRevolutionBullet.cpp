#include "EnemyRevolutionBullet.h"

using namespace MathUtility;

void EnemyRevolutionBullet::GetPlayerPos(Vector3 pos)
{
	targetPos = pos;
}

void EnemyRevolutionBullet::Update()
{
	if (!isStart_) {
		direction = targetPos - worldTransform_.translation_;
		direction *= -1.0f;
		speed = 0.0f;
		delay = kdelay;

		color->SetColor( Vector4(1.0f, 1.0f, 1.0f, 0.8f));

		isStart_ = true;
	}
	
	if(delay >= 0.0f)
	{
		delay -= flameTime;
	}else{
		speed = kSpeed;
		color->SetColor( Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	velocity_ = direction * speed;

	worldTransform_.translation_ += velocity_;

	worldTransform_.UpdateMatrix();

}
