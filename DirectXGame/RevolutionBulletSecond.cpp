#include "RevolutionBulletSecond.h"

using namespace MathUtility;
void RevolutionBulletSecond::SetPlayerPos(Vector3 pos) { targetPos = pos; }

void RevolutionBulletSecond::Update() {
	if (!isStart_) {
		direction *= -1.0f;
		delay = kdelay;
		color->SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.8f));
		isStart_ = true;
	}
	delay -= 1.0f / 60.0f;

	DrawImgui();

	if (delay <= 0.0f) {
		color->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		worldTransform_.translation_ = worldTransform_.translation_ * MakeRotateZMatrix(speed_);
	}
	worldTransform_.UpdateMatrix();
}

void RevolutionBulletSecond::DrawImgui() {
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.01f);
	//ImGui::DragFloat3("scale_", &worldTransform_.scale_.x, 0.01f);
	// ImGui::DragFloat("miniTime", &miniBulletTimer_, 0.1f);
	// ImGui::DragInt("HP", &hp);
	ImGui::End();
#endif // _DEBUG
}
