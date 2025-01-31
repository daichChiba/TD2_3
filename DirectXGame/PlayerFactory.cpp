#include "PlayerFactory.h"

#include "PlayerActor.h"
#include "PlayerWizard.h"

std::unique_ptr<PlayerActor> PlayerFactory::CraeteWizard()
{
	std::unique_ptr<PlayerActor> Wizard = std::make_unique<PlayerWizard>();
	
	return Wizard;
}

std::unique_ptr<PlayerActor> PlayerFactory::CraeteFencer()
{
	std::unique_ptr<PlayerActor> Wizard = std::make_unique<PlayerWizard>();
	
	return Wizard;
}
