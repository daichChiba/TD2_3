#include "MeteoriteBullet.h"

void MeteoriteBullet::SetPlayerPos(Vector3 pos) { targetPos = pos; }

void MeteoriteBullet::Update() {
	if (!isStart_) {
		goalPos = targetPos;
		goalPos.x = targetPos.x * -1.0f;
		isStart_ = true;
	}
	DrawImgui();
	speed_ = MathUtility::Length(goalPos);

	if (worldTransform_.translation_.x >= goalPos.x) {
		worldTransform_.translation_.x += speed_;
	}
	worldTransform_.UpdateMatrix();
}

void MeteoriteBullet::DrawImgui() {
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("MeteoritePos", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
}
