#pragma once

#include "kamataEngine.h"

using namespace KamataEngine;

class Enemy
{
public:
	void Initialize(Model* model, Vector3 pos);
	void Update();
	void Draw(Camera* camera);


	Vector3 GetWorldPosition();

private:
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
};

