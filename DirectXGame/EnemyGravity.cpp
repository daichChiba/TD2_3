#include "EnemyGravity.h"

#include "../DirectXGame/Scene/GameScene.h"
#include "EnemyBullet.h"
#include "GrabiltBullet.h"
#include "../DirectXGame/GrabityBulletSecond.h"

#include "../DirectXGame/Player.h"
using namespace MathUtility;

void EnemyGravity::Update() {
	if (!isStart_) {
		HP = kMaxHP;

		enemyMode = EnemyMode::First;
		HP = 49;
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

	ImGui::Begin("enemy");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat("miniTime", &miniBulletTimer_, 0.1f);
	ImGui::DragFloat("BigTime", &bigBulletTimer_, 0.1f);
	ImGui::DragInt("HP", &HP);
	ImGui::End();
}

Vector3 EnemyGravity::GetPlayerPos() {
	Vector3 PlayerPos;

	PlayerPos = player_->GetPlayerPos();

	return PlayerPos;
}

void EnemyGravity::modeFirst() {
	if (!isStartMode) {
		miniBulletTimer_ = kMiniBulletStartTime_;
		bigBulletTimer_ = kBigBulletStartTime_;

		miniBulletOffset_ = 0.0f;

		bigBulletTimer_ = kBigBulletTime_;

		isStartMode = true;
	}

	miniBulletTimer_ -= flameTime;
	bigBulletTimer_ -= flameTime;


	if (miniBulletTimer_ < 0.0f) {

		miniBulletOffset_ = (miniBulletOffset_ == 0.0f) ? spacing / 2.0f : 0.0f;

		for (float x = rightEdgeX + miniBulletOffset_; x >= leftEdgeX; x -= spacing) {
			std::shared_ptr<EnemyBullet> grabityBullet_(new GrabiltBullet);
			grabityBullet_->Initialize(bulletModel_, Vector3{x, -initialY, 0.0f});
			gameScene_->AddEnemyBullet(grabityBullet_); // プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す
		}

		miniBulletTimer_ = kMiniBulletTime_;
	}

	if (bigBulletTimer_ < 0.0f) {
		PlayerFollBigBullet();

		bigBulletTimer_ = kBigBulletTime_;
	}
}

void EnemyGravity::PlayerFollBigBullet() {
	Vector3 playerPos = GetPlayerPos();

	std::shared_ptr<EnemyBullet> grabityBullet_(new GrabiltBullet);
	grabityBullet_->Initialize(bulletModel_, Vector3{playerPos.x, -initialY, 0.0f});
	grabityBullet_->SetScale(kBigBulletScale);
	gameScene_->AddEnemyBullet(grabityBullet_); // プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す
}

void EnemyGravity::modeSecond() {
	if (!isStartMode) {
		miniBulletTimer_ = kMiniBulletStartTime_;

		isStartMode = true;
	}

	miniBulletTimer_ -= flameTime;

	if (miniBulletTimer_ < 0.0f)
	{
		Vector3 playerPos = GetPlayerPos();
		float angle_increment = 2 * PI / kBulletPoint; // 円周を等分割するための角度の増分
		for(int i = 0; i < kBulletPoint; i++)
		{
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
		miniBulletTimer_ = kMiniBulletTime_;
	}

}