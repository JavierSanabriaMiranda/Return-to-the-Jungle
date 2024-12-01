#pragma once

#include "Tile.h"
#include "GameLayer.h"

class TunnelTile : public Tile
{
public:
	TunnelTile(string orientacion,float x, float y, Game* game, GameLayer* gameLayer);
	void update() override; // Nuevo m�todo para actualizar el estado
	void generateCar();
	bool contains(float carX, float carY);
	TunnelTile* getTunnelContaining(float carX, float carY);

private:
	GameLayer* gameLayer;
	float timeSinceLastCar; // Tiempo acumulado desde la �ltima generaci�n
	float carGenerationInterval; // Intervalo entre coches en segundos
};
