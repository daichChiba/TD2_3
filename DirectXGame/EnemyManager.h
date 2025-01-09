#pragma once

#include "kamataEngine.h"

using namespace KamataEngine;

class GameScene;
class Player;

class EnemyManager
{
public:
	void Initialize(Model* model, Model* bulletModel, Vector3 pos);
	virtual void Update();
	void Draw(Camera* camera);
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	virtual void GetPlayer(Player* player){  player_ = player; }
	Vector3 GetWorldPosition();

protected:

	GameScene* gameScene_;

	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	WorldTransform worldTransform_;

	Player* player_;

	static inline const float flameTime = 1.0f/ 60.0f;
	bool isStart_ = false;
};