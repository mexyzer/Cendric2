#pragma once

#include "global.h"
#include "Enums/FractionID.h"

struct MerchantData final {
	FractionID fraction = FractionID::VOID;
	// the multiplier for the selling prices (1.0 is the default)
	float multiplier = 1.0f;
	// the multiplier for the buying prices (0.4 is the default)
	float receiver_multiplier = 0.4f;

	// the wares the npc offers for sale
	std::map<std::string, int> wares;
	// reputation needed to buy an item (default 0)
	std::map<std::string, int> reputation;
};