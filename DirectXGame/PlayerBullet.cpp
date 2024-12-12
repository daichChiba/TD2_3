#include "PlayerBullet.h"
#include <cassert>
using namespace MathUtility;

void PlayerBullet::Initialize(Model* BulletModel, Camera* camera, Vector3 pos) {
	assert(BulletModel);
	model_ = BulletModel;
	camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void PlayerBullet::Update() {
}

void PlayerBullet::Draw() {
}
