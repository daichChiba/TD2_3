#include "Zoldorak.h"
#include "../ActorManager.h"
#include "../player/PlayerManager.h"
using namespace MathUtility;
void Zoldorak::Update() {
	if (!start) {
		start = true;
		isDelete_ = false;
		isHit_ = false;
		// worldTransform_.scale_ = {0.5f, 0.2f, 0.2f};
		pos_ = worldTransform_.translation_;
		worldTransform_.translation_ = pos_ + actorManager->GetPlayer()->GetWorldPosition();
		worldTransform_.rotation_.z += std::atan2(direction.y, direction.x);
		color->SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.8f));
		// worldTransform_.rotation_ = Vector3(1.0f,0.0f,0.0f)*MakeRotateZMatrix(rotate);
	}
	if (!isHit_) {
		predictionTimer++;

		if (isFire_ == false) {
			if (color->GetColor().w > 0.5f) {
				color->SetColor(Vector4(1.0f, 1.0f, 1.0f, color->GetColor().w - 0.005f));
				if (color->GetColor().w <= 0.5f) {
					isFire_ = true;
				}
			}
		} else {
			if (color->GetColor().w < 0.75f && color->GetColor().w < 1.0f) {
				color->SetColor(Vector4(1.0f, 1.0f, 1.0f, color->GetColor().w + 0.05f));
				if (color->GetColor().w >= 1.0f) {
					isFire_ = false;
				}
			}
		}

		if (predictionTimer >= kPredictionTimer) {
			isHit_ = true;
			worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
			color->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	} else {
		firingTimer++;
		if (firingTimer >= kFiringTimer) {
			isDelete_ = true;
		}
	}

	worldTransform_.UpdateMatrix();
}

void Zoldorak::OnCollision() { isHit_ = true; }

void Zoldorak::Draw(Camera* camera) {
	if (isDraw_) {
		model_->Draw(worldTransform_, *camera, color);
	}
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
