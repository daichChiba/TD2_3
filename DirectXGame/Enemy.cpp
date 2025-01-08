#include "Enemy.h"

#include "../DirectXGame/Scene/GameScene.h"

#include "../DirectXGame/EnemyGravity.h"
#include "../DirectXGame/EnemyManager.h"

using namespace MathUtility;

void Enemy::Initialize(Model* model, Vector3 pos) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	// worldTransform_.scale_ = Vector3{20.0f, 20.0f, 20.0f};

	stage = Stage::Test;
}

void Enemy::Update() {
	if (stage == Stage::Test) 
	{
		InitializeGrabity();
		stage = Stage::Grabity;
	}
}

void Enemy::InitializeGrabity() {
	std::shared_ptr<EnemyManager> modeGravity(new EnemyGravity);
	modeGravity->Initialize(model_, model_, worldTransform_.translation_);
	gameScene_->AddEnemy(modeGravity);
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
