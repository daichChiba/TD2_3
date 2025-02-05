#include "EnemyRevolution.h"

#include "../DirectXGame/Player.h"
#include "../DirectXGame/Scene/GameScene.h"

#include "EnemyBullet.h"
#include "EnemyRevolutionBullet.h"
#include "GrabityBulletSecond.h"
#include "MeteoriteBullet.h"
#include "RevolutionBulletSecond.h"

using namespace MathUtility;

void EnemyRevolution::Update() {
	if (!isStart_) {
		hp = kMaxHp;

		enemyMode = EnemyMode::First;

		miniBulletTimer_ = 1.0f;

		isStart_ = true;
	}

	if (hp < kChangeModeHP && enemyMode != EnemyMode::Second) {
		enemyMode = EnemyMode::Second;
		isStartMode = false;
	} else if (hp < 1) {
		isDelete_ = true;
	}

#ifdef _DEBUG
	DrawImgui();
#endif //  _DEBUG

	modeUpdate[enemyMode]();
	worldTransform_.UpdateMatrix();
}

void EnemyRevolution::DrawImgui() {
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.01f);
	// ImGui::DragFloat("miniTime", &miniBulletTimer_, 0.1f);
	ImGui::DragInt("HP", &hp);
	ImGui::End();
#endif // _DEBUG
}

void EnemyRevolution::modeFirst() {
	// if (!isStartMode) {
	//	isStartMode = true;
	// }
	miniBulletTimer_ -= flameTime;

	if (miniBulletTimer_ < 0.0f) {
		Vector3 bulletStartPos = worldTransform_.translation_;

		// 上下左右の位置を計算
		Vector3 positions[2];
		positions[0] = {bulletStartPos.x, bulletStartPos.y + radius, bulletStartPos.z}; // 上
		positions[1] = {bulletStartPos.x, bulletStartPos.y - radius, bulletStartPos.z}; // 下
		// positions[2] = {bulletStartPos.x + radius, bulletStartPos.y, bulletStartPos.z}; // 右
		// positions[3] = {bulletStartPos.x - radius, bulletStartPos.y, bulletStartPos.z}; // 左

		for (const auto& Bulletpos : positions) {
			float angle_increment = 2 * PI / kBulletPoint; // 円周を等分割するための角度の増分
			for (int i = 0; i < kBulletPoint; i++) {
				float angle = static_cast<float>(i) * angle_increment;
				Vector3 pos;
				pos.x = Bulletpos.x + radius * cosf(angle);
				pos.y = Bulletpos.y + radius * sinf(angle);
				pos.z = 0.0f;

				std::shared_ptr<EnemyBullet> RevolutionBullet_(new EnemyRevolutionBullet);
				RevolutionBullet_->Initialize(bulletModel_, pos);
				RevolutionBullet_->SetPlayerPos(bulletStartPos);
				gameScene_->AddEnemyBullet(RevolutionBullet_); // プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す
			}
		}
		miniBulletTimer_ = 5.0f;
	}
}

void EnemyRevolution::modeSecond() {
	auto bulletUpStartPos = Vector3(0.0f, 0.0f, 0.0f);
	auto bulletDownStartPos = Vector3(0.0f, 0.0f, 0.0f);
	auto bulletDistance = 5.0f;

	if (!isSecondStart_) {

		for (auto i = 0; i < 4; i++) {
			bulletUpStartPos.y += bulletDistance;
			std::shared_ptr<EnemyBullet> RevolutionSecondUpBullet_(new RevolutionBulletSecond);
			RevolutionSecondUpBullet_->Initialize(bulletModel_, bulletUpStartPos);
			RevolutionSecondUpBullet_->SetPlayerPos(bulletUpStartPos);
			RevolutionSecondUpBullet_->SetSpeed(rotateSpeed_[i]);
			gameScene_->AddEnemyBullet(RevolutionSecondUpBullet_);
			bulletDownStartPos.y -= bulletDistance;
			std::shared_ptr<EnemyBullet> RevolutionSecondDownBullet_(new RevolutionBulletSecond);
			RevolutionSecondDownBullet_->Initialize(bulletModel_, bulletDownStartPos);
			RevolutionSecondDownBullet_->SetPlayerPos(bulletDownStartPos);
			RevolutionSecondDownBullet_->SetSpeed(rotateSpeed_[i]);
			gameScene_->AddEnemyBullet(RevolutionSecondDownBullet_);

		}
		std::shared_ptr<EnemyBullet> MeteoriteBullet_(new MeteoriteBullet);
		MeteoriteBullet_->Initialize(bulletModel_, worldTransform_.translation_);
		MeteoriteBullet_->SetPlayerPos(Vector3(-5.0, -5.0f, 0.0f));
		gameScene_->AddEnemyBullet(MeteoriteBullet_);
		isSecondStart_ = true;
	}
}

Vector3 EnemyRevolution::GetPlayerPos() {
	//player_->GetWorldPosition();
	//return Vector3(player_->GetWorldPosition());
	return Vector3Zero();
}
