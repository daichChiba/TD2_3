#pragma once
#include "EnemyManager.h"
#include "KamataEngine.h"
#include <map>
#include <functional>

using namespace KamataEngine;

enum class EnemyMode
{
	First,
	Second,
};

class EnemyGravity : public EnemyManager {
public:
	void Update() override;

	Vector3 SetPos() {
		Vector3 pos = {worldTransform_.matWorld_.m[3][0],worldTransform_.matWorld_.m[3][1],worldTransform_.matWorld_.m[3][2]};

		return pos;
	}
	//// 半径を取得
	//float GetRadius() { return radius_; }

private:
	void DrowImgui();

	Vector3 GetPlayerPos();


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

#pragma region 小さい弾
	float miniBulletTimer_ = 0.0f;
	
	 float miniBulletOffset_ = 0.0f; 

	// 弾の間隔
	static inline const float spacing = 15.04f;

	// 弾の初期Y座標
	static inline const float initialY = -22.1f;

	// 小さい球のクールダウン
	static inline const float kMiniBulletTime_ = 1.5f;
	static inline const float kMiniBulletStartTime_ = 1.0f;
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
	static inline const float radius = 72.0f;
	static inline const int kBulletPoint = 8;
#pragma endregion
	
	
};
	//// 半径
	//float radius_ = 6.0f;
};
