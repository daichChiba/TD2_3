#include "PlayerWizard.h"

#include "../DirectXGame/Scene/GameScene.h"

#include "ActorManager.h"
#include "EnemyActor.h"

#include "EnemyBullet.h"
#include "PlayerAccelerationBullet.h"
#include "Straight.h"
#include "Zoldorak.h"

void PlayerWizard::Update() {
	Input::GetInstance()->GetJoystickState(0, xinput_);
	Input::GetInstance()->GetJoystickStatePrevious(0, preXinput_);
	
	Move();

	Attack();

	ImGui::Begin("player");
	ImGui::DragFloat("coolTime", &globalCoolTime, 0.01f);
	ImGui::DragFloat("SPCoolTime", &tertiaryAttackCoolTime, 0.01f);
	ImGui::End();

	worldTransform_.UpdateMatrix();
}

void PlayerWizard::Attack() {
	globalCoolTime -= flameTime;
	tertiaryAttackCoolTime -= flameTime;

	if (globalCoolTime < 0.0f) {
		if (Input::GetInstance()->ReleseKey(DIK_U) || xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
			PrimaryAttack();
		}
		if (Input::GetInstance()->ReleseKey(DIK_I) || xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			SecondaryAttack();
		}

		if (tertiaryAttackCoolTime < 0.0f) {
			if (Input::GetInstance()->ReleseKey(DIK_O) || xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
				SpechalAttack();
			}
		}
	}
}

void PlayerWizard::PrimaryAttack() {
	std::shared_ptr<EnemyBullet> acceleration(new PlayerAccelerationBullet);
	acceleration->Initialize(bulletModel_, GetWorldPosition());
	acceleration->SetTagetPos(actorManager->GetEnemy()->GetWorldPos());
	//acceleration->SetStartPos(worldTransform_.translation_);
	gameScene_->AddPlayerBullet(acceleration);

	globalCoolTime = kGlobalCoolTime;
}

void PlayerWizard::SecondaryAttack() {
	std::shared_ptr<EnemyBullet> straight(new Straight);
	straight->Initialize(bulletModel_, GetWorldPosition());
	Vector3 direction = actorManager->GetEnemy()->GetWorldPos() - GetWorldPosition();
	direction = Normalize(direction);
	straight->SetTagetPos(direction);
	// straight->SetStartPos(worldTransform_.translation_);
	gameScene_->AddPlayerBullet(straight);

	globalCoolTime = kGlobalCoolTime;
}

void PlayerWizard::SpechalAttack() {
	Vector3 direction = actorManager->GetEnemy()->GetWorldPos() - GetWorldPosition();
	direction = Normalize(direction);
	for (int i = 0; i < 60; i++) {
		std::shared_ptr<EnemyBullet> zoldrak(new Zoldorak);
		zoldrak->Initialize(zoldrakModel_, direction * (radius_ * i + radius_ /*/ 2*/));
		zoldrak->SetTagetPos(direction);
		zoldrak->SetBullet(Bullet::Zoldorak);
		zoldrak->SetActor(actorManager);
		gameScene_->AddPlayerBullet(zoldrak);
	}
	tertiaryAttackCoolTime = kTertiaryAttackCoolTime;
	globalCoolTime = kGlobalCoolTime;
}
