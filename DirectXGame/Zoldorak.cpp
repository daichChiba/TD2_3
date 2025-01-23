#include "Zoldorak.h"
using namespace MathUtility;
void Zoldorak::Update() {
	if (!start) {
		start = true;
		isDelete_ = false;
		isHit_ = false;
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
