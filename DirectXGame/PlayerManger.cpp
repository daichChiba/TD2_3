#include "PlayerManger.h"

void PlayerManager::Initialize(Model* model, Model* bulletModel, Model* zoldrakModel, const Vector3 position, GameScene* gameScene)
{
	#ifdef _DEBUG 
	assert(model); 
	assert(bulletModel); 
	assert(zoldrakModel); 
#endif
	model_ = model;
	bulletModel_ = bulletModel;
	zoldrakModel_ = zoldrakModel;

	// camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	// worldTransform_.rotation_ = {0.0f, 0.5f, 0.0f};

	gameScene_ = gameScene;

	playerFactory = new PlayerFactory;
}


void PlayerManager::Update()
{
	player_->Update();
}

void PlayerManager::Draw(Camera* camera)
{
	player_->Draw(camera);
}

void PlayerManager::CreatePlayerWizard()
{
	player_ = playerFactory->CraeteWizard();
}
