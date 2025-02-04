#pragma once

#include "KamataEngine.h"

using namespace KamataEngine;

class GameScene;
class PlayerManager;
class EnemyManager;
class PlayerActor;
class EnemyActor;

class ActorManager
{
public:
	void Initialize(Model* playerModel, Model* playerBulleModel, Model* playerBeamModel, Model* enemyModel, Model* enemyBulletModel, Vector3 playerPos, Vector3 enemyPos, GameScene* gameScene);

	void Update();

	void Draw(Camera* camera);

	std::shared_ptr<PlayerActor> GetPlayer();
	std::shared_ptr<EnemyActor> GetEnemy();

private:
	PlayerManager* playerManager;
	EnemyManager* enemyManager;
};

