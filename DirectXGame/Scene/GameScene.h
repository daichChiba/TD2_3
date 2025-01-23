#pragma once

#include <KamataEngine.h>
#include "../Fade.h"
#include <vector>
using namespace KamataEngine;

#include "../Enemy.h"
#include "../EnemyManager.h"
#include "../EnemyBullet.h"
using namespace KamataEngine;
#include "../Player.h"
#include "../Skydome.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};

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

	/// <summary>
	/// 敵のモードの読み取り(enemy内で使う)
	/// </summary>
	void AddEnemy(std::shared_ptr<EnemyManager> enemy) { enemies_.push_back(enemy); }
	
	/// <summary>
	/// 敵の弾の読み取り(enemy内で使う)
	/// </summary>
	void AddEnemyBullet(std::shared_ptr<EnemyBullet> enemyBullet) { enemiesBullet_.push_back(enemyBullet); }

	// デスフラグのgetter
	bool IsFinished() const { return finished_; } // 後で消す

private: // メンバ変数

	// 終了フラグ
	bool finished_ = false; //後で消す

	/// <summary>
	/// 敵のアップデート関数
	/// </summary>
	void enemyUpdate();

	/// <summary>
	/// 敵の描画関数
	/// </summary>
	void enemyDrow();
	void playerInitialize();
	void playerUpdate();
	void playerDraw();

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// カメラ
	/// </summary>
	Camera* camera_ = nullptr;
	static inline const Vector3 normalCameraPos_ = { 0.0f, 0.0f, -20.0f};

	/// <summary>
	/// player
	/// </summary>
	Player* playerModelBody_ = nullptr;       //体
	Player* playerModelHat_ = nullptr;        //帽子
	Player* playerModelHead_ = nullptr;       //頭
	Player* playerModelRightArm_ = nullptr;   //右腕
	Player* playerModelLeftArm_ = nullptr;    //左腕
	Player* playerModelRightLeg_ = nullptr;   //右脚
	Player* playerModelLeftLeg_ = nullptr;    //左脚
	Player* playerModelMagic_ = nullptr;      //魔法陣

	Skydome* skydomeModel_ = nullptr;

	/// <summary>
	/// プレイヤーモデル
	/// </summary>
	Model* playerBody_ = nullptr;
	Model* playerHat_ = nullptr;
	Model* playerHead_ = nullptr;
	Model* playerRightArm_ = nullptr;
	Model* playerLeftArm_ = nullptr;
	Model* playerRightLeg_ = nullptr;
	Model* playerLeftLeg_ = nullptr;
	Model* playerMagic_ = nullptr;

	// SkyDomeのモデル
	Model* skydome_ = nullptr;
	
	/// <summary>
	/// 敵
	/// </summary>
	Enemy* enemy_ = nullptr;

	int testBullet = 0;

	/// <summary>
	///敵マネージャー(GameSceneではUpdateとDrowのみ行う)
	/// </summary>
	std::list<std::shared_ptr<EnemyManager>> enemies_;

	/// <summary>
	///敵の弾(GameSceneではUpdateとDrowのみ行う)
	/// </summary>
	std::list<std::shared_ptr<EnemyBullet>> enemiesBullet_;

	/// <summary>
	/// 敵モデル
	/// </summary>
	Model* enemyModel_ = nullptr;

	// 画面フェード
	Fade* fade_ = nullptr;
	// 現在のフェーズ
	Phase phase_ = Phase::kFadeIn;
	
};
