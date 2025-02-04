#include "EnemyRevolution.h"

#include "../DirectXGame/Player.h"
#include "../DirectXGame/Scene/GameScene.h"

#include "EnemyBullet.h"
#include "GrabityBulletSecond.h"
#include "EnemyRevolutionBullet.h"

using namespace MathUtility;

void EnemyRevolution::Update() {
	if (!isStart_) {
		hp = kMaxHp;

		enemyMode = EnemyMode::First;

		miniBulletTimer_ = 1.0f;

		isStart_ = true;
	}

#ifdef _DEBUG
	DrawImgui();
#endif //  _DEBUG

	modeUpdate[enemyMode]();
	worldTransform_.UpdateMatrix();
}

void EnemyRevolution::DrawImgui() {}

void EnemyRevolution::modeFirst() {
	miniBulletTimer_ -= flameTime;

	if (miniBulletTimer_ < 0.0f) {
		Vector3 bulletStartPos = worldTransform_.translation_;

		// 上下左右の位置を計算
		Vector3 positions[2];
		positions[0] = {bulletStartPos.x, bulletStartPos.y + radius, bulletStartPos.z}; // 上
		positions[1] = {bulletStartPos.x, bulletStartPos.y - radius, bulletStartPos.z}; // 下
		//positions[2] = {bulletStartPos.x + radius, bulletStartPos.y, bulletStartPos.z}; // 右
		//positions[3] = {bulletStartPos.x - radius, bulletStartPos.y, bulletStartPos.z}; // 左

		for (const auto& Bulletpos : positions) {
			float angle_increment = 2 * PI / kBulletPoint; // 円周を等分割するための角度の増分
			for (int i = 0; i < kBulletPoint; i++) {
				float angle = static_cast<float>(i) * angle_increment;
				Vector3 pos;
				pos.x = Bulletpos.x + radius * cosf(angle);
				pos.y = Bulletpos.y + radius * sinf(angle);
				pos.z = 0.0f;

				std::shared_ptr<EnemyBullet> grabityBullet_(new EnemyRevolutionBullet);
				grabityBullet_->Initialize(bulletModel_, pos);
				grabityBullet_->GetPlayerPos(bulletStartPos);
				gameScene_->AddEnemyBullet(grabityBullet_); // プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す
			}
		}
		miniBulletTimer_ = 5.0f;
	}
}

void EnemyRevolution::modeSecond() {

}

Vector3 EnemyRevolution::GetPlayerPos() {
	//player_->GetWorldPosition();
	//return Vector3(player_->GetWorldPosition());
	return Vector3Zero();
}
