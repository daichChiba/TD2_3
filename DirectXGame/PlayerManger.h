#pragma once

#include "KamataEngine.h"

#include "PlayerActor.h"
#include "PlayerWizard.h"
#include "PlayerFactory.h"

using namespace KamataEngine;

class GameScene;

class PlayerManager
{
public:
	void Initialize(Model* model, Model* bulletModel, Model* zoldrakModel, const Vector3 position, GameScene* gameScene);
	void Update();
	void Draw(Camera* camera);

	void CreatePlayerWizard();

	std::unique_ptr<PlayerActor>& GetPlayerActor() { return player_; }
private:
	GameScene* gameScene_;

	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	Model* zoldrakModel_ = nullptr;
	WorldTransform worldTransform_;

	std::unique_ptr<PlayerActor> player_;

	PlayerFactory* playerFactory;
};

