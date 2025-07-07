#include "GameScene.h"
#include "../Action/ActorManager.h"
#include <cassert>
#include <corecrt_math.h>

#include "../Action/player/PlayerManager.h"
#include "../Action/player/PlayerActor.h"
#include "../Action/enemy/EnemyManager.h"
#include "../Action/enemy/EnemyActor.h"

using namespace KamataEngine;

// インストラクタ
GameScene::GameScene() {}
// デストラクタ
GameScene::~GameScene() {
	delete playerBulletModel_;
	delete playerBody_;
	delete skydomeModel_;
	audio_->StopWave(voiceHundle);
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	camera_ = new Camera();
	camera_->Initialize();
	camera_->translation_ = normalCameraPos_;

	isFinished = false;

	// playerのモデル
	playerBulletModel_ = new Model();
	// playerModel_->CreateFromOBJ("player", true);

	enemyModel_ = Model::CreateFromOBJ("enemy", true);

	// player_ = new Player()

	playerBulletModel_ = Model::CreateFromOBJ("playerBullet", true);

	playerBody_ = Model::CreateFromOBJ("playerBody", true);

	skydome_ = new Skydome();
	skydomeModel_ = Model::CreateFromOBJ("Skydome", true);
	skydome_->Initialize(skydomeModel_, camera_);

	playerBulletModel_ = Model::CreateFromOBJ("PlayerBullet");

	zoldorkModel_ = Model::CreateFromOBJ("Zoldorak", true);
	enemyBulletModel_ = Model::CreateFromOBJ("enemyBullet");

	//character_ = CX::wizard;
	// playerの初期化
	/*player_ = new Player();
	player_->Initialize(playerModel_, Vector3{0.0f}, character_, playerModel_, enemyModel_);
	player_->SetGameScene(this);*/
	PlayerHPResorces = TextureManager::Load("PlayerHP.png");
	EnemyHpResorces = TextureManager::Load("EnemyHP.png");
	PlayerHpHeafResorces = TextureManager::Load("PlayerHPHeaf.png");
	EnemyHpBarResorces = TextureManager::Load("EnemyHPBar.png");

	soundHundle = audio_->LoadWave("uchuusensou.mp3");
	//soundHundle = bgm_->LoadWave("fanfare.wav");
	voiceHundle = audio_->PlayWave(soundHundle, true);

	actorManager = new ActorManager;
	actorManager->Initialize(playerBody_, playerBulletModel_, zoldorkModel_, enemyModel_, enemyBulletModel_, Vector3{0.0f, 0.0f, 0.0f}, Vector3{0.0f, 0.0f, 0.0f}, this);
	

}

void GameScene::Update() {
	
	int enemyHp = actorManager->GetEnemy()->GetHp();
	if (enemyHp <= 0) {
		isFinished = true;
		isCleard = true;
	}
	
	if (actorManager->GetPlayer()->GetPlayerHP()<=0) {
		isFinished = true;
	}
	//if (actorManager->GetPlayer()->GetHp()<=0) {
	//	isFinished = true;
	//}

	//player_->Update();
	actorManager->Update();

	for(std::shared_ptr<EnemyBullet> playerBullet : playerBullets_)
	{ 
		playerBullet->Update(); 
	}
	
	for(std::shared_ptr<EnemyBullet> enemyBullet : enemiesBullet_)
	{ 
		enemyBullet->Update(); 
	}

	CheckAllCollisions();

	enemiesBullet_.remove_if([](std::shared_ptr<EnemyBullet> a) { return a->IsDelete(); });
	playerBullets_.remove_if([](std::shared_ptr<EnemyBullet> a) { return a->IsDelete(); });
#ifdef _DEBUG
	ImGui::Begin("gamescene");
	ImGui::DragFloat3("pPos", &playerPos.x);
	ImGui::End();
#endif // _DEBUG

}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	skydome_->Draw();

	actorManager->Draw(camera_);

	

	for(std::shared_ptr<EnemyBullet> playerBullet : playerBullets_)
	{ playerBullet->Draw(camera_); }
	
	for(std::shared_ptr<EnemyBullet> enemyBullet : enemiesBullet_)
	{ enemyBullet->Draw(camera_); }

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);



	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	actorManager->GetPlayer()->DrawHP();
	actorManager->GetEnemy()->DrawHp();
	actorManager->GetPlayer()->SpriteDraw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	 //判定対象AとBの座標
	 Vector3 posA, posB;

#pragma region 敵の弾とプレイヤーの当たり判定
	bool is = false;
	posA = actorManager->GetPlayer()->GetWorldPosition();
	playerPos = actorManager->GetPlayer()->GetWorldPosition();
	for (std::shared_ptr<EnemyBullet> enemyBullet : enemiesBullet_) {
		posB = enemyBullet->GetWorldPosition();
		Vector3 A2B = MathUtility::Sphere(posA, posB);
		float len = MathUtility::Length(A2B);
		float radius = enemyBullet->GetRadius() + actorManager->GetPlayer()->GetRadius();
		if (len <= radius) {
			// 自キャラの衝突時コールバックを呼び出す
			actorManager->GetPlayer()->OnCollision();
			// 自弾の衝突時コールバックを呼び出す
			enemyBullet->OnCollision();
		}
	}

#pragma endregion

#pragma region 自機の弾と敵の当たり判定
	posA = actorManager->GetEnemy()->GetWorldPos();
	for (std::shared_ptr<EnemyBullet> playerBullet : playerBullets_) {
		if (playerBullet->GetBullet() == Bullet::Zoldorak) {
			if (!is) {
				if (playerBullet->GetIsHit()) {
					posB = playerBullet->GetWorldPosition();
					Vector3 A2B = MathUtility::Sphere(posA, posB);
					float len = MathUtility::Length(A2B);
					float radius = playerBullet->GetRadius() + actorManager->GetEnemy()->GetRadius();
					if (len <= radius) {
						is = true;
						// playerBullet->OnCollision();

						actorManager->GetEnemy()->OnCollision(1);
					}
				}
			}
		} else {
			posB = playerBullet->GetWorldPosition();
			Vector3 A2B = MathUtility::Sphere(posA, posB);
			float len = MathUtility::Length(A2B);
			float radius = playerBullet->GetRadius() + actorManager->GetEnemy()->GetRadius();
			if (len <= radius) {
				playerBullet->OnCollision();

				actorManager->GetEnemy()->OnCollision(1);
			}
		}
	}
#pragma endregion

#pragma region 自機の弾と敵の弾の当たり判定

#pragma endregion
}
