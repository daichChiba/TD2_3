#include "PlayerFencer.h"

#include "Scene/GameScene.h"

#include "EnemyBullet.h"
#include "PlayerAccelerationBullet.h"
#include "ActorManager.h"
#include "EnemyActor.h"

void PlayerFencer::Update()
{
	Input::GetInstance()->GetJoystickState(0, xinput_);
	Input::GetInstance()->GetJoystickStatePrevious(0, preXinput_);
	
	Move();

	Attack();

	ImGui::Begin("player");
	ImGui::DragFloat("coolTime", &globalCoolTime, 0.01f);
	ImGui::DragFloat("SPCoolTime", &spechialAttackCoolTime, 0.01f);
	ImGui::End();

	worldTransform_.UpdateMatrix();
}

void PlayerFencer::Attack()
{
	globalCoolTime -= flameTime;
	spechialAttackCoolTime -= flameTime;

	if (globalCoolTime < 0.0f) {
		if (Input::GetInstance()->ReleseKey(DIK_U)) {
			PrimaryAttack();
		}
		if (Input::GetInstance()->ReleseKey(DIK_I)) {
			SecondaryAttack();
		}

		if (spechialAttackCoolTime < 0.0f) {
			if (Input::GetInstance()->ReleseKey(DIK_O)) {
				SpechalAttack();
			}
		}
	}
}

void PlayerFencer::PrimaryAttack() {
	std::shared_ptr<EnemyBullet> acceleration(new PlayerAccelerationBullet);
	acceleration->Initialize(bulletModel_, GetWorldPosition());
	acceleration->SetTagetPos(actorManager->GetEnemy()->GetWorldPos());
	//acceleration->SetStartPos(worldTransform_.translation_);
	gameScene_->AddPlayerBullet(acceleration);

	globalCoolTime = kGlobalCoolTime;
}
