#include "PlayerManager.h"

#include "Scene/GameScene.h"
#include "../ActorManager.h"

#include "PlayerFactory.h"
#include "PlayerWizard.h"

void PlayerManager::Initialize(Model* playerModel, Model* bulletModel, Model* beamModel, const Vector3 pos, GameScene* gameScene, ActorManager* actor)
{
	model_ = playerModel;
	bulletModel_ = bulletModel;
	beamModel_ = beamModel;

	position_ = pos;

	gameScene_ = gameScene;
	actorManager = actor;

	playerHat_ = Model::CreateFromOBJ("playerHat", true);
	playerHead_ = Model::CreateFromOBJ("playerHead", true);
	playerLeftArm_ = Model::CreateFromOBJ("playerLeftArm", true);
	playerLeftLeg_ = Model::CreateFromOBJ("playerLeftLeg", true);
	playerRightArm_ = Model::CreateFromOBJ("playerRightArm", true);
	playerRightLeg_ = Model::CreateFromOBJ("playerRightLeg", true);

	CreateWizard();
}

void PlayerManager::Update()
{
	player_->Update();
	player_->HPposUpdate();
}

void PlayerManager::Draw(Camera* camera)
{
	player_->Draw(camera);
	DrawBody(camera);
}

void PlayerManager::DrawBody(Camera* camera) {
	playerHat_->Draw(player_->GetWorldTransform(), *camera);
	playerHead_->Draw(player_->GetWorldTransform(), *camera);
	playerLeftArm_->Draw(player_->GetWorldTransform(), *camera);
	playerLeftLeg_->Draw(player_->GetWorldTransform(), *camera);
	playerRightArm_->Draw(player_->GetWorldTransform(), *camera);
	playerRightLeg_->Draw(player_->GetWorldTransform(), *camera);
}

void PlayerManager::CreateWizard()
{
	player_ = factory_->CreateWizard();

	player_->Initialize(model_, bulletModel_, beamModel_, position_, gameScene_, actorManager);
}
