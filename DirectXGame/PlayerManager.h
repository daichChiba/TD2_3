#pragma once

#include "KamataEngine.h"
//#include "Scene/GameScene.h"

#include "PlayerActor.h"

using namespace KamataEngine;

class GameScene;
//class PlayerActor;
class PlayerFactory;

class PlayerManager
{
public:
	void Initialize(Model* playerModel, Model* bulletModel, Model* beamModel, const Vector3 pos, GameScene* gameScene);
	void Update();
	void Draw(Camera* camera);

	void CreateWizard();

	PlayerActor* GetActor() const { return player_.get(); }
private:
	Model* model_;
	Model* bulletModel_;
	Model* beamModel_;

	std::unique_ptr<PlayerActor> player_;

	GameScene* gameScene_;
	PlayerFactory* factory_;

	Vector3 position_;
};

