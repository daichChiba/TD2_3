#pragma once

#include "kamataEngine.h"

using namespace KamataEngine;

class GameScene;

enum class Stage{
	Grabity,
	Test
};

class Enemy
{
public:
	void Initialize(Model* model, Vector3 pos);
	void Update();

	void SetGameScene(GameScene* gameScene){ gameScene_ = gameScene; }

	void SetEnemyStage(const int i){  stage = static_cast<Stage>(i); }
	void Draw(Camera* camera);


	Vector3 GetWorldPosition();

	void OnCollision();

	// 半径を取得
	float GetRadius() { return radius_; }

private:
	void InitializeGrabity();

	Model* model_ = nullptr;
	WorldTransform worldTransform_;

	GameScene* gameScene_;

	Stage stage;

	// 半径
	float radius_ = 6.0f;
};

