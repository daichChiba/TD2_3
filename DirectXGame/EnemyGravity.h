#pragma once
#include "EnemyManager.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class EnemyGravity : public EnemyManager
{
public:
	void Update() override;

private:
	void DrowImgui();
	float miniBulletTimer_ = 0.0f;

	// 画面の右端と左端のX座標
	static inline const float rightEdgeX = 35.1f;
	static inline const float leftEdgeX = -35.1f;

	// 弾の間隔
	static inline const float spacing = 7.0f;

	// 弾の初期Y座標
	static inline const float initialY = -22.1f;

	//小さい球のクールダウン
	static inline const float kMiniBulletTime_ = 0.8f;
	static inline const float kMiniBulletStartTime_ = 1.5f;

	
};

