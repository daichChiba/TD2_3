#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class GameScene;
class PlayerWizard;

static enum class Character {
	wizard,
	fencer,
	dancer,
};

class PlayerActor {
public:
	virtual void Initialize(Model* model, Model* bulletModel, Model* zoldrakModel, const Vector3 position, Character character, GameScene* gameScene);

	virtual void Update();

	virtual void Draw(Camera* camera);

	Vector3 GetWorldPos() { return Vector3{worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1], worldTransform_.matWorld_.m[3][2]}; }
	float GetRadius() { return radius_; }
	virtual void OnCollision(int damage) { hp -= damage; };
	Vector3 GetEnemyPos(Vector3 pos) {return enemyPos = pos; }

protected:
	virtual void Move();

	virtual void Attack();

	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void SpecialAttack();

	void AddVelocity(Vector3 velocity);

protected:
	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	Model* zoldrakModel_ = nullptr;
	WorldTransform worldTransform_;

	GameScene* gameScene_;
	PlayerWizard* player_;

	bool isDelete_ = false;

	int hp;

	float radius_ = 0.5f;

	Character character_;

	XINPUT_STATE xinput_;
	XINPUT_STATE preXinput_;

	Vector3 velocity_ = {0.0f, 0.0f, 0.0f};

	Vector3 enemyPos;
};
