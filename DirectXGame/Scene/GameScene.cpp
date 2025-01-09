#include "GameScene.h"
#include <cassert>

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

	//playerのモデル
	playerModel_ = new Model();
	//playerModel_->CreateFromOBJ("player", true);
	
	enemyModel_ = Model::CreateFromOBJ("cube", true);

	// player_ = new Player()
	
	playerModel_=Model::CreateFromOBJ("Player", true);
	//playerの初期化
	player_ = new Player();
	player_->Initialize(playerModel_, Vector3{0.0f});

	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel_, Vector3{0.0f}, player_);
	enemy_->SetGameScene(this); 
}

void GameScene::Update() {
	
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
		
	//敵
	enemyDrow();

	//player
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

void GameScene::enemyUpdate()
{

	enemy_->Update();
	enemy_->SetGameScene(this);
	for (std::shared_ptr<EnemyManager> enemy : enemies_)
	{
		enemy->Update();
		enemy->SetGameScene(this);
	}
	 testBullet = 0;
	for (std::shared_ptr<EnemyBullet> enemyBullet : enemiesBullet_)
	{
		enemyBullet->Update();
		++testBullet;
	}

	ImGui::Begin("gamescene");
	ImGui::Text("%d", testBullet);
	ImGui::End();

	enemiesBullet_.remove_if([](std::shared_ptr<EnemyBullet> a) { return a->IsDelete(); });
}

void GameScene::enemyDrow()
{
	for (std::shared_ptr<EnemyManager> enemy : enemies_)
	{
		enemy->Draw(camera_);
	}

	for (std::shared_ptr<EnemyBullet> enemyBullet : enemiesBullet_)
	{
		enemyBullet->Draw(camera_);
	}
}
