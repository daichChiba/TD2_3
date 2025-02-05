#pragma once

#include <KamataEngine.h>
using namespace KamataEngine;

//#include "../Enemy.h"
//#include "../EnemyFactoy.h"
//#include "../EnemyManager.h"
#include "../EnemyBullet.h"
//////#include "../Player.h"
////#include "../PlayerActor.h"
////#include "../PlayerWizard.h"
//#include "../PlayerManager.h"
//#include "../PlayerActor.h"
//#include "../PlayerWizard.h"

//enum class Character {
//	wizard,
//	fencer,
//	dancer,
//};

class ActorManager;

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
	/// 敵の弾の読み取り(enemy内で使う)
	/// </summary>
	void AddEnemyBullet(std::shared_ptr<EnemyBullet> enemyBullet) { enemiesBullet_.push_back(enemyBullet); }
	
	void AddPlayerBullet(std::shared_ptr<EnemyBullet> playerBullet) { playerBullets_.push_back(playerBullet); }

	bool IsFinished() { return isFinished;}
private: // メンバ変数

	/// <summary>
	/// すべての当たり判定
	/// </summary>
	void CheckAllCollisions();

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// カメラ
	/// </summary>
	Camera* camera_ = nullptr;
	static inline const Vector3 normalCameraPos_ = { 0.0f, 0.0f, -20.0f};

	bool isFinished;

	/// <summary>
	/// player
	/// </summary>
	//Player* player_ = nullptr;
	//std::unique_ptr<PlayerActor> player_;
	//PlayerManager* playerManager;
	ActorManager* actorManager;
	/// <summary>
	/// プレイヤーモデル
	/// </summary>
	Model* playerModel_ = nullptr;
	
	//EnemyManager* enemyManger = nullptr;

	int testBullet = 0;

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

	Model* zoldorkModel_ = nullptr;
	
	//Character character_;

	Vector3 playerPos;
};
