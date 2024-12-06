#pragma once

#include "kamataEngine.h"

using namespace KamataEngine;

class EnemyManager
{
public:
	void Initialize(Model* model, Model* bulletModel, Vector3 pos);
	virtual void Update();
	void Draw(Camera* camera);

protected:

	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	WorldTransform worldTransform_;

	static inline const float flameTime = 1.0f/ 60.0f;
	bool isStart_ = false;
};