#include "GrabityBigBullet.h"
#include "ActorManager.h"
#include "PlayerActor.h"
using namespace MathUtility;

void GrabityBigBullet::Update() {
	if (!isStart_) {
		velocity_.y = gravity;

		isStart_ = true;
	}

	worldTransform_.translation_ += velocity_;

	DrowImgui();

	//PlayerSuction();

	worldTransform_.UpdateMatrix();

	if (worldTransform_.translation_.y < -23.3f) {
		isDelete_ = true;
	}
}

void GrabityBigBullet::PlayerSuction()
{
	playerPos = actorManager->GetPlayer()->GetWorldPosition();

	Vector3 direction = playerPos - worldTransform_.translation_;

	float distance = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

	if (distance < Suction)
	{
		actorManager->GetPlayer()->AddVelocity( -direction * PlayerSuctionSpeed);
	}
}

void GrabityBigBullet::DrowImgui() {
#ifdef _DEBUG

	ImGui::Begin("EnemyBullet");
	ImGui::Text("bullet");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.0001f);
	ImGui::DragFloat3("sce", &worldTransform_.scale_.x, 0.001f);
	ImGui::DragFloat3("vel", &velocity_.x, 0.001f);
	ImGui::End();
#endif // _DEBUG
}
