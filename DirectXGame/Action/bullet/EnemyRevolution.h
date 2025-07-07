#pragma once
#include "KamataEngine.h"
#include "../enemy/EnemyActor.h"

using namespace KamataEngine;



class EnemyRevolution : public EnemyActor {
public:
	void Update() override;

private:
	void DrawImgui()override;

	void modeFirst() override;
	void modeSecond() override;

	Vector3 GetPlayerPos();
private:
	static inline const int kMaxHp = 100;

	float miniBulletTimer_;

#pragma region miniBullet
	static inline const float radius = 5.0f;
	static inline const int kBulletPoint = 24;
	static inline const int kBulletcount = 2;

	static inline const int kMaxHP = 100;
	static inline const int kChangeModeHP = 50;

	bool isStartMode = false;

	bool isSecondStart_ = false;
	
	static inline const float repelSpeed = 0.05f; // 反発速度のスケール

	static inline const float bigBulletSpace = 15.0f;

#pragma endregion

	const float rotateSpeed_[4] = {
		MathUtility::PI * 2.0f / (60.0f * 6.0f),
		MathUtility::PI * 2.0f / (60.0f * 4.0f),
		MathUtility::PI * 2.0f / (60.0f * 3.0f),
		MathUtility::PI * 2.0f / (60.0f * 2.0f)
	};
};