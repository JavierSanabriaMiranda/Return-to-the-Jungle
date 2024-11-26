#pragma once
#include "Player.h"

class Elefante : public Player
{
public :
	Elefante(float x, float y, Game* game);
	void jump() override;

	int jumpQuantity = -10;
};

