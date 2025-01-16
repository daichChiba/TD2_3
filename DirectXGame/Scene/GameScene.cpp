#include "GameScene.h"
#include <cassert>

using namespace KamataEngine;

// インストラクタ
GameScene::GameScene() {}
// デストラクタ
GameScene::~GameScene() {

	delete playerBody_;
	delete playerHead_;
	delete playerRightArm_;
	delete playerLeftArm_;
	delete playerRightLeg_;
	delete playerLeftLeg_;
	delete playerMagic_;

	delete playerModelBody_;
	delete playerModelHead_;
	delete playerModelRightArm_;
	delete playerModelLeftArm_;
	delete playerModelRightLeg_;
	delete playerModelLeftLeg_;
	delete playerModelMagic_;
}




void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	camera_ = new Camera();
	camera_->Initialize();
	camera_->translation_ = normalCameraPos_;

	//playerのモデル
	//playerModel_ = new Model(); 
	//playerHead_ = new Model();
	//playerModel_->CreateFromOBJ("player", true);
	
	enemyModel_ = Model::CreateFromOBJ("enemy", true);

	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel_, Vector3{0.0f});
	enemy_->SetGameScene(this); 
	
#pragma region modelのやつ
	playerBody_ = Model::CreateFromOBJ("playerBody", true);
	playerHead_ = Model::CreateFromOBJ("playerHead", true);
	playerRightArm_ = Model::CreateFromOBJ("playerRightArm", true);
	playerLeftArm_ = Model::CreateFromOBJ("playerLeftArm", true);
	playerRightLeg_ = Model::CreateFromOBJ("playerRightLeg", true);
	playerLeftLeg_ = Model::CreateFromOBJ("playerLeftLeg", true);
	playerMagic_ = Model::CreateFromOBJ("mahou", true);
#pragma endregion


#pragma region playerの初期化
	playerModelBody_ = new Player();
	playerModelHead_ = new Player();
	playerModelRightArm_ = new Player();
	playerModelLeftArm_ = new Player();
	playerModelRightLeg_ = new Player();
	playerModelLeftLeg_ = new Player();
	playerModelMagic_ = new Player();
#pragma endregion


#pragma region playerのInitialize
	playerModelBody_->Initialize(playerBody_, Vector3{0.0f});
	playerModelHead_->Initialize(playerHead_, Vector3{0.0f});
	playerModelRightArm_->Initialize(playerRightArm_, Vector3{0.0f});
	playerModelLeftArm_->Initialize(playerLeftArm_, Vector3{0.0f});
	playerModelRightLeg_->Initialize(playerRightLeg_, Vector3{0.0f});
	playerModelLeftLeg_->Initialize(playerLeftLeg_, Vector3{0.0f});
	playerModelMagic_->Initialize(playerMagic_, Vector3{0.0f});
#pragma endregion
}

void GameScene::Update() {
	
#pragma region プレイヤーのアップデート
	playerModelBody_->Update();
	playerModelHead_->Update();
	playerModelRightArm_->Update();
	playerModelLeftArm_->Update();
	playerModelRightLeg_->Update();
	playerModelLeftLeg_->Update();
	playerModelMagic_->Update();
#pragma endregion

	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) { // 後で消す
		finished_ = true;
	}

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

#pragma region プレイヤー
	playerModelBody_->Draw(camera_);
	playerModelHead_->Draw(camera_);
	playerModelRightArm_->Draw(camera_);
	playerModelLeftArm_->Draw(camera_);
	playerModelRightLeg_->Draw(camera_);
	playerModelLeftLeg_->Draw(camera_);
	playerModelMagic_->Draw(camera_);
#pragma endregion

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
