#pragma once

#include "Player.h"

class Serpiente : public Player
{
public:
	Serpiente(float x, float y, Game* game);

	void moveX(float axis) override;
	void jump() override;

	int jumpQuantity = -13;
};

