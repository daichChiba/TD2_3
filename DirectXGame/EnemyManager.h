#pragma once

#include "kamataEngine.h"

using namespace KamataEngine;

class GameScene;
class Player;
class EnemyFactory;
class EnemyActor;

class EnemyManager
{
public:
	void Initialize(Model* model, Model* bulletModel,Vector3 pos ,Player* player, GameScene* gameScene);
	virtual void Update();
	void Draw(Camera* camera);
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	void CreateEnemy();

	//Vector3 GetEnemyPos(){ return enemy_->GetWorldPos(); }

	virtual void GetPlayer(Player* player){  player_ = player; }
	
private:

	GameScene* gameScene_;

	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	WorldTransform worldTransform_;

	Player* player_;

	EnemyFactory* enemyFactory_;

	std::unique_ptr<EnemyActor> enemy_;
};