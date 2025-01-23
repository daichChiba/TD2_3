#include "EnemyManager.h"
#include "EnemyActor.h"
#include "EnemyFactoy.h"
#include "EnemyGravity.h"

void EnemyManager::Initialize(Model* model, Model* bulletModel, Vector3 pos, Player* player, GameScene* gameScene) {
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif // _DEBUG

	model_ = model;

	bulletModel_ = bulletModel;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	player_ = player;
	gameScene_ = gameScene;

	enemyFactory_ = new EnemyFactory();
	enemyFactory_->Initialize(model_, bulletModel_);
	enemyFactory_->SetPlayer(player_);
	enemyFactory_->SetGameScene(gameScene_);

	CreateEnemy();
}

void EnemyManager::Update() { enemy_->Update(); }

void EnemyManager::Draw(Camera* camera) { model_->Draw(worldTransform_, *camera); }

void EnemyManager::CreateEnemy() {
	enemy_ = enemyFactory_->AddEnemy();

	enemy_->Initialize(model_, bulletModel_, Vector3{0.0f, 0.0f, 0.0f}, player_, gameScene_);
}

Vector3 EnemyManager::GetEnemyPos() {
	Vector3 result = enemy_->GetWorldPos();
	return result;
}

float EnemyManager::GetRadius()
{
	return enemy_->GetRadius();
}

void EnemyManager::OnCollision(int damage)
{
	enemy_->OnCollision(damage);
}

// Vector3 EnemyManager::GetWorldPosition() {
//	Vector3 worldPos;
//
//	worldPos.x = worldTransform_.matWorld_.m[3][0];
//	worldPos.y = worldTransform_.matWorld_.m[3][1];
//	worldPos.z = worldTransform_.matWorld_.m[3][2];
//
//	return worldPos;
// }
