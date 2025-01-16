#pragma once

#include <KamataEngine.h>
#include <vector>
using namespace KamataEngine;

#include "../Enemy.h"
#include "../EnemyManager.h"
#include "../EnemyBullet.h"
using namespace KamataEngine;
#include "../Player.h"

//enum class Character {
//	wizard,
//	fencer,
//	dancer,
//};

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

	/// <summary>
	/// 敵のモードの読み取り(enemy内で使う)
	/// </summary>
	void AddEnemy(std::shared_ptr<EnemyManager> enemy) { enemies_.push_back(enemy); }
	
	/// <summary>
	/// 敵の弾の読み取り(enemy内で使う)
	/// </summary>
	void AddEnemyBullet(std::shared_ptr<EnemyBullet> enemyBullet) { enemiesBullet_.push_back(enemyBullet); }

private: // メンバ変数

	/// <summary>
	/// 敵のアップデート関数
	/// </summary>
	void enemyUpdate();

	/// <summary>
	/// 敵の描画関数
	/// </summary>
	void enemyDrow();

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
	Player* player_ = nullptr;

	/// <summary>
	/// プレイヤーモデル
	/// </summary>
	Model* playerModel_ = nullptr;
	
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

	/// <summary>
	/// 自機の弾(GameSceneではUpdateとDrowのみ行う)
	/// </summary>
	std::list<std::shared_ptr<EnemyBullet>> playerBullets_;
	
	//Model* playerBulletModel_ = nullptr;
	
};
