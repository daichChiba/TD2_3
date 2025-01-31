#include "RevolutionBulletSecond.h"

using namespace MathUtility;
void RevolutionBulletSecond::GetPlayerPos(Vector3 pos) {
	targetPos = pos;
}

void RevolutionBulletSecond::Update() {
	if (!isStart_) {
		speed = kSpeed;
		direction *= -1.0f;
		speed = 0.0f;
		delay = kdelay;

		color->SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.8f));
		isStart_ = true;
	}

	if (delay <= 0.0f) {
		color->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
