#pragma once
#include "EnemyManager.h"
#include "KamataEngine.h"
#include <map>
#include <functional>

using namespace KamataEngine;

class Player;

enum class EnemyMode
{
	First,
	Second,
};

class EnemyGravity : public EnemyManager {
public:
	void Update() override;

	
private:
	void DrowImgui();

	Vector3 GetPlayerPos();


	int HP = 100;

	static inline const int kMaxHP = 100;
	static inline const int kChangeModeHP = 50;

	bool isStartMode = false;

	EnemyMode enemyMode;

	// 画面の右端と左端のX座標
	static inline const float rightEdgeX = 35.1f;
	static inline const float leftEdgeX = -35.1f;

	std::map<EnemyMode, std::function<void()>> modeUpdate{
	    {EnemyMode::First, [this]() { modeFirst(); }},
	    {EnemyMode::Second, [this]() { modeSecond(); }},
	};

	void modeFirst();
	void modeSecond();

#pragma region 小さい弾
	float miniBulletTimer_ = 0.0f;
	
	 float miniBulletOffset_ = 0.0f; 

	// 弾の間隔
	static inline const float spacing = 12.0f;

	// 弾の初期Y座標
	static inline const float initialY = -22.1f;

	// 小さい球のクールダウン
	static inline const float kMiniBulletTime_ = 1.5f;
	static inline const float kMiniBulletStartTime_ = 1.0f;
#pragma endregion

#pragma region 大きい弾
	float bigBulletTimer_ = 0;
	bool bullet

	static inline const float kBigBulletScale = 3.0f;

	// 小さい球のクールダウン
	static inline const float kBigBulletTime_ = 2.0f;
	static inline const float kBigBulletStartTime_ = 1.5f;
#pragma endregion
};
