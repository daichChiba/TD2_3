#pragma once
#include "kamataEngine.h"

using namespace KamataEngine;

class Player;
enum class Bullet {
	Grabity,
	Enemy,
	Player,
	Zoldorak
};
class EnemyBullet {
public:
	void Initialize(Model* model, Vector3 pos);
	virtual void Update();
	virtual void Draw(Camera* camera);

	bool IsDelete() const { return isDelete_; }
	void SetScale(const float scale) { worldTransform_.scale_ = Vector3{scale, scale, scale}; }

	virtual void SetTagetPos(Vector3 pos) { pos = pos; }
	// virtual void SetStartPos(Vector3 pos) { pos = pos; }
	Vector3 GetWorldPosition();

	void OnCollision();
	// 半径を取得
	float GetRadius() { return worldTransform_.scale_.x * radius_; }
	virtual void GetPlayerPos(Vector3 pos) { pos = pos; }

	void SetBullet(Bullet bullet) { bullet_ = bullet; }

	Bullet GetBullet() const { return bullet_; }
	
	void SetParent(WorldTransform* parent) { worldTransform_.parent_ = parent; }

	bool GetIsHit() { return isHit_; }

protected:
	void SetVec(float* a, Vector3 b) {
		b.x = a[0];
		b.y = a[1];
		b.z = a[2];
	}

	void DrowImgui();

	Model* model_ = nullptr;
	WorldTransform worldTransform_;

	Vector3 velocity_;

	bool isDelete_ = false;

	static inline const float flameTime = 1.0f / 60.0f;
	bool isStart_ = false;

	Player* player_;

	// 半径
	float radius_ = 6.0f;

	Bullet bullet_;

	bool isHit_ = true;
};
