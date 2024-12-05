#include "Enemy.h"

void Enemy::Initialize(Model* model, Vector3 pos)
{
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void Enemy::Update()
{
}

void Enemy::Draw(Camera* camera)
{
	model_->Draw(worldTransform_, *camera);
}
