#include "BadEndScene.h"

BadEndScene::BadEndScene() {}

BadEndScene::~BadEndScene() {
	delete modelFont_;
	delete fade_;
	finished_ = false;
}

void BadEndScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクション
	camera_.Initialize();

	// フェード
	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1);

	//3D文字
	modelFont_ = Model::CreateFromOBJ("badEndFont");

	//2D背景
	skydome_ = TextureManager::Load("badEndSkydome/badEndSkydome.png");
	badEndSkydome_ = Sprite::Create(skydome_, {0, 0});
	
	worldTransformFont_.Initialize();
	worldTransform_.Initialize();

	worldTransformFont_.translation_.y = 10;
	worldTransformFont_.scale_ = {1, 1, 1};

}

void BadEndScene::Update() {
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

	// 行列を更新
	worldTransformFont_.UpdateMatrix();

	// フェード
	fade_->Update();
}

void BadEndScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	
	//modelFont_->Draw(worldTransformFont_, camera_);

	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	// ここに3Dオブジェクトの描画処理を追加できる
	badEndSkydome_->Draw();

	// 3Dオブジェクト描画処理後
	Model::PostDraw();

	// フェード
	fade_->Draw(commandList);
}
