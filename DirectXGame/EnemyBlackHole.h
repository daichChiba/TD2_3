#pragma once
#include "KamataEngine.h"
#include "EnemyActor.h"

using namespace KamataEngine;



class EnamyBlackHole : public EnemyActor {
public:
	void Update() override;
private:
	static inline const int kMaxHp = 100;
};