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
	camera_->translation_ = panoramaCameraPos;
	//camera_->rotation_ = panoramaCameraRot;

	//playerのモデル
	playerModel_ = new Model();
	//playerModel_->CreateFromOBJ("player", true);
	
	enemyModel_ = Model::CreateFromOBJ("cube", true);

	// player_ = new Player()

	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel_, Vector3{0.0f});
	
	playerModel_=Model::CreateFromOBJ("Player", true);
	//playerの初期化
	player_ = new Player();
	player_->Initialize(playerModel_, Vector3{0.0f});
}

void GameScene::Update() {
	enemy_->Update();
//
//#ifdef _DEBUG
//	float CameraPos[] = {camera_->translation_.x, camera_->translation_.y, camera_->translation_.z};
//	float CameraRot[] = {camera_->rotation_.x, camera_->rotation_.y, camera_->rotation_.z};
//
//	ImGui::Begin("camera");
//	ImGui::DragFloat3("CameraPos", CameraPos, 0.01f);
//	ImGui::DragFloat3("CameraRot", CameraRot, 0.01f);
//	ImGui::End();
//
//	camera_->translation_.x = CameraPos[0];
//	camera_->translation_.y = CameraPos[1];
//	camera_->translation_.z = CameraPos[2];
//	
//	camera_->rotation_.x = CameraRot[0];
//	camera_->rotation_.y = CameraRot[1];
//	camera_->rotation_.z = CameraRot[2];
//#endif // DEBUG

	camera_->UpdateMatrix();
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

	//player
	player_->Draw(camera_);


	enemy_->Draw(camera_);

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
