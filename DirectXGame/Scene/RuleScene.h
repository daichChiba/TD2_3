#pragma once
#include <KamataEngine.h>
#include "../Fade.h"

using namespace KamataEngine;
#include <vector>

class RuleScene {
public:
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};

	RuleScene();

	~RuleScene();

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

	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

private:
	// 終了フラグ
	bool finished_ = false;

	Model* modelFont_ = nullptr;
	Model* modelEnemy_ = nullptr;

	// ビュープロジェクション
	Camera camera_;

	WorldTransform worldTransformFont_;
	WorldTransform worldTransformPlayer_;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	float timer_ = 0.0f;
	static inline const float kMotionTime = 1.0f;

	// 画面フェード
	Fade* fade_ = nullptr;
	// 現在のフェーズ
	Phase phase_ = Phase::kFadeIn;

	// サウドデータハンドル
	uint32_t soundDataHandle_ = 0;
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;
};
