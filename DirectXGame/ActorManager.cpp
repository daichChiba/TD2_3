#include "ActorManager.h"

#include "../DirectXGame/Scene/GameScene.h"
#include "PlayerManager.h"
#include "EnemyManager.h"

void ActorManager::Initialize(Model* playerModel, Model* playerBulleModel, Model* playerBeamModel, Model* enemyModel, Model* enemyBulletModel, Vector3 playerPos, Vector3 enemyPos, GameScene* gameScene)
{
	playerManager = new PlayerManager;
	playerManager->Initialize(playerModel, playerBulleModel, playerBeamModel, playerPos, gameScene);

	playerManager->CreateWizard();

	enemyManager = new EnemyManager;
	enemyManager->Initialize(enemyModel, enemyBulletModel, enemyPos, gameScene);
	enemyManager->CreateEnemy();
}

void ActorManager::Update()
{
	playerManager->Update();
	enemyManager->Update();
}

void ActorManager::Draw(Camera* camera)
{
	playerManager->Draw(camera);
	enemyManager->Draw(camera);
}

PlayerActor ActorManager::GetPlayer()
{
	playerManager->GetActor();
}
EnemyActor ActorManager::GetEnemy()
{
	enemyManager->GetActor();
}
