#include "PlayerWizard.h"

#include "../DirectXGame/Scene/GameScene.h"

#include "../ActorManager.h"
#include "../enemy/EnemyActor.h"

#include "../bullet/EnemyBullet.h"
#include "../bullet/PlayerAccelerationBullet.h"
#include "../bullet/Straight.h"
#include "../bullet/Zoldorak.h"

void PlayerWizard::Update() {
	Input::GetInstance()->GetJoystickState(0, xinput_);
	Input::GetInstance()->GetJoystickStatePrevious(0, preXinput_);

	Move();

	Attack();



#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::DragFloat("coolTime", &globalCoolTime, 0.01f);
	ImGui::DragFloat("SPCoolTime", &tertiaryAttackCoolTime, 0.01f);
	ImGui::DragInt("hp", &hp);
	ImGui::End();

#endif // _DEBUG

	worldTransform_.UpdateMatrix();
}

void PlayerWizard::Attack() {
	globalCoolTime -= flameTime;
	tertiaryAttackCoolTime -= flameTime;

	if (globalCoolTime < 0.0f) {
		color[0] = {1.0f, 1.0f, 1.0f, 1.0f};
		color[1] = {1.0f, 1.0f, 1.0f, 1.0f};
		if (Input::GetInstance()->ReleseKey(DIK_U) || xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
			PrimaryAttack();
		}
		if (Input::GetInstance()->ReleseKey(DIK_I) || xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			SecondaryAttack();

		}

		if (tertiaryAttackCoolTime < 0.0f) {
			color[2] = {1.0f, 1.0f, 1.0f, 1.0f};
			if (Input::GetInstance()->ReleseKey(DIK_O) || xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
				SpechalAttack();
			}
		} else {
			color[2] = {1.0f, 1.0f, 1.0f, 0.5f};
		}
	} else {
		color[0] = {1.0f, 1.0f, 1.0f, 0.5f};
		color[1] = {1.0f, 1.0f, 1.0f, 0.5f};
		color[2] = {1.0f, 1.0f, 1.0f, 0.5f};
	}
}

void PlayerWizard::PrimaryAttack() {
	std::shared_ptr<EnemyBullet> acceleration(new PlayerAccelerationBullet);
	acceleration->Initialize(bulletModel_, GetWorldPosition());
	acceleration->SetTagetPos(actorManager->GetEnemy()->GetWorldPos());
	// acceleration->SetStartPos(worldTransform_.translation_);
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
		if (i != 0) {
			zoldrak->SetDraw(false);
		}
		gameScene_->AddPlayerBullet(zoldrak);
	}
	tertiaryAttackCoolTime = kTertiaryAttackCoolTime;
	globalCoolTime = kGlobalCoolTime;
}
