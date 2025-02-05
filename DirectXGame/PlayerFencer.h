#pragma once

#include "PlayerActor.h"
class PlayerFencer : public PlayerActor {
	public:
	void Update() override;

private:
	void Attack() override;

	void PrimaryAttack() override;
	void SecondaryAttack() override;
	void SpechalAttack() override;

private:
	float spechialAttackCoolTime;
	static inline const float kSpechialAttackCoolTime
		= 5;

	//
	float globalCoolTime;
	static inline const float kGlobalCoolTime = 1.0f;
};
