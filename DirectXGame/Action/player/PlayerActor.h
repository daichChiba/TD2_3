#pragma once

#include <KamataEngine.h>

using namespace KamataEngine;

class GameScene;
class ActorManager;

enum class CX {
	wizard,
	fencer,
	dancer,
};

class PlayerActor {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">モデルの座標</param>
	void Initialize(Model* model, Model* bulletModel, Model* beamModel, const Vector3 position, GameScene* gameScene, ActorManager* actor);

	/// <summary>
	/// アップデート
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(Camera* camera);

	void HPposUpdate();
	void DrawHP();

	int GetPlayerHP(){ return hp;}

	Vector3 GetWorldPosition();

	void AddVelocity(Vector3 velocity);

	void OnCollision();

	float GetRadius() { return radius_; }
	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

	int GetHp() const { return hp; }
	void SpriteDraw();

protected:
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void SpechalAttack();

	void Move();

	virtual void Attack();

	Vector4 color[3]{};


protected:
	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	Model* zoldrakModel_ = nullptr;

	WorldTransform worldTransform_;

	GameScene* gameScene_;
	ActorManager* actorManager;

	int hp;

	static inline const int kMaxHp = 10;

	Vector2 HPPos;

	float HPSpacing = 40.0f;
	Vector2 HPscele;

	Sprite* HPSprite[5];
	Sprite* HPHeafSprite[5];

	uint32_t HpHeafResources;
	uint32_t hpResources;

	CX character;

	XINPUT_STATE xinput_;
	XINPUT_STATE preXinput_;

	Vector3 velocity_ = {0.0f, 0.0f, 0.0f};

	float radius_ = 0.5f;

	

	float flameTime = 1.0f / 60.0f;
	// テクスチャハンドル
	uint32_t SkillTextureHandle_[3] = {0};
	Sprite* skillSprite[3];

};
