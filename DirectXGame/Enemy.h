#pragma once

#include "kamataEngine.h"

using namespace KamataEngine;

class Enemy
{
public:
	void Initialize(Model* model, Vector3 pos);
	void Update();
	void Draw(Camera* camera);
private:
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
};

