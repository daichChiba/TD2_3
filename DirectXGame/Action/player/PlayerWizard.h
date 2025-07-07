#pragma once

#include "KamataEngine.h"
#include "PlayerActor.h"

class PlayerWizard : public PlayerActor {
public:
	void Update() override;

private:
	void Attack() override;

	void PrimaryAttack() override;
	void SecondaryAttack() override;
	void SpechalAttack() override;

private:
	float tertiaryAttackCoolTime;
	static inline const float kTertiaryAttackCoolTime = 5;

	//
	float globalCoolTime;
	static inline const float kGlobalCoolTime = 1.0f;

	bool isStart_ = false;

	ObjectColor* color_ = nullptr;

};
