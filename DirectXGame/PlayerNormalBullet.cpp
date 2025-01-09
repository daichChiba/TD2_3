#include "PlayerNormalBullet.h"
#include"EnemyBullet.h"
#include "Player.h"
#include "Easings.h"
using namespace KamataEngine;
using namespace MathUtility;
void PlayerNormalBullet::Update() {
	if (!start) {
		tagetPos = player_->GetWorldPosition();
		start = true;
		startPos = worldTransform_.translation_;
	}

	if (moveTimer < kMoveTimer) {
		moveTimer++;
	} else {
		deleteTimer++;
	}
	worldTransform_.translation_ =
		Vector3Lerp(startPos, tagetPos, Easings::EaselnQuart(static_cast<float>(moveTimer) / static_cast<float>(kMoveTimer)));

	if (deleteTimer >= kDeleteTimer) {
		isDelete_ = true;
	}

	worldTransform_.UpdateMatrix();
}
