#include "EnemyManager.h"
//#include "EnemyActor.h"
#include "ActorManager.h"
#include "EnemyFactoy.h"
#include "EnemyGravity.h"

void EnemyManager::Initialize(Model* model, Model* bulletModel, Vector3 pos, GameScene* gameScene, ActorManager* actorMana) {
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif // _DEBUG

	model_ = model;

	bulletModel_ = bulletModel;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	gameScene_ = gameScene;
	actorManager = actorMana;

	enemyFactory_ = new EnemyFactory();
	enemyFactory_->Initialize(model_, bulletModel_);
	enemyFactory_->SetGameScene(gameScene_);

	//CreateEnemy();
}

void EnemyManager::Update() { enemy_->Update(); }

void EnemyManager::Draw(Camera* camera) { model_->Draw(worldTransform_, *camera); }

void EnemyManager::CreateEnemyGrabity() {
	enemy_ = enemyFactory_->AddEnemyGrabity();

	enemy_->Initialize(model_, bulletModel_, Vector3{0.0f, 0.0f, 0.0f}, gameScene_, actorManager);
}

void EnemyManager::CreateEnemyRevolution()
{
	enemy_ = enemyFactory_->AddEnemyRevolution();

	enemy_->Initialize(model_, bulletModel_, Vector3{0.0f, 0.0f, 0.0f}, gameScene_, actorManager);
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
