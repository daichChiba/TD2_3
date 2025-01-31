#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class PlayerActor;

class PlayerFactory
{
public:
	std::unique_ptr<PlayerActor> CraeteWizard();
	std::unique_ptr<PlayerActor> CraeteFencer();
};

