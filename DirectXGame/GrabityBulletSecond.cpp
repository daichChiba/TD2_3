#include "GrabityBulletSecond.h"
using namespace MathUtility;

void GrabityBulletSecond::GetPlayerPos(Vector3 pos) { targetPos = pos; }

void GrabityBulletSecond::Update() {

	if (!isStart_) {
		speed = kSpeed;
		direction = targetPos - worldTransform_.translation_;
		direction *= -1.0f;

		isStart_ = true;
	}

	float distance = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
	
	if (distance > 25.0f) {
		isDelete_ = true;
	}
	velocity_ = direction * speed;

	worldTransform_.translation_ += velocity_;

	DrowImgui();

	worldTransform_.UpdateMatrix();
}

void GrabityBulletSecond::DrowImgui() {
#ifdef _DEBUG
	ImGui::Begin("GraBullet");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x);
	ImGui::DragFloat("speed", &speed);
	ImGui::End();
#endif // _DEBUG
}
