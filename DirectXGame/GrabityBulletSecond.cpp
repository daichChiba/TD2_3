#include "GrabityBulletSecond.h"
using namespace MathUtility;

void GrabityBulletSecond::GetPlayerPos(Vector3 pos) { targetPos = pos; }

void GrabityBulletSecond::Update() {

	Vector3 direction = targetPos - worldTransform_.translation_;
		

	float distance = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

	velocity_ = direction * speed;
	
	
	if (distance < 0.5f) {
		isDelete_ = true;
	}

	worldTransform_.translation_ += velocity_;

	worldTransform_.UpdateMatrix();
}

void GrabityBulletSecond::DrowImgui() {
#ifdef _DEBUG
	ImGui::Begin("GraBullet");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x);
	ImGui::End();
#endif // _DEBUG


}
