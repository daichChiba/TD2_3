#include "EnemyGravity.h"

#include "EnemyBullet.h"
#include "GrabiltBullet.h"
#include "../DirectXGame/Scene/GameScene.h"

void EnemyGravity::Update()
{
	if (!isStart_)
	{
		miniBulletTimer_ = kMiniBulletTime_;
		isStart_ = true;
	}

	miniBulletTimer_ -= flameTime;

	DrowImgui();

	worldTransform_.UpdateMatrix();
	
	if (miniBulletTimer_ < 0.0f)
	{
		for (float x = rightEdgeX; x >= leftEdgeX; x -= spacing)
		{
			std::shared_ptr<EnemyBullet> grabityBullet_(new GrabiltBullet);
			grabityBullet_->Initialize(bulletModel_, Vector3{ x, -initialY, 0.0f });
			gameScene_->AddEnemyBullet(grabityBullet_);//プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す
		}

		miniBulletTimer_ = kMiniBulletTime_;
	}
}

void EnemyGravity::DrowImgui()
{
	float pos[] = {worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z };

	ImGui::Begin("enemy");
	ImGui::DragFloat3("pos", pos, 0.01f);
	ImGui::DragFloat("timre", &miniBulletTimer_,0.1f);
	ImGui::End();

	worldTransform_.translation_.x = pos[0];
	worldTransform_.translation_.y = pos[1];
	worldTransform_.translation_.z = pos[2];
}
