#include "ActorManager.h"

ActorManager::ActorManager() : playerManager_(nullptr), enemyManager_(nullptr) {}

ActorManager::~ActorManager() {
	delete playerManager_;
	delete enemyManager_;
}

void ActorManager::Initialize(Model* playerModel, Model* PlayerBulletModel, Model* zoldrakModel, Model* enemyModel, Model* enemyBulletModel, Vector3 playerPos, Vector3 enemyPos, GameScene* gameScene)
{
	 playerManager_ = new PlayerManager();
    playerManager_->Initialize(playerModel, playerModel, enemyModel, playerPos, gameScene);
    playerManager_->CreatePlayerWizard();
    playerManager_->GetPlayerActor()->Initialize(playerModel, PlayerBulletModel, zoldrakModel, playerPos, Character::wizard, gameScene);

    enemyManager_ = new EnemyManager();
    enemyManager_->Initialize(enemyModel, enemyBulletModel, enemyPos, gameScene);
	//	enemyManager_->CreateEnemy();
   
	
}

void ActorManager::Update() {
	playerManager_->Update();
	enemyManager_->Update();
}

void ActorManager::Draw(Camera* camera) {
	playerManager_->Draw(camera);
	enemyManager_->Draw(camera);
}

std::shared_ptr<EnemyActor> ActorManager::GetEnemy()
{
	enemyManager_->GetEnemyActor();
}

std::shared_ptr<PlayerActor> ActorManager::GetPlayer()
{
	playerManager_->GetPlayerActor();
}
