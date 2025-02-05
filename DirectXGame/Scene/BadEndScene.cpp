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


	textureHandle_ = TextureManager::Load("badEndSkydome.png");
	sprite = Sprite::Create(textureHandle_, {0.0f, 0.0f});
	/*modelFont_ = Model::CreateFromOBJ("badEndFont");

	worldTransformFont_.Initialize();
	worldTransform_.Initialize();

	worldTransformFont_.translation_.y = 10;
	worldTransformFont_.scale_ = {1, 1, 1};*/
}

void BadEndScene::Update() {

	// SPACEキーを押すとフェードアウトを開始
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		if (phase_ != Phase::kFadeOut) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1);
		}
	}

	if (fade_ != nullptr && fade_->IsFadeOutFinished() == true) {
		// 次のシーンに進む処理
		// フェードアウトが終了したらゲームシーンに行く
		// 音声停止
		// audio_->StopWave(voiceHandle_);
		finished_ = true;
	}

	// 行列を更新
	//worldTransformFont_.UpdateMatrix();

	if (fade_ == nullptr) {
		return;
	}
	fade_->Update();
}

void BadEndScene::Draw() {
    if (dxCommon_ == nullptr) {
        dxCommon_ = DirectXCommon::GetInstance();
    }

    ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
    if (commandList == nullptr) {
        // エラーログを出力するか、デフォルトの処理を行う
        return;
    }
	
	// 3Dオブジェクト描画前処理
	Sprite::PreDraw(commandList);

	sprite->Draw();

	// 3Dオブジェクト描画処理後
	Sprite::PostDraw();

	// フェード
	fade_->Draw(commandList);
}
