#pragma once
#include "Player.h"
class MagicPlayer : public PlayerWizard {
public:
	void PrimaryAttack()override;
	void SecondaryAttack()override;
	void SpecialAttack() override;
};
