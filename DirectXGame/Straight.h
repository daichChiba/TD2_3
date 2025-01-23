#pragma once
#include "EnemyBullet.h"
class Straight : public EnemyBullet {
public:
	void Update() override;
	void SetTagetPos(Vector3 pos) override { direction = pos; }

private:
	bool start = false;
	Vector3 direction;

	const float speed = 2.0f;

private:
	void DrowImgui();
};
