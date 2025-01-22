#include "Player.h"
//#include "magic"
#include<cassert>
#include "EnemyManager.h"

#include"../DirectXGame/Scene/GameScene.h"
#include"PlayerNormalBullet.h"
using namespace MathUtility;
void Player::Initialize(Model* model, const Vector3 position, Character character, Model* bulletModel) {
	assert(model);
	model_ = model;
	bulletModel_ = bulletModel;

	character_ = character;

	//camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = {0.0f, 0.5f, 0.0f};

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
		const float maxSpeed = 0.1f;

		// 移動速度を計算
		velocity_.x = cos(angle) * magnitude * maxSpeed;
		velocity_.y = sin(angle) * magnitude * maxSpeed;
	}
#pragma endregion

	worldTransform_.translation_ += velocity_;

}

void Player::Attack() {
	if (primaryAttackCoolTime<0) {
		if (Input::GetInstance()->ReleseKey(DIK_U)) {
			std::shared_ptr<EnemyBullet> normal(new PlayerNormalBullet);
			normal->Initialize(bulletModel_, GetWorldPosition());
			//normal->GetTagetPos()
			gameScene_->AddEnemyBullet(normal);
			primaryAttackCoolTime = kPrimaryAttackCoolTime;

		}
	} else {
		primaryAttackCoolTime--;
	}
}

	



