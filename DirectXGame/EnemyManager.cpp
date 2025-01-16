#include "EnemyManager.h"

void EnemyManager::Initialize(Model* model, Model* bulletModel, Vector3 pos)
{
	assert(model);
	model_ = model;

	assert(bulletModel);
	bulletModel_ = bulletModel;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void EnemyManager::Update()
{
}

void EnemyManager::Draw(Camera* camera)
{
	model_->Draw(worldTransform_, *camera); }

Vector3 EnemyManager::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

