#include "GameScene.h"
#include <cassert>

using namespace KamataEngine;

// インストラクタ
GameScene::GameScene() {}
// デストラクタ
GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	camera_ = new Camera();
	camera_->Initialize();
	camera_->translation_ = normalCameraPos_;

	playerModel_ = new Model();
	//playerModel_->CreateFromOBJ("player", true);
	
	enemyModel_ = Model::CreateFromOBJ("cube", true);

	// player_ = new Player()

	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel_, Vector3{0.0f});
	enemy_->SetGameScene(this); 
}

void GameScene::Update() {
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
	enemyDrow();

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
