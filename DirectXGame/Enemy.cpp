#include "Enemy.h"

using namespace MathUtility;

void Enemy::Initialize(Model* model, Vector3 pos)
{
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void Enemy::Update()
{
	worldTransform_.translation_ += Vector3{0.0f, 0.0f, 0.0f};
}

void Enemy::Draw(Camera* camera)
{
	model_->Draw(worldTransform_, *camera);
}
