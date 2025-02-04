// EnemyFactory.cpp
#include "../DirectXGame/EnemyFactoy.h"
#include "../DirectXGame/EnemyActor.h"
#include "../DirectXGame/EnemyGravity.h"
#include "../DirectXGame/EnemyRevolution.h"

void EnemyFactory::Initialize(Model* model, Model* bulletModel) {
	model_ = model;
	bulletModel_ = bulletModel;
}

std::unique_ptr<EnemyActor> EnemyFactory::AddEnemy() {
	std::unique_ptr<EnemyActor> enemy_ = std::make_unique<EnemyGravity>();
	//enemy_->Initialize(model_, bulletModel_, Vector3{0.0f, 0.0f, 0.0f}, player_, gameScene_);
	//enemy_->SetGameScene(gameScene_);
	//enemy_->GetPlayer(player_);
	return enemy_;
}

void EnemyFactory::SetPlayer(Player* player) { player_ = player; }
