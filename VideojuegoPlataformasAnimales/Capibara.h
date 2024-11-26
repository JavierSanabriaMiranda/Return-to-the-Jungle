#pragma once
#include "Player.h"

class Capibara : public Player
{
public :
	Capibara(float x, float y, Game* game);
	//void update() override;

	Animation* aSleep;
	int timeToSleep = 50;
	int const stateStill = -1; //quieto
};

