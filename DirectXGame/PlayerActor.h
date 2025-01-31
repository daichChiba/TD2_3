#pragma once

#include <KamataEngine.h>

using namespace KamataEngine;

class GameScene;

enum class CX {
	wizard,
	fencer,
	dancer,
};

class PlayerActor
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">モデルの座標</param>
	void Initialize(Model* model, Model* bulletModel,Model* beamModel,const Vector3 position, GameScene* gameScene);

	/// <summary>
	/// アップデート
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(Camera* camera);

	Vector3 GetWorldPosition();

	void AddVelocity(Vector3 velocity);

	void OnCollision();

	float GetRadius() { return radius_; }
protected:
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void SpechalAttack();

	void Move();

	virtual void Attack();
protected:
	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	Model* zoldrakModel_ = nullptr;

	WorldTransform worldTransform_;

	GameScene* gameScene_;

	CX character;

	XINPUT_STATE xinput_;
	XINPUT_STATE preXinput_;

	Vector3 velocity_ = {0.0f, 0.0f, 0.0f};

	float radius_ = 0.5f;

	int hp;

	float flameTime = 1.0f / 60.0f;
};

