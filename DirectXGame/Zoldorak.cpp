#include "Zoldorak.h"
using namespace MathUtility;
void Zoldorak::Update() {
	if (!start) {
		start = true;
		isDelete_ = false;
		isHit_ = false;
		worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
		worldTransform_.rotation_.z = std::atan2(direction.y, direction.x);
		//worldTransform_.rotation_ = Vector3(1.0f,0.0f,0.0f)*MakeRotateZMatrix(rotate);
	}
	if (!isHit_) {
		predictionTimer++;
		if (predictionTimer>=kPredictionTimer) {
			isHit_ = true;
		}
	} else {
		firingTimer++;
		if (firingTimer>=kFiringTimer) {
			isDelete_ = true;
		}
	}


	worldTransform_.UpdateMatrix();
}

void Zoldorak::DrowImgui() {
#ifdef _DEBUG
	ImGui::Begin("playerBullet");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.01f);
	// ImGui::DragFloat3("targetPos", &tagetPos.x, 0.01f);
	// ImGui::DragFloat3("startPos", &startPos.x, 0.01f);
	//  ImGui::Checkbox("isDelete_", &isDelete_);
	ImGui::End();
#endif // _DEBUG
}
