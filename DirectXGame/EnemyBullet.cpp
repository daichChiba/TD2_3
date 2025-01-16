#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, Vector3 pos)
{
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void EnemyBullet::Update()
{
	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(Camera* camera)
{
	model_->Draw(worldTransform_, *camera);
}

void EnemyBullet::SetScale(const float scale)
{ 
	worldTransform_.scale_.x = {scale}; 
	worldTransform_.scale_.y = {scale}; 
	worldTransform_.scale_.z = {scale}; 
}

void EnemyBullet::GetPlayerPos(Vector3 pos)
{
	pos = pos;
}
