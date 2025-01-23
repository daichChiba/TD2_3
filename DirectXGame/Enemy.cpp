#include "Enemy.h"

#include "../DirectXGame/Scene/GameScene.h"

#include "../DirectXGame/EnemyGravity.h"
#include "../DirectXGame/EnemyManager.h"
#include "../DirectXGame/Player.h"

using namespace MathUtility;

void Enemy::Initialize(Model* model, Vector3 pos, Player* player) {
#ifdef _DEBUG

	assert(model);
#endif // _DEBUG
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	// worldTransform_.scale_ = Vector3{20.0f, 20.0f, 20.0f};

	stage = Stage::Test;

	player_ = player;
}

void Enemy::Update() {
	if (stage == Stage::Test) 
	{
		InitializeGrabity();
		stage = Stage::Grabity;
	}
}

inline void Enemy::SetEnemyStage(const int i) { stage = static_cast<Stage>(i); }

void Enemy::InitializeGrabity() {
	std::unique_ptr<EnemyManager> modeGravity(new EnemyGravity);
	modeGravity->Initialize(model_, model_, worldTransform_.translation_);
	modeGravity->GetPlayer(player_);
	gameScene_->AddEnemy(std::move(modeGravity));
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::OnCollision() {

}
