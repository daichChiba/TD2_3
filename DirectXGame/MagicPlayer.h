#pragma once
#include "Player.h"
class MagicPlayer : public Player {
public:
	void PrimaryAttack()override;
	void SecondaryAttack()override;
	void TertiaryAttack() override;
};
