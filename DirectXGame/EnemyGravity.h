#pragma once
#include "KamataEngine.h"
#include "EnemyActor.h"
#include <map>
#include <functional>

using namespace KamataEngine;

enum class EnemyMode
{
	First,
	Second,
};

class EnemyGravity : public EnemyActor {
public:
	void Update() override;
private:
	void DrowImgui();

	Vector3 GetPlayerPos();

	void LowerPlayer();

	int HP = 100;

	static inline const int kMaxHP = 100;
	static inline const int kChangeModeHP = 50;

	bool isStartMode = false;

	EnemyMode enemyMode;

	// 画面の右端と左端のX座標
	static inline const float rightEdgeX = 35.0f;
	static inline const float leftEdgeX = -35.0f;

	std::map<EnemyMode, std::function<void()>> modeUpdate{
	    {EnemyMode::First, [this]() { modeFirst(); }},
	    {EnemyMode::Second, [this]() { modeSecond(); }},
	};
	
	void modeFirst();
	void PlayerFollBigBullet();

	void modeSecond();
	void RepelPlayer();

#pragma region 小さい弾
	float miniBulletTimer_ = 0.0f;
	int miniBulletCount = 0;
	
	// 弾の間隔
	static inline const float spacing =7.0f;

	// 弾の初期Y座標
	static inline const float initialY = -22.1f;

	// 小さい球のクールダウン
	static inline const float kMiniBulletTime_ = 2.0f;
	static inline const float kMiniBulletStartTime_ = 1.0f;
	static inline const float kMiniBulletIntervalTime_ = 0.3f;
	static inline const int kMiniBulletMaxConunt_ = 3;
#pragma endregion

#pragma region 大きい弾
	float bigBulletTimer_ = 0;

	float kBigBulletTime_ = 2.0f;

	// 弾の間隔
	static inline const float kBigBulletSpacing = 18.5f;

	static inline const float kBigBulletScale = 3.0f;

	// 小さい球のクールダウン
	static inline const float kFirstModeBigBulletTime = 2.0f;
	static inline const float kSecondModeBigBulletTime = 1.5f;
	static inline const float kBigBulletStartTime_ = 1.5f;
#pragma endregion

#pragma region 
	static inline const float playerFollSpeed = -0.01f;
#pragma endregion

#pragma region 
	static inline const float radius = 5.0f;
	static inline const int kBulletPoint = 24;
	
	static inline const float repelSpeed = 0.05f; // 反発速度のスケール

	static inline const float bigBulletSpace = 15.0f;
#pragma endregion
	
	
};