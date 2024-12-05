#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class Player {
public:
	void Initialize(Model* model, const Vector3 position);

	void Update();

	void Draw(Camera* camera);

private:
	Model* model_ = nullptr;
	
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
};
