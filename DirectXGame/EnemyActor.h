#pragma once
#include "kamataEngine.h"

#include <map>
#include <functional>

using namespace KamataEngine;

class GameScene;
class Player;

class EnemyActor {
public:
	void Initialize(Model* model, Model* bulletModel, Vector3 pos, GameScene* gameScene);
	virtual void Update();
	void Draw(Camera* camera);

	Vector3 GetWorldPos() { return Vector3{worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1], worldTransform_.matWorld_.m[3][2]}; }
	float GetRadius() { return radius_; }
	virtual void OnCollision(int damage) { hp -= damage; }



protected:
	GameScene* gameScene_;

	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	WorldTransform worldTransform_;

	static inline const float flameTime = 1.0f / 60.0f;
	bool isStart_ = false;
	bool isDelete_ = false;

	int hp;

	enum class EnemyMode {
		First,
		Second,
	};

	EnemyMode enemyMode;

	virtual void modeFirst();
	virtual void modeSecond();

	std::map<EnemyMode, std::function<void()>> modeUpdate{
	    {EnemyMode::First, [this]() { modeFirst(); }},
	    {EnemyMode::Second, [this]() { modeSecond(); }},
	};

	float radius_ = 0.5f;
};
