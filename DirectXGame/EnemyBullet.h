#pragma once
#include "kamataEngine.h"

using namespace KamataEngine;

class ActorManager;

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


	void SetActor(ActorManager* actor);

	virtual void OnCollision();

	/*Getter*/
	// 半径を取得
	float GetRadius() { return worldTransform_.scale_.x * radius_; }
	Vector3 GetWorldPosition();

	bool GetIsHit() { return isHit_; }
	Bullet GetBullet() const { return bullet_; }


	/*Setter*/
	virtual void SetTagetPos(Vector3 pos) { pos = pos; }
	void SetScale(const float scale) { worldTransform_.scale_ = Vector3{scale, scale, scale}; }
	void SetBullet(Bullet bullet) { bullet_ = bullet; }
	
	virtual void SetPlayerPos(Vector3 pos) { pos = pos; }
	void SetParent(WorldTransform* parent) { worldTransform_.parent_ = parent; }

	void SetDraw(bool isDraw) { isDraw_ = isDraw; }
	void SetSpeed(float speed) { speed_ = speed; }

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

	ActorManager* actorManager;

	// 半径
	float radius_ = 6.0f;

	Bullet bullet_;

	bool isHit_ = true;

	ObjectColor* color = nullptr;

	bool isDraw_ = true;

	float speed_ = 0.0f;
};
