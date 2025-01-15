#include "EnemyGravity.h"

#include "EnemyBullet.h"
#include "GrabiltBullet.h"
#include "../DirectXGame/Scene/GameScene.h"

#include "../DirectXGame/Player.h"
void EnemyGravity::Update()
{
	if (!isStart_)
	{
		HP = kMaxHP;

		enemyMode = EnemyMode::First; 

		isStart_ = true;
	}

	//miniBulletTimer_ -= flameTime;
	bigBulletTimer_ -= flameTime;

	if (HP < kChangeModeHP)
	{
		enemyMode = EnemyMode::Second;
	}else if (HP < 1)
	{
		isDelete_ = true;
	}

#ifdef _DEBUG
	DrowImgui();
#endif // _DEBUG

	
	modeUpdate[enemyMode]();

	worldTransform_.UpdateMatrix();
	
	
}
	
void EnemyGravity::DrowImgui()
{
	
	ImGui::Begin("enemy");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat("timre", &miniBulletTimer_,0.1f);
	ImGui::DragFloat("timre", &bigBulletTimer_,0.1f);
	ImGui::End();

	
}

Vector3 EnemyGravity::GetPlayerPos()
{
	Vector3 PlayerPos;

	PlayerPos = player_->GetPlayerPos();

	return PlayerPos;
}

void EnemyGravity::modeFirst()
{
	if(!isStartMode)
	{
		miniBulletTimer_ = kMiniBulletStartTime_;
		bigBulletTimer_ = kBigBulletStartTime_;
		isStart_ = true;

		miniBulletOffset_ = 0.0f;

		isStartMode = true;
	}

	

	if (miniBulletTimer_ < 0.0f)
	{

		miniBulletOffset_ = (miniBulletOffset_ == 0.0f) ? spacing / 2.0f : 0.0f; 

		for (float x = rightEdgeX + miniBulletOffset_; x >= leftEdgeX; x -= spacing)
		{
			std::shared_ptr<EnemyBullet> grabityBullet_(new GrabiltBullet);
			grabityBullet_->Initialize(bulletModel_, Vector3{ x, -initialY, 0.0f });
			gameScene_->AddEnemyBullet(grabityBullet_);//プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す
		}

		miniBulletTimer_ = kMiniBulletTime_;
	}
	
	if (bigBulletTimer_ < 0.0f)
	{
		Vector3 playerPos = GetPlayerPos();

		//std::shared_ptr<EnemyBullet> grabityBullet_(new GrabiltBullet);
		//grabityBullet_->Initialize(bulletModel_, Vector3{ playerPos.x, -initialY, 0.0f });
		//grabityBullet_->SetScale(kBigBulletScale);
		//gameScene_->AddEnemyBullet(grabityBullet_);//プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す

		bigBulletTimer_ = kBigBulletTime_;
	}

}

void EnemyGravity::modeSecond()
{

}
