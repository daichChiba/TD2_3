#include "Player.h"
#include<cassert>
using namespace MathUtility;
void Player::Initialize(Model* model, const Vector3 position) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = {0.0f, 0.5f, 0.0f};
}

void Player::Update() {

	ImGui::Begin("player");
	ImGui::SliderFloat3("pos", &worldTransform_.translation_.x, -10.0f, 10.0f);
	ImGui::End();

	Move();

	worldTransform_.UpdateMatrix();
}

void Player::Draw(Camera* camera) {
	model_->Draw(worldTransform_, *camera);
}

void Player::Move() {
	Vector3 velocity = {0.0f, 0.0f, 0.0f};
	#pragma region 移動タイプWASD
	if (Input::GetInstance()->PushKey(DIK_D)) {
		velocity.x = 0.1f;
	} else if (Input::GetInstance()->PushKey(DIK_A)) {
		velocity.x = -0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_W)) {
		velocity.y = 0.1f;
	} else if (Input::GetInstance()->PushKey(DIK_S)) {
		velocity.y = -0.1f;
	}
	#pragma endregion 



	worldTransform_.translation_ += velocity;
}
