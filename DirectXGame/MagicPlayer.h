#pragma once
#include "Player.h"
#include "KamataEngine.h"
using namespace KamataEngine;
class MagicPlayer : public Player {
public:

	//弾
	void PrimaryAttack() override;
	//
	void SecondaryAttack() override;
	//
	void TertiaryAttack() override;

private:
	

};
