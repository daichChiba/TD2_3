#pragma once

#include "kamataEngine.h"
#include "EnemyActor.h"
using namespace KamataEngine;

class GameScene;
//class EnemyActor;
class EnemyFactory;

class EnemyManager
{
public:
	void Initialize(Model* model, Model* bulletModel,Vector3 pos , GameScene* gameScene);
	virtual void Update();
	void Draw(Camera* camera);
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	void CreateEnemy();

	Vector3 GetEnemyPos();
	float GetRadius();
	void OnCollision( int damage);

	 EnemyActor* GetActor() const { return enemy_.get(); }
private:

	GameScene* gameScene_;

	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	WorldTransform worldTransform_;

	EnemyFactory* enemyFactory_;

	std::unique_ptr<EnemyActor> enemy_;
};