#include "Straight.h"
using namespace MathUtility;

void Straight::Update() {
	if (!start) {
		start = true;
		isDelete_ = false;
	}
	
	DrowImgui();

	worldTransform_.translation_ += direction*speed;


	worldTransform_.UpdateMatrix();
}

void Straight::DrowImgui() {
#ifdef _DEBUG
	ImGui::Begin("playerBullet");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.01f);
	//ImGui::DragFloat3("targetPos", &tagetPos.x, 0.01f);
	//ImGui::DragFloat3("startPos", &startPos.x, 0.01f);
	// ImGui::Checkbox("isDelete_", &isDelete_);
	ImGui::End();
#endif // _DEBUG
}
