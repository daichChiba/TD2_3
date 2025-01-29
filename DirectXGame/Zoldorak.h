#pragma once
#include "EnemyBullet.h"
class Zoldorak : public EnemyBullet {
	void Update() override;
	void SetTagetPos(Vector3 pos) override { direction = pos; }
	void OnCollision()override;

private:
	bool start = false;
	Vector3 direction;

	const float speed = 2.0f;

	//予測時間
	int predictionTimer = 0;
	const int kPredictionTimer = 60;

	//発射時間
	int firingTimer = 0;
	const int kFiringTimer = 30;

	Vector3 pos_;
	
private:
	void DrowImgui();
};
