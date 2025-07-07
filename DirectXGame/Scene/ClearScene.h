#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include "../etc/Fade.h"
#include <vector>

class ClearScene {
public:
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};

	ClearScene();
	~ClearScene();

	/// <summary>
	/// 初期化
	/// <summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// <summary>
	void Update();

	/// <summary>
	/// 描画
	/// <summary>
	void Draw();

	bool IsFinished() const { return finished_; }

private:
	// 終了フラグ
	bool finished_ = false;
	Model* modelFont_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;
	XINPUT_STATE xinput_;
	XINPUT_STATE preXinput_;
	// ビュープロジェクション
	Camera camera_;

	WorldTransform worldTransformFont_;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// 画面フェード
	Fade* fade_ = nullptr;
	// 現在のフェーズ
	Phase phase_ = Phase::kFadeIn;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	Sprite* sprite;
};
