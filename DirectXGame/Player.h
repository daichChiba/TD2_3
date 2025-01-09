#pragma once
#include <KamataEngine.h>
#include <functional>
#include <map>


using namespace KamataEngine;

class GameScene;

enum class Character {
	wizard,
	fencer,
	dancer,
};
class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">モデルの座標</param>
	void Initialize(Model* model, const Vector3 position,Character character,Model* bulletModel);

	/// <summary>
	/// アップデート
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(Camera* camera);

	Vector3 GetWorldPosition();

	void OnCollision();

	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void TertiaryAttack();
	Model* bulletModel_ = nullptr;

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	// 半径を取得
	float GetRadius() { return radius_; }

	Vector3 GetPlayerPos();
private:
	Character character_;

	Model* model_ = nullptr;

	//Camera* camera_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	XINPUT_STATE xinput_;
	XINPUT_STATE preXinput_;

	Vector3 velocity = {0.0f, 0.0f, 0.0f};

	int primaryAttackCoolTime;
	static inline const int kPrimaryAttackCoolTime = 30;
	//int secondaryAttackCoolTime;
	//static inline const int kSecondaryAttackCoolTime = 30;
	//int tertiaryAttackCoolTime;
	//static inline const int kTertiaryAttackCoolTime = 45;

	GameScene* gameScene_;

	// 半径
	float radius_ = 6.0f;

private: // メンバ関数
	/// <summary>
	/// playerの動き
	/// </summary>
	void Move();

	void Attack();

};
