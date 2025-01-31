#pragma once
#include "kamataEngine.h"

using namespace KamataEngine;

class GameScene;
class PlayerWizard;

class EnemyActor {
public:
	void Initialize(Model* model, Model* bulletModel, Vector3 pos, PlayerWizard* player, GameScene* gameScene);
	virtual void Update();
	void Draw(Camera* camera);

	Vector3 GetWorldPos() { return Vector3{worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1], worldTransform_.matWorld_.m[3][2]}; }
	float GetRadius() { return radius_; }
	virtual void OnCollision(int damage) { hp -= damage; }

	void SetPlayerPos(Vector3 pos);

protected:
	GameScene* gameScene_;

	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	WorldTransform worldTransform_;

	PlayerWizard* player_;

	static inline const float flameTime = 1.0f / 60.0f;
	bool isStart_ = false;
	bool isDelete_ = false;

	int hp;

	float radius_ = 0.5f;

	
};
