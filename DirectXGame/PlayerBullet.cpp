#include "PlayerBullet.h"
#include <cassert>
using namespace MathUtility;

void PlayerBullet::Initialize(Model* model, Vector3 pos) {
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void PlayerBullet::Update() {
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(Camera* camera) {
	model_->Draw(worldTransform_, *camera);
}

