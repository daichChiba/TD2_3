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
	model_->Draw(worldTransform_, *camera); }

Vector3 EnemyBullet::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void EnemyBullet::OnCollision() {
	isDelete_ = true;
}
