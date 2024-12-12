#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">モデルの座標</param>
	void Initialize(Model* model, const Vector3 position);

	/// <summary>
	/// アップデート
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(Camera* camera);

private:

	Model* model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	XINPUT_STATE xinput_;
	XINPUT_STATE preXinput_;

private://メンバ関数
	/// <summary>
	/// playerの動き
	/// </summary>
	void Move();

};
