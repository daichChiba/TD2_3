#pragma once

#include "kamataEngine.h"
#include "EnemyActor.h"
using namespace KamataEngine;

class GameScene;
//class EnemyActor;
class EnemyFactory;
class ActorManager;

class EnemyManager
{
public:
	void Initialize(Model* model, Model* bulletModel,Vector3 pos , GameScene* gameScene, ActorManager* actorMana);
	virtual void Update();
	void Draw(Camera* camera);
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	void CreateEnemyGrabity();
	void CreateEnemyRevolution();

	 EnemyActor* GetActor() const { return enemy_.get(); }
private:

	GameScene* gameScene_;
	ActorManager* actorManager;

	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	WorldTransform worldTransform_;

	EnemyFactory* enemyFactory_;

	std::unique_ptr<EnemyActor> enemy_;
};