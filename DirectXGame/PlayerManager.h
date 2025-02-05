#pragma once

#include "KamataEngine.h"
//#include "Scene/GameScene.h"

#include "PlayerActor.h"

using namespace KamataEngine;

class GameScene;
class ActorManager;
class PlayerFactory;

class PlayerManager
{
public:
	void Initialize(Model* playerModel, Model* bulletModel, Model* beamModel, const Vector3 pos, GameScene* gameScene, ActorManager* actor);
	void Update();
	void Draw(Camera* camera);
	void DrawBody(Camera* camera);
	void CreateWizard();

	PlayerActor* GetActor() const { return player_.get(); }
private:
	Model* model_;
	Model* bulletModel_;
	Model* beamModel_;

	std::unique_ptr<PlayerActor> player_;

	GameScene* gameScene_;
	PlayerFactory* factory_;
	ActorManager* actorManager;

	Model* playerHat_ = nullptr;
	Model* playerHead_ = nullptr;
	Model* playerLeftArm_ = nullptr;
	Model* playerLeftLeg_ = nullptr;
	Model* playerRightArm_ = nullptr;
	Model* playerRightLeg_ = nullptr;

	Vector3 position_;
};

