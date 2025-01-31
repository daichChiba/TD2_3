#include "PlayerManager.h"

#include "Scene/GameScene.h"

#include "PlayerFactory.h"
#include "PlayerWizard.h"

void PlayerManager::Initialize(Model* playerModel, Model* bulletModel, Model* beamModel, const Vector3 pos, GameScene* gameScene)
{
	model_ = playerModel;
	bulletModel_ = bulletModel;
	beamModel_ = beamModel;

	position_ = pos;

	gameScene_ = gameScene;

	CreateWizard();
}

void PlayerManager::Update()
{
	player_->Update();
}

void PlayerManager::Draw(Camera* camera)
{
	player_->Draw(camera);
}

void PlayerManager::CreateWizard()
{
	player_ = factory_->CreateWizard();

	player_->Initialize(model_, bulletModel_, beamModel_, position_, gameScene_);
}
