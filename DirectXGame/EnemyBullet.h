#pragma once
#include "kamataEngine.h"

using namespace KamataEngine;

class EnemyBullet
{
public:
	void Initialize(Model* model, Vector3 pos);
	virtual void Update();
	void Draw(Camera* camera);

	bool GetIsDelete() const { return isDelete_; }
protected:	
	Model* model_ = nullptr;
	WorldTransform worldTransform_;

	bool isDelete_ = false;

	static inline const float flameTime = 1.0f/ 60.0f;
	bool isStart_ = false;
};

