#include "Enemy.h"

using namespace MathUtility;

void Enemy::Initialize(Model* model, Vector3 pos)
{
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	//worldTransform_.scale_ = Vector3{20.0f, 20.0f, 20.0f};

	
}

void Enemy::Update()
{
	//worldTransform_.translation_ += Vector3{0.0f, 0.0f, 0.0f};
	worldTransform_.UpdateMatrix();

	ImGui::Begin("enemy");
	ImGui::Text("%f, %f, %f",worldTransform_.scale_.x, worldTransform_.scale_.y, worldTransform_.scale_.z);
	ImGui::Text("%f, %f, %f",worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z);
	ImGui::Text("%f, %f, %f",worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::End();
}

void Enemy::Draw(Camera* camera)
{
	model_->Draw(worldTransform_, *camera);
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
