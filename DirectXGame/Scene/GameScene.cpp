#include "GameScene.h"
#include <cassert>
#include <corecrt_math.h>

using namespace KamataEngine;

// インストラクタ
GameScene::GameScene() {}
// デストラクタ
GameScene::~GameScene() {
	delete playerModel_;

	delete player_;
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
	character_ = Character::wizard;
	// playerの初期化
	player_ = new Player();
	player_->Initialize(playerModel_, Vector3{0.0f}, character_, playerModel_,enemyModel_);
	player_->SetGameScene(this);

	enemyManger = new EnemyManager();
	enemyManger->Initialize(enemyModel_, enemyModel_, Vector3{0.0f, 0.0f, 0.0f}, player_, this);

	
}

void GameScene::Update() {
	CheckAllCollisions();
	player_->Update();

#pragma region 敵のアップデート
	enemyUpdate();
#pragma endregion
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

	// 敵
	enemyDrow();

	// player
	player_->Draw(camera_);

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

void GameScene::enemyUpdate() {

	enemyManger->Update();
	testBullet = 0;
	for (std::shared_ptr<EnemyBullet> enemyBullet : enemiesBullet_) {
		enemyBullet->Update();
		++testBullet;
	}

	for (std::shared_ptr<EnemyBullet> playerBullet : playerBullets_) {
		playerBullet->Update();
	}

	enemiesBullet_.remove_if([](std::shared_ptr<EnemyBullet> a) { 
		return a->IsDelete(); });
	playerBullets_.remove_if([](std::shared_ptr<EnemyBullet> a) { 
		return a->IsDelete(); });
}

void GameScene::enemyDrow() {
		enemyManger->Draw(camera_);

	for (std::shared_ptr<EnemyBullet> enemyBullet : enemiesBullet_) {
		enemyBullet->Draw(camera_);
	}

	for (std::shared_ptr<EnemyBullet> playerBullet : playerBullets_) {
		playerBullet->Draw(camera_);
	}
}

void GameScene::CheckAllCollisions() {
	// 判定対象AとBの座標
	Vector3 posA, posB;

#pragma region 敵の弾とプレイヤーの当たり判定
	bool is = false;
	posA = player_->GetWorldPosition();
	for (std::shared_ptr<EnemyBullet> enemyBullet : enemiesBullet_) {
		posB = enemyBullet->GetWorldPosition();
		Vector3 A2B = MathUtility::Sphere(posA, posB);
		float len = MathUtility::Length(A2B);
		float radius = enemyBullet->GetRadius() + player_->GetRadius();
		if (len <= radius) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 自弾の衝突時コールバックを呼び出す
			enemyBullet->OnCollision();
		}




		if (enemyBullet->GetBullet() == Bullet::Zoldorak) {
			if (!is) {

			}
		}
	}

#pragma endregion

#pragma region 自機の弾と敵の当たり判定
	
#pragma endregion

#pragma region 自機の弾と敵の弾の当たり判定

#pragma endregion
}
