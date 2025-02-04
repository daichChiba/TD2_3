#include "EnemyActor.h"

void EnemyActor::Initialize(Model* model, Model* bulletModel, Vector3 pos, GameScene* gameScene) {
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif // _DEBUG

	model_ = model;

	bulletModel_ = bulletModel;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	gameScene_ = gameScene;
}

void EnemyActor::Update()
{
	
}

void EnemyActor::Draw(Camera* camera)
{
	model_->Draw(worldTransform_, *camera); }

void EnemyActor::modeFirst()
{

}

void EnemyActor::modeSecond()
{
}
