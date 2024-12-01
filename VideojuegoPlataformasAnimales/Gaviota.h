#pragma once

#include "Enemy.h"
class Gaviota : public Enemy
{
public:
	Gaviota(float x, float y, Game* game);
	void setVY(float vy) override;
	void update() override;

	float distanciaX;
	float distanciaRecorridaX;
};