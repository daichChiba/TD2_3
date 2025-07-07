#include "MeteoriteBullet.h"
using namespace MathUtility;

void MeteoriteBullet::Update() {
	if (!isStart_) {
		startPos = worldTransform_.translation_;
		isStart_ = true;
		timer;
		isDelete_ = false;
	}

	if (isStart_) {
		if (timer < kTimer) {
			timer++;
		}
		worldTransform_.translation_ = Vector3Lerp(startPos, targetPos, static_cast<float>(timer) / static_cast<float>(kTimer));
	}

	DrawImgui();

	worldTransform_.UpdateMatrix();
}

void MeteoriteBullet::SetTagetPos(Vector3 pos) { targetPos = pos; }

void MeteoriteBullet::DrawImgui() {
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
}
