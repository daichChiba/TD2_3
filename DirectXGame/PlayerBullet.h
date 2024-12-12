#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
class Enemy;

class PlayerBullet {
public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="pos">座標</param>
	void Initialize(Model* model, Vector3 pos);
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(Camera* camera);


private:
	//モデル
	Model* model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

};
