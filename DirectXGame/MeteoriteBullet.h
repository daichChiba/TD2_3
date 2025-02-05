#pragma once
#include "EnemyBullet.h"
class MeteoriteBullet : public EnemyBullet {
public:
	void SetPlayerPos(Vector3 pos) override;
	void Update() override;

private:
	Vector3 targetPos;
	Vector3 goalPos;
	Vector3 direction;

	void DrawImgui();

	float delay;

	float speed;

	static inline const float kSpeed = 0.01f;
	static inline const float kdelay = 1.0f;
};
