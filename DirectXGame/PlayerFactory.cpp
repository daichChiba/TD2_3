#include "PlayerFactory.h"

#include "PlayerActor.h"
#include "PlayerWizard.h"

std::unique_ptr<PlayerActor> PlayerFactory::CreateWizard()
{
	std::unique_ptr<PlayerActor> player_ = std::make_unique< PlayerWizard>();
	return player_;
}
