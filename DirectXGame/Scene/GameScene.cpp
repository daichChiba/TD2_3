#include "GameScene.h"
#include "../ActorManager.h"
#include <cassert>
#include <corecrt_math.h>

#include "../PlayerManager.h"
#include "../PlayerActor.h"
#include "../EnemyManager.h"
#include "../EnemyActor.h"

using namespace KamataEngine;

// インストラクタ
GameScene::GameScene() {}
// デストラクタ
GameScene::~GameScene() {
	delete playerModel_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	camera_ = new Camera();
	camera_->Initialize();
	camera_->translation_ = normalCameraPos_;

	// playerのモデル
	playerModel_ = new Model();
	// playerModel_->CreateFromOBJ("player", true);

	enemyModel_ = Model::CreateFromOBJ("cube", true);

	// player_ = new Player()

	playerModel_ = Model::CreateFromOBJ("Player", true);
	//character_ = CX::wizard;
	// playerの初期化
	/*player_ = new Player();
	player_->Initialize(playerModel_, Vector3{0.0f}, character_, playerModel_, enemyModel_);
	player_->SetGameScene(this);*/

	actorManager = new ActorManager;
	actorManager->Initialize(playerModel_, playerModel_, enemyModel_, enemyModel_, enemyModel_, Vector3{0.0f, 0.0f, 0.0f}, Vector3{0.0f, 0.0f, 0.0f}, this);

	//player_ = std::make_unique< PlayerWizard>();
	//player_->Initialize(playerModel_, playerModel_, enemyModel_, Vector3( 0.0f, 0.0f, 0.0f), this);

	/*playerManager = new PlayerManager;
	playerManager->Initialize(playerModel_, playerModel_, enemyModel_, Vector3(0.0f, 0.0f, 0.0f), this);*/

	/*enemyManger = new EnemyManager();
	enemyManger->Initialize(enemyModel_, enemyModel_, Vector3{0.0f, 0.0f, 0.0f}, player_, this);*/
}

void GameScene::Update() {
	CheckAllCollisions();
	//player_->Update();
	actorManager->Update();

	for(std::shared_ptr<EnemyBullet> playerBullet : playerBullets_)
	{ playerBullet->Update(); 
		
	}
	
	for(std::shared_ptr<EnemyBullet> enemyBullet : enemiesBullet_)
	{ enemyBullet->Update(); }



	ImGui::Begin("gamescene");
	ImGui::DragFloat3("pPos", &playerPos.x);
	ImGui::End();

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
