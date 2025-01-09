#pragma once

#include "kamataEngine.h"

using namespace KamataEngine;

class GameScene;
class Player;

enum class Stage{
	Grabity,
	Test
};

class Enemy
{
public:
	void Initialize(Model* model, Vector3 pos, Player* player);
	void Update();

	void SetGameScene(GameScene* gameScene){ gameScene_ = gameScene; }

	void SetEnemyStage(const int i){  stage = static_cast<Stage>(i); }
	void Draw(Camera* camera);


	Vector3 GetWorldPosition();

private:
	void InitializeGrabity();

	Model* model_ = nullptr;
	WorldTransform worldTransform_;

	GameScene* gameScene_;

	Stage stage;

	Player* player_;
};

