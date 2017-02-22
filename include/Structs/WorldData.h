#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Structs/AnimatedTileData.h"
#include "Structs/LightData.h"
#include "Structs/TriggerData.h"
#include "Structs/WeatherData.h"
#include "Structs/SignData.h"
#include "Structs/ChestTileData.h"

struct WorldData {
	virtual ~WorldData() {};

	std::string id;
	sf::Vector2i mapSize;
	std::string tileSetPath;
	std::string musicPath;
	std::vector<std::vector<int>> backgroundTileLayers;
	std::vector<std::vector<int>> lightedForegroundTileLayers;
	std::vector<std::vector<int>> foregroundTileLayers;
	
	std::vector<AnimatedTileData> animatedTiles;
	std::vector<bool> collidableTiles;
	std::vector<std::vector<bool>> collidableTilePositions;

	std::vector<LightData> lights;
	std::vector<TriggerData> triggers;
	std::vector<SignData> signs;
	std::vector<ChestTileData> chests;
	
	sf::FloatRect mapRect;
	WeatherData weather;
};