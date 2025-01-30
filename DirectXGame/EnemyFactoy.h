#pragma once
#include "kamataEngine.h"
#include "EnemyManager.h"
#include "EnemyActor.h"
#include <vector>
#include <memory>

using namespace KamataEngine;

class GameScene;
class PlayerWizard;

class EnemyFactory {
public:
    void Initialize(Model* model, Model* bulletModel);
    void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
    std::unique_ptr<EnemyActor> AddEnemy();
    void SetPlayer(PlayerWizard* player);

private:
    GameScene* gameScene_;
    Model* model_ = nullptr;
    Model* bulletModel_ = nullptr;
    PlayerWizard* player_;

};