#pragma once
#include "KamataEngine.h"
#include "EnemyActor.h"

using namespace KamataEngine;



class EnamyBlackHole : public EnemyActor {
public:
	void Update() override;

private:
	void DrawImgui();

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
	
	static inline const float repelSpeed = 0.05f; // 反発速度のスケール

	static inline const float bigBulletSpace = 15.0f;
#pragma endregion
};