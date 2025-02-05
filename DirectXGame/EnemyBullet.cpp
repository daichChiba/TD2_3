#include "EnemyBullet.h"

#include "ActorManager.h"

void EnemyBullet::Initialize(Model* model, Vector3 pos) {
#ifdef _DEBUG
	assert(model);
#endif // _DEBUG

	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	color = new ObjectColor;
	color->Initialize();
	color->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
}

void EnemyBullet::Update() { worldTransform_.UpdateMatrix(); }

void EnemyBullet::Draw(Camera* camera) {
	if (isDraw_) {
		model_->Draw(worldTransform_, *camera, color);
	}
}

Vector3 EnemyBullet::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void EnemyBullet::SetActor(ActorManager* actor) { actorManager = actor; }

void EnemyBullet::OnCollision() { isDelete_ = true; }

// void EnemyBullet::SetScale(const float scale)
//{
//	worldTransform_.scale_.x = {scale};
//	worldTransform_.scale_.y = {scale};
//	worldTransform_.scale_.z = {scale};
// }
//
// void EnemyBullet::GetPlayerPos(Vector3 pos)
//{
//	pos = pos;
// }
