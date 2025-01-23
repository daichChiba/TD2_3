#include "GameScene.h"
#include <cassert>

using namespace KamataEngine;

// インストラクタ
GameScene::GameScene() {}
// デストラクタ
GameScene::~GameScene() {
#pragma region delete
	delete skydomeModel_;
	delete fade_;

	delete playerBody_;
	delete playerHat_;
	delete playerHead_;
	delete playerRightArm_;
	delete playerLeftArm_;
	delete playerRightLeg_;
	delete playerLeftLeg_;
	delete playerMagic_;

	delete playerModelBody_;
	delete playerModelHat_;
	delete playerModelHead_;
	delete playerModelRightArm_;
	delete playerModelLeftArm_;
	delete playerModelRightLeg_;
	delete playerModelLeftLeg_;
	delete playerModelMagic_;
#pragma endregion
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	camera_ = new Camera();
	camera_->Initialize();
	camera_->translation_ = normalCameraPos_;

	// フェード
	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1);

	//playerのモデル
	//playerModel_ = new Model(); 
	//playerHead_ = new Model();
	//playerModel_->CreateFromOBJ("player", true);

	// skydomeの生成
	skydomeModel_ = new Skydome();
	skydome_ = Model::CreateFromOBJ("Skydome", true);
	skydomeModel_->Initialize(skydome_, camera_);
	
	// enemy
	enemyModel_ = Model::CreateFromOBJ("enemy", true);
	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel_, Vector3{0.0f});
	enemy_->SetGameScene(this); 
	
#pragma region modelのやつ
	playerBody_ = Model::CreateFromOBJ("playerBody", true);
	playerHat_ = Model::CreateFromOBJ("playerHat", true);
	playerHead_ = Model::CreateFromOBJ("playerHead", true);
	playerRightArm_ = Model::CreateFromOBJ("playerRightArm", true);
	playerLeftArm_ = Model::CreateFromOBJ("playerLeftArm", true);
	playerRightLeg_ = Model::CreateFromOBJ("playerRightLeg", true);
	playerLeftLeg_ = Model::CreateFromOBJ("playerLeftLeg", true);
	playerMagic_ = Model::CreateFromOBJ("mahou", true);
#pragma endregion


#pragma region playerの初期化
	playerModelBody_ = new Player();
	playerModelHat_ = new Player();
	playerModelHead_ = new Player();
	playerModelRightArm_ = new Player();
	playerModelLeftArm_ = new Player();
	playerModelRightLeg_ = new Player();
	playerModelLeftLeg_ = new Player();
	playerModelMagic_ = new Player();
#pragma endregion


#pragma region playerのInitialize
	playerInitialize();
#pragma endregion
}

void GameScene::Update() {
	
#pragma region プレイヤーのアップデート
	playerModelBody_->Update();
#pragma endregion

	playerUpdate();

	// SPACEキーを押すとフェードアウトを開始
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		if (phase_ != Phase::kFadeOut) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1);
		}
		// finished_ = true;
	}

	// フェードアウトが終了したらゲームシーンに行く
	if (fade_->IsFadeOutFinished() == true) {
		// 音声停止
		// audio_->StopWave(voiceHandle_);
		finished_ = true;
	} 

#pragma region 敵のアップデート
	enemyUpdate();
#pragma endregion 

	// フェード
	fade_->Update();
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
	
	
#pragma region 敵	
	enemyDrow();
#pragma endregion



#pragma region プレイヤー
	playerDraw();
#pragma endregion



#pragma region スカイドーム
	skydomeModel_->Draw();
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

	// フェード
	fade_->Draw(commandList);

#pragma endregion
}

void GameScene::enemyUpdate()
{
#pragma region enemyのUpdate
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
#pragma endregion
}

void GameScene::enemyDrow()
{
#pragma region enemyの描画
	for (std::shared_ptr<EnemyManager> enemy : enemies_)
	{
		enemy->Draw(camera_);
	}

	for (std::shared_ptr<EnemyBullet> enemyBullet : enemiesBullet_)
	{
		enemyBullet->Draw(camera_);
	}
#pragma endregion
}

void GameScene::playerInitialize() {
#pragma region playerのInitialize
	playerModelBody_->Initialize(playerBody_, Vector3{0.0f});
	playerModelHat_->Initialize(playerHat_, Vector3{0.0f});
	playerModelHead_->Initialize(playerHead_, Vector3{0.0f});
	playerModelRightArm_->Initialize(playerRightArm_, Vector3{0.0f});
	playerModelLeftArm_->Initialize(playerLeftArm_, Vector3{0.0f});
	playerModelRightLeg_->Initialize(playerRightLeg_, Vector3{0.0f});
	playerModelLeftLeg_->Initialize(playerLeftLeg_, Vector3{0.0f});
	//playerModelMagic_->Initialize(playerMagic_, Vector3{0.0f});
#pragma endregion
}

void GameScene::playerUpdate() {
#pragma region playerのUpdate
	playerModelHat_->ModelUpdate();
	playerModelHead_->ModelUpdate();
	playerModelRightArm_->ModelUpdate();
	playerModelLeftArm_->ModelUpdate();
	playerModelRightLeg_->ModelUpdate();
	playerModelLeftLeg_->ModelUpdate();
	// playerModelMagic_->Update();
#pragma endregion
}

void GameScene::playerDraw() {
#pragma region playerの描画
	playerModelBody_->Draw(camera_);
	playerModelHat_->Draw(camera_);
	playerModelHead_->Draw(camera_);
	playerModelRightArm_->Draw(camera_);
	playerModelLeftArm_->Draw(camera_);
	playerModelRightLeg_->Draw(camera_);
	playerModelLeftLeg_->Draw(camera_);
	// playerModelMagic_->Draw(camera_);
#pragma endregion
}
