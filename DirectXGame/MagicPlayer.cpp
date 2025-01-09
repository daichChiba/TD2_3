#include "MagicPlayer.h"
#include "PlayerNormalBullet.h"
#include "../DirectXGame/Scene/GameScene.h"
void MagicPlayer::PrimaryAttack() {
	std::shared_ptr<EnemyBullet> normal(new PlayerNormalBullet);
	normal->Initialize(bulletModel_, GetWorldPosition());
	normal->SetScale(10.0f);
	gameScene_->AddPlayerBullet(normal);
}

void MagicPlayer::SecondaryAttack() {

}

void MagicPlayer::TertiaryAttack() {

}
