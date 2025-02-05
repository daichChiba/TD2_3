#include "PlayerActor.h"

#include "ActorManager.h"
#include"EnemyManager.h"


using namespace MathUtility;

void PlayerActor::Initialize(Model* model, Model* bulletModel, Model* beamModel, const Vector3 position, GameScene* gameScene, ActorManager* actor) {
	model_ = model;
	bulletModel_ = bulletModel;
	zoldrakModel_ = beamModel;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	gameScene_ = gameScene;
	actorManager = actor;

	hp = 10;
}

void PlayerActor::Update() {
	// 入力の更新
	preXinput_ = xinput_;
	// XInputの状態を取得
	XInputGetState(0, &xinput_);

	// 移動処理
	Move();

	// 攻撃処理
	Attack();

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

void PlayerActor::Draw(Camera* camera) {
	if (model_) {
		model_->Draw(worldTransform_, *camera);
	}
}

Vector3 PlayerActor::GetWorldPosition() { return worldTransform_.translation_; }

void PlayerActor::AddVelocity(Vector3 velocity) { velocity_ += velocity; }

void PlayerActor::OnCollision() {
	hp --;
}

void PlayerActor::PrimaryAttack() {
	// プライマリ攻撃の処理
}

void PlayerActor::SecondaryAttack() {
	// セカンダリ攻撃の処理
}

void PlayerActor::SpechalAttack() {
	// ターシャリ攻撃の処理
}

void PlayerActor::Move() {
	if (worldTransform_.translation_.x >= actorManager->GetEnemy()->GetWorldPos().x) {
		worldTransform_.rotation_.y = 5.0f;
	} else {
		worldTransform_.rotation_.y = -5.0f;
	}

	worldTransform_.translation_ += velocity_;
	
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

	if (lx != 0.0f || ly != 0.0f) {
		// デッドゾーンの設定(スティックがニュートラルに近い場合に意図せず移動しないようにする)
		const float deadZone = 0.1f;
		if (fabs(lx) < deadZone)
			lx = 0.0f;
		if (fabs(ly) < deadZone)
			ly = 0.0f;

		// スティックの強度と角度を計算
		float magnitude = sqrtf(lx * lx + ly * ly); // 入力強度（0 ～ 1）
		float angle = atan2f(ly, lx);               // スティックの角度（ラジアン）

		// 最大速度
		const float maxSpeed = 0.3f;

		// 移動速度を計算
		velocity_.x = cos(angle) * magnitude * maxSpeed;
		velocity_.y = sin(angle) * magnitude * maxSpeed;
	}
#pragma endregion

	worldTransform_.translation_ += velocity_;

	velocity_ = Vector3Zero();
}

void PlayerActor::Attack() {
	// 攻撃処理の実装
	if (xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		PrimaryAttack();
	}
	if (xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		SecondaryAttack();
	}
	if (xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		SpechalAttack();
	}
}
