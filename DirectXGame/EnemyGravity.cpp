#include "EnemyGravity.h"

#include "../DirectXGame/GrabityBigBullet.h"
#include "../DirectXGame/GrabityBulletSecond.h"
#include "../DirectXGame/Scene/GameScene.h"
#include "EnemyBullet.h"
#include "GrabiltBullet.h"

#include "../DirectXGame/Player.h"
#include <algorithm>
using namespace MathUtility;

void EnemyGravity::Update() {
	if (!isStart_) {
		HP = kMaxHP;

		enemyMode = EnemyMode::First;
		HP = 30;
		isStart_ = true;
	}

	if (HP < kChangeModeHP && enemyMode != EnemyMode::Second) {
		enemyMode = EnemyMode::Second;
		isStartMode = false;
	} else if (HP < 1) {
		isDelete_ = true;
	}

#ifdef _DEBUG
	DrowImgui();
#endif // _DEBUG

	modeUpdate[enemyMode]();

	worldTransform_.UpdateMatrix();
}

void EnemyGravity::DrowImgui() {
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat("miniTime", &miniBulletTimer_, 0.1f);
	ImGui::DragFloat("BigTime", &bigBulletTimer_, 0.1f);
	ImGui::DragInt("HP", &HP);
	ImGui::End();
#endif // _DEBUG
}

Vector3 EnemyGravity::GetPlayerPos() {
	Vector3 PlayerPos;

	PlayerPos = player_->GetWorldPosition();

	return PlayerPos;
}

void EnemyGravity::LowerPlayer() { player_->AddVelocity(Vector3{0.0f, playerFollSpeed, 0.0f}); }

void EnemyGravity::modeFirst() {
	if (!isStartMode) {
		miniBulletTimer_ = kMiniBulletStartTime_;
		bigBulletTimer_ = kBigBulletStartTime_;

		bigBulletTimer_ = kBigBulletTime_;

		miniBulletCount = kMiniBulletMaxConunt_;
		isStartMode = true;
	}

	LowerPlayer();

	miniBulletTimer_ -= flameTime;
	bigBulletTimer_ -= flameTime;

	miniBulletTimer_ = std::clamp(miniBulletTimer_, 0.0f, kMiniBulletTime_);

	if (miniBulletTimer_ <= 0.0f) {
		if (miniBulletCount <= kMiniBulletMaxConunt_) {
			for (float x = rightEdgeX; x >= leftEdgeX; x -= spacing) {
				std::shared_ptr<EnemyBullet> grabityBullet_(new GrabiltBullet);
				grabityBullet_->Initialize(bulletModel_, Vector3{x, -initialY, 0.0f});
				gameScene_->AddEnemyBullet(grabityBullet_);
			}
			miniBulletTimer_ = kMiniBulletIntervalTime_;
			miniBulletCount--;
			if (miniBulletCount <= 0) {
				miniBulletTimer_ = kMiniBulletTime_; // 1.5秒のクールタイム
				miniBulletCount = kMiniBulletMaxConunt_;
			}
		}
	}

	if (bigBulletTimer_ < 0.0f) {
		PlayerFollBigBullet();

		bigBulletTimer_ = kBigBulletTime_;
	}
}

void EnemyGravity::PlayerFollBigBullet() {
	Vector3 playerPos = GetPlayerPos();

	std::shared_ptr<EnemyBullet> grabityBullet_(new GrabityBigBullet);
	grabityBullet_->Initialize(bulletModel_, Vector3{playerPos.x, -initialY, 0.0f});
	grabityBullet_->SetScale(kBigBulletScale);
	grabityBullet_->SetPlayer(player_);
	gameScene_->AddEnemyBullet(grabityBullet_); // プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す
}

void EnemyGravity::modeSecond() {
	if (!isStartMode) {
		miniBulletTimer_ = kMiniBulletStartTime_;
		bigBulletTimer_ = kMiniBulletStartTime_;

		isStartMode = true;
	}

	RepelPlayer();

	miniBulletTimer_ -= flameTime;
	bigBulletTimer_ -= flameTime;

	if (miniBulletTimer_ < 0.0f) {
		Vector3 playerPos = GetPlayerPos();
		float angle_increment = 2 * PI / kBulletPoint; // 円周を等分割するための角度の増分
		for (int i = 0; i < kBulletPoint; i++) {
			float angle = static_cast<float>(i) * angle_increment;
			Vector3 pos;
			pos.x = playerPos.x + radius * cosf(angle);
			pos.y = playerPos.y + radius * sinf(angle);
			pos.z = 0.0f;

			std::shared_ptr<EnemyBullet> grabityBullet_(new GrabityBulletSecond);
			grabityBullet_->Initialize(bulletModel_, pos);
			grabityBullet_->GetPlayerPos(playerPos);
			gameScene_->AddEnemyBullet(grabityBullet_); // プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す
		}
		miniBulletTimer_ = 5.0f;
	}
	if (bigBulletTimer_ < 0.0f) {
		Vector3 playerPos = GetPlayerPos();

		for (float x = rightEdgeX; x >= leftEdgeX; x -= bigBulletSpace) {

			std::shared_ptr<EnemyBullet> grabityBullet_(new GrabiltBullet);
			grabityBullet_->Initialize(bulletModel_, Vector3{x, -initialY, 0.0f});
			grabityBullet_->SetScale(3.0f);
			gameScene_->AddEnemyBullet(grabityBullet_); // プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す
		}

		bigBulletTimer_ = 5.0f;
	}
}

void EnemyGravity::RepelPlayer() {
	Vector3 playerPos = GetPlayerPos();

	// プレイヤーからエネミーへのベクトルを計算
	Vector3 direction = playerPos - worldTransform_.translation_;

	// ベクトルを正規化（単位ベクトルに変換）
	float length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
	if (length != 0) {
		direction.x /= length;
		direction.y /= length;
		direction.z /= length;
	}

	// 反発する速度を設定（適切なスケールを掛ける）
	Vector3 repelVelocity = direction * repelSpeed;

	// プレイヤーに反発する速度を加える
	player_->AddVelocity(repelVelocity);
}
