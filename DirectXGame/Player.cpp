#include "Player.h"
#include<cassert>
void Player::Initialize(Model* model, const Vector3 position) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Player::Update() {
	worldTransform_.TransferMatrix();
}

void Player::Draw(Camera* camera) {
	model_->Draw(worldTransform_, *camera);
}
