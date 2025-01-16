#include "../DirectXGame/GrabiltBullet.h"

using namespace MathUtility;

void GrabiltBullet::Update()
{
	if(!isStart_ )
	{
		velocity_.y = gravity;
	
		if (worldTransform_.scale_.x < 1.0f)
		{
			velocity_.y = BigBulletGrabity;
		}

		isStart_ = true;
	}

	worldTransform_.translation_ += velocity_;

	DrowImgui();
	
	worldTransform_.UpdateMatrix();

	if (worldTransform_.translation_.y < -23.3f)
	{
		isDelete_ = true;
	}
}

void GrabiltBullet::DrowImgui()
{
#ifdef _DEBUG

	ImGui::Begin("EnemyBullet");
	ImGui::Text("bullet");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.0001f);
	ImGui::DragFloat3("sce", &worldTransform_.scale_.x, 0.001f);
	ImGui::DragFloat3("vel", &velocity_.x, 0.001f);
	ImGui::End();
#endif // _DEBUG
}
