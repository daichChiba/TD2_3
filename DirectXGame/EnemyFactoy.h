#pragma once
#include "kamataEngine.h"
#include "EnemyManager.h"
#include "EnemyActor.h"
#include <vector>
#include <memory>

using namespace KamataEngine;

class GameScene;
class Player;

class EnemyFactory {
public:
    void Initialize(Model* model, Model* bulletModel);
    void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
    std::unique_ptr<EnemyActor> AddEnemyGrabity();
    std::unique_ptr<EnemyActor> AddEnemyRevolution();
    void SetPlayer(Player* player);

private:
    GameScene* gameScene_;
    Model* model_ = nullptr;
    Model* bulletModel_ = nullptr;
    Player* player_;

};