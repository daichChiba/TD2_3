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
			std::shared_ptr<EnemyBullet> grabityBullet_(new GrabiltBullet);
			grabityBullet_->Initialize(bulletModel_, Vector3{ worldTransform_.translation_.x, 19.3f, 0.0f});
			SetGameScene(gameScene_);
			gameScene_->AddEnemyBullet(grabityBullet_);

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
