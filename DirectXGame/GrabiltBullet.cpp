#include "GrabiltBullet.h"

using namespace MathUtility;

void GrabiltBullet::Update()
{
	velocity_ .y = fallSpeed_;

	worldTransform_.translation_ += velocity_;

	DrowImgui();
	
	worldTransform_.UpdateMatrix();

	if (worldTransform_.translation_.y < 19.3f)
	{
		isDelete_ = true;
	}
}

void GrabiltBullet::DrowImgui()
{
	
	float pos[] = {worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z };

	ImGui::Begin("EnemyBullet");
	ImGui::DragFloat3("pos", pos, 0.001f);
	ImGui::End();

	worldTransform_.translation_.x = pos[0];
	worldTransform_.translation_.y = pos[1];
	worldTransform_.translation_.z = pos[2];
}
