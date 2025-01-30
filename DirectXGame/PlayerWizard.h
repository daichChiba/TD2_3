#pragma once
#include <KamataEngine.h>
#include <functional>
#include <map>
#include "PlayerActor.h"

using namespace KamataEngine;

class GameScene;

class PlayerWizard : public PlayerActor {
public:
	void Update() override;

	void PrimaryAttack() override;
	void SecondaryAttack()override;
	void SpecialAttack()override;

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	// 半径を取得
	float GetRadius() { return radius_; }

private:
	Character character_;

	int primaryAttackCoolTime;
	static inline const int kPrimaryAttackCoolTime = 30;
	int secondaryAttackCoolTime;
	static inline const int kSecondaryAttackCoolTime = 45;
	int tertiaryAttackCoolTime;
	static inline const int kTertiaryAttackCoolTime = 60;

	//
	int globalCoolTime;
	static inline const int kGlobalCoolTime=20;

	const float kZoldorakRadius_ = 3.0f;

private://メンバ関数
	/// <summary>
	/// playerの動き
	/// </summary>
	void Move();

	void Attack();

};
