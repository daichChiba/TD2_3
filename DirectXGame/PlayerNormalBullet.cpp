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
		currentTime = 0.0f;
	}

	DrowImgui();

	float duration = static_cast<float>(kMoveTimer) / 60.0f; // フレーム数を秒数に変換（例：60fpsなら1/60）

	if (currentTime < duration) {
		// イージングを適用して弾の位置を更新
		Vector3 newPosition = Easings::EaseInTime(startPos, tagetPos, currentTime, duration);
		newPosition.z = 0.0f;
		worldTransform_.translation_ = newPosition;

		currentTime += 1.0f / 60.0f; // 1フレームごとに時間を進める(60fpsを想定)
	} else {
		// 移動完了後の処理
		deleteTimer++;
	}

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
	// ImGui::Checkbox("isDelete_", &isDelete_);
	ImGui::End();
#endif // _DEBUG
}
