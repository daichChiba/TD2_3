#pragma once

#include <KamataEngine.h>
#include <vector>

#include "../Enemy.h"

using namespace KamataEngine;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// カメラ
	/// </summary>
	Camera* camera_ = nullptr;
	static inline const Vector3 panoramaCameraPos = {0.0f, 20.0f, 0.0f};
	static inline const Vector3 panoramaCameraRot = {1.57f, 0.0f, 0.0f};

	/// <summary>
	/// player
	/// </summary>
	//Player* player_ = nullptr;

	/// <summary>
	/// プレイヤーモデル
	/// </summary>
	Model* playerModel_ = nullptr;
	
	/// <summary>
	/// 敵
	/// </summary>
	Enemy* enemy_ = nullptr;

	/// <summary>
	/// 敵モデル
	/// </summary>
	Model* enemyModel_ = nullptr;
	
};
