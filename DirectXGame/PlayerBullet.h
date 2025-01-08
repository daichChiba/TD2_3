#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
class Enemy;

class PlayerBullet {
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="BulletModel"></param>
	/// <param name="camera"></param>
	/// <param name="pos">弾の位置</param>
	void Initialize(Model* BulletModel, Camera* camera, Vector3 pos);
	/// <summary>
	/// 
	/// </summary>
	void Update();
	/// <summary>
	/// 
	/// </summary>
	void Draw();


private:
	Model* model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	Camera* camera_ = nullptr;
};
