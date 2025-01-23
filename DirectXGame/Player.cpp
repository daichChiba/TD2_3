#include "Player.h"
//#include "magic"
#include<cassert>
#include "EnemyManager.h"
#include"Straight.h"
#include"../DirectXGame/Scene/GameScene.h"
#include"PlayerAccelerationBullet.h"
#include"Zoldorak.h"
using namespace MathUtility;
void Player::Initialize(Model* model, const Vector3 position, Character character, Model* bulletModel, Model* zoldrakModel) {
	assert(model);
	model_ = model;
	bulletModel_ = bulletModel;
	zoldrakModel_ = zoldrakModel;
	character_ = character;

	//camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	//worldTransform_.rotation_ = {0.0f, 0.5f, 0.0f};

	primaryAttackCoolTime = 0;
	//secondaryAttackCoolTime = 0;
	//tertiaryAttackCoolTime = 0;
}

void Player::Update() {
	Input::GetInstance()->GetJoystickState(0, xinput_);
	Input::GetInstance()->GetJoystickStatePrevious(0, preXinput_);
#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::SliderFloat3("pos", &worldTransform_.translation_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("vel", &velocity_.x, -10.0f, 10.0f);
	ImGui::Text("primaryAttackCoolTime=%d", primaryAttackCoolTime);
	ImGui::End();

#endif // DEBUG


	Move();

	Attack();

	worldTransform_.UpdateMatrix();
}

void Player::Draw(Camera* camera) {
	model_->Draw(worldTransform_, *camera);
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::AddVelocity(Vector3 velocity){
	worldTransform_.translation_ += velocity; 
}

void Player::OnCollision() {

}

void Player::PrimaryAttack() {

}

void Player::SecondaryAttack() {

}

void Player::TertiaryAttack() {

}


void Player::Move() {
	velocity_ = {0.0f};
	

#pragma region 移動タイプWASD
	if (Input::GetInstance()->PushKey(DIK_D)) {
		velocity_.x = 0.1f;
	} else if (Input::GetInstance()->PushKey(DIK_A)) {
		velocity_.x = -0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_W)) {
		velocity_.y = 0.1f;
	} else if (Input::GetInstance()->PushKey(DIK_S)) {
		velocity_.y = -0.1f;
	}
	#pragma endregion 

	#pragma region 移動タイプ上下左右
	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		velocity_.x = 0.1f;
	} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		velocity_.x = -0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_UP)) {
		velocity_.y = 0.1f;
	} else if (Input::GetInstance()->PushKey(DIK_DOWN)) {
		velocity_.y = -0.1f;
	}
	#pragma endregion 

#pragma region 移動タイプコントローラー

	// 左スティックのX, Y値を取得
	float lx = xinput_.Gamepad.sThumbLX / 32767.0f; // 正規化（-1.0 ～ 1.0）
	float ly = xinput_.Gamepad.sThumbLY / 32767.0f;

	if(lx !=  0.0f || ly !=  0.0f){
		// デッドゾーンの設定(スティックがニュートラルに近い場合に意図せず移動しないようにする)
		const float deadZone = 0.1f;
		if (fabs(lx) < deadZone)
			lx = 0.0f;
		if (fabs(ly) < deadZone)
			ly = 0.0f;

		// スティックの強度と角度を計算
		float magnitude = sqrtf(lx * lx + ly * ly); // 入力強度（0 ～ 1）
		float angle = atan2f(ly, lx);// スティックの角度（ラジアン）

		// 最大速度
		const float maxSpeed = 0.3f;

		// 移動速度を計算
		velocity_.x = cos(angle) * magnitude * maxSpeed;
		velocity_.y = sin(angle) * magnitude * maxSpeed;
	}
#pragma endregion

	worldTransform_.translation_ += velocity_;

}

void Player::Attack() {
	if (primaryAttackCoolTime<0) {
		if (Input::GetInstance()->ReleseKey(DIK_U)||xinput_.Gamepad.wButtons==XINPUT_GAMEPAD_X&&preXinput_.Gamepad.wButtons!=XINPUT_GAMEPAD_X) {
			std::shared_ptr<EnemyBullet> acceleration(new PlayerAccelerationBullet);
			acceleration->Initialize(bulletModel_, GetWorldPosition());
			acceleration->SetTagetPos(enemyPos);
			// acceleration->SetStartPos(worldTransform_.translation_);
			gameScene_->AddPlayerBullet(acceleration);
			primaryAttackCoolTime = kPrimaryAttackCoolTime;
		}
	} else {
		primaryAttackCoolTime--;
	}
	if (secondaryAttackCoolTime < 0) {
		if (Input::GetInstance()->ReleseKey(DIK_I) || xinput_.Gamepad.wButtons == XINPUT_GAMEPAD_Y && preXinput_.Gamepad.wButtons != XINPUT_GAMEPAD_Y) {
			std::shared_ptr<EnemyBullet> straight(new Straight);
			straight->Initialize(bulletModel_, GetWorldPosition());
			Vector3 direction = enemyPos - GetWorldPosition();
			direction = Normalize(direction);
			straight->SetTagetPos(direction);
			// straight->SetStartPos(worldTransform_.translation_);
			gameScene_->AddPlayerBullet(straight);
			secondaryAttackCoolTime = kSecondaryAttackCoolTime;
		}
	} else {
		secondaryAttackCoolTime--;
	}

	if (tertiaryAttackCoolTime<0) {
		if (Input::GetInstance()->ReleseKey(DIK_O) || xinput_.Gamepad.wButtons == XINPUT_GAMEPAD_B && preXinput_.Gamepad.wButtons != XINPUT_GAMEPAD_B) {
			Vector3 direction = enemyPos - GetWorldPosition();
			direction = Normalize(direction);
			for (int i = 0; i < 60; i++) {
				std::shared_ptr<EnemyBullet> zoldrak(new Zoldorak);
				zoldrak->Initialize(zoldrakModel_, direction * (radius_ * i + radius_ /*/ 2*/));
				zoldrak->SetTagetPos(direction);
				zoldrak->SetPlayer(this);
				zoldrak->SetBullet(Bullet::Zoldorak);
				gameScene_->AddPlayerBullet(zoldrak);
			}
			tertiaryAttackCoolTime = kTertiaryAttackCoolTime;
		}
		
	} else {
		tertiaryAttackCoolTime--;
	}
}

	



