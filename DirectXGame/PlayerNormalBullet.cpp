#include "PlayerNormalBullet.h"
#include "Easings.h"
#include "EnemyBullet.h"
#include "Player.h"
using namespace KamataEngine;
using namespace MathUtility;
void PlayerNormalBullet::Update() {
	if (!start) {
		
		start = true;
		startPos = worldTransform_.translation_;
		isDelete_ = false;	
	}

	DrowImgui();

	if (moveTimer < kMoveTimer) {
		moveTimer++;
	} else {
		deleteTimer++;
	}
	// 移動方向のベクトルを計算
	Vector3 direction = tagetPos - startPos;

	// 移動方向を正規化
	Vector3 normalizeDirection = Normalize(direction);

	velocity_ = Easings::EaseInTime(direction,normalizeDirection );
	velocity_.z = 0.0f;
	worldTransform_.translation_ += velocity_;
	//// イージングの値を取得
	//float easeValue = Easings::EaseInTime(static_cast<float>(moveTimer), static_cast<float>(kMoveTimer));

	//// 正規化された方向ベクトルにイージングとスピードをかけ、移動量を計算
	//float speed = kMaxSpeed * easeValue; // イージングによってスピードを調整
	//worldTransform_.translation_ = startPos + (normalizedDirection * speed * static_cast<float>(kMoveTimer));

	if (deleteTimer >= kDeleteTimer) {
		isDelete_ = true;
	}

	worldTransform_.UpdateMatrix();
}

void PlayerNormalBullet::DrowImgui() {
#ifdef _DEBUG
	ImGui::Begin("playerBullet");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.01f);	
	ImGui::DragFloat3("targetPos", &tagetPos.x, 0.01f);	
	ImGui::DragFloat3("startPos", &startPos.x, 0.01f);	
	//ImGui::Checkbox("isDelete_", &isDelete_);
	ImGui::End();
#endif // _DEBUG
}
