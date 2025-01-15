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

	Vector3 GetPlayerPos();

	void SetPlayerBody
	(Model* head, Model* body, 
	Model* LeftArm, Model* RightArm, 
	Model* LeftLeg, Model* RightLeg);
private:

	Model* model_ = nullptr;

#pragma region
	Model* playerHeadModel_ = nullptr;
	Model* playerBodyModel_ = nullptr;
	Model* playerLeftArmModel_ = nullptr;
	Model* playerRightArmModel_ = nullptr;
	Model* playerLeftLegModel_ = nullptr;
	Model* playerRightLegModel_ = nullptr;

	/// <summary>
	/// playerの体のそれぞれの位置情報
	/// </summary>
	WorldTransform playerBody[5];

	void InitialezeBody();
#pragma endregion
	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	XINPUT_STATE xinput_;
	XINPUT_STATE preXinput_;

	Vector3 velocity = {0.0f, 0.0f, 0.0f};

private://メンバ関数
	/// <summary>
	/// playerの動き
	/// </summary>
	void Move();


	void Fire();

};
