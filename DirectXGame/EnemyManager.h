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
	Vector3 GetWorldPos(){ return Vector3{ worldTransform_.matWorld_.m[3][0],worldTransform_.matWorld_.m[3][1],worldTransform_.matWorld_.m[3][2]};}
protected:

	GameScene* gameScene_;

	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	WorldTransform worldTransform_;

	Player* player_;

	static inline const float flameTime = 1.0f/ 60.0f;
	bool isStart_ = false;
	bool isDelete_ = false;
};