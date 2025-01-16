#pragma once
#include "kamataEngine.h"

using namespace KamataEngine;

class Player;

class EnemyBullet {
public:
	void Initialize(Model* model, Vector3 pos);
	virtual void Update();
	void Draw(Camera* camera);

	bool IsDelete() const { return isDelete_; }
	void SetScale(const float scale) { worldTransform_.scale_ = {scale}; }

	virtual void GetTagetPos(Vector3 pos) { pos = pos; }
	Vector3 GetWorldPosition();

	void OnCollision();
	// 半径を取得
	float GetRadius() { return radius_; }

protected:
	void SetVec(float* a, Vector3 b) {
	void SetScale(const float scale);
	virtual void GetPlayerPos(Vector3 pos);
	
protected:	
	void SetVec(float* a, Vector3 b){
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

	// ���a
	float radius_ = 6.0f;
};
