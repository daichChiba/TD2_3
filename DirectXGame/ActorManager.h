#pragma once

#include "EnemyManager.h"
#include "PlayerManger.h"

class ActorManager {
public:
	ActorManager();
	~ActorManager();

	void Initialize(Model* playerModel, Model* PlayerBulletModel, Model* zoldrakModel, Model* enemyModel, Model* EnemyBulletModel, Vector3 playerPos, Vector3 enemyPos, GameScene* gameScene);
	void Update();
	void Draw(Camera* camera);

	std::shared_ptr<EnemyActor> GetEnemy();
	std::shared_ptr<PlayerActor> GetPlayer();

private:
	PlayerManager* playerManager_;
	EnemyManager* enemyManager_;
};
