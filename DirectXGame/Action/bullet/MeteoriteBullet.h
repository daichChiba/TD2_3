#pragma once
#include "EnemyBullet.h"
	/// どういった動きをしたいか
	/// 一定速度で縦横に動くようにしたい
	/// targetpos=終着点
	/// initializeでstartPosをtransform.translation_にする
	/// <必要なもの>
	/// privete
	/// startPos
class MeteoriteBullet : public EnemyBullet {
public:
	void Update()override;
	void SetTagetPos(Vector3 pos) override;

private:
	Vector3 startPos;
	Vector3 targetPos;
	void DrawImgui() ;

	int timer;
	int kTimer=60;

	
};
