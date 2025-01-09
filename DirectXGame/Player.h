#pragma once
#include <KamataEngine.h>
#include <functional>
#include <map>
#include"../DirectXGame/MagicPlayer.h"

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

	

protected:
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void TertiaryAttack();
	Model* bulletModel_ = nullptr;
	GameScene* gameScene_ ;

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

	MagicPlayer* magicPlayer_;

private: // メンバ関数
	/// <summary>
	/// playerの動き
	/// </summary>
	void Move();

	void Attack();

	std::map<Character, std::function<void()>> PrimaryMode{
	    {Character::wizard, [this]() { magicPlayer_->PrimaryAttack(); }},
	};
};
