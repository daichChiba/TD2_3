#pragma once

#include <KamataEngine.h>
using namespace KamataEngine;

// #include "../Enemy.h"
// #include "../EnemyFactoy.h"
// #include "../EnemyManager.h"
#include "../Action/bullet/EnemyBullet.h"
#include "../etc/Skydome.h"
//////#include "../Player.h"
////#include "../PlayerActor.h"
////#include "../PlayerWizard.h"
// #include "../PlayerManager.h"
// #include "../PlayerActor.h"
// #include "../PlayerWizard.h"

// enum class Character {
//	wizard,
//	fencer,
//	dancer,
// };

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

	uint32_t SetPlayerHPResources() { return PlayerHPResorces; }
	uint32_t SetPlayerHPBarResources() { return PlayerHpHeafResorces; }
	uint32_t SetEnemyHPResources() { return EnemyHpResorces; }
	uint32_t SetEnemyHPBarResources() { return EnemyHpBarResorces; }

	bool IsCleard(){ return isCleard;};

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
	static inline const Vector3 normalCameraPos_ = {0.0f, 0.0f, -20.0f};

	bool isFinished = false;
	bool isCleard = false;

	/// <summary>
	/// player
	/// </summary>
	// Player* player_ = nullptr;
	// std::unique_ptr<PlayerActor> player_;
	// PlayerManager* playerManager;
	ActorManager* actorManager;
	/// <summary>
	/// playerBullet
	/// </summary>

	// EnemyManager* enemyManger = nullptr;

	int testBullet = 0;

	/// <summary>
	/// 敵の弾(GameSceneではUpdateとDrowのみ行う)
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
	
	Model* zoldorkModel_ = nullptr;

	Model* enemyBulletModel_ = nullptr;
	
	//Character character_;

	Model* playerBulletModel_ = nullptr;

	// Character character_;

	Model* playerBody_ = nullptr;
	Skydome* skydome_ = nullptr;
	// SkyDomeのモデル
	Model* skydomeModel_ = nullptr;

	uint32_t PlayerHPResorces, EnemyHpResorces, PlayerHpHeafResorces, EnemyHpBarResorces;

	uint32_t soundHundle = 0;
	uint32_t voiceHundle = 0;

	Vector3 playerPos;
};
