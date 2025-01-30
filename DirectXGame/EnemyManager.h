#pragma once

#include "kamataEngine.h"

using namespace KamataEngine;

class GameScene;
class PlayerWizard;
class EnemyFactory;
class EnemyActor;

class EnemyManager
{
public:
	void Initialize(Model* model, Model* bulletModel,Vector3 pos ,std::unique_ptr<EnemyActor> player, GameScene* gameScene);
	virtual void Update();
	void Draw(Camera* camera);
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	void CreateEnemy();

	Vector3 GetEnemyPos();
	float GetRadius();
	void OnCollision( int damage);

	virtual void GetPlayer(std::unique_ptr<PlayerActor> player){  player_->= player; }
	
private:

	GameScene* gameScene_;

	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	WorldTransform worldTransform_;

	std::unique_ptr<PlayerActor> player_;

	EnemyFactory* enemyFactory_;

	std::unique_ptr<EnemyActor> enemy_;
};