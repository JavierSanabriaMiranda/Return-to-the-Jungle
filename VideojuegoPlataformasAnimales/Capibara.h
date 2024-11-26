#pragma once
#include "Player.h"

class Capibara : public Player
{
public :
	Capibara(float x, float y, Game* game);
	void update() override;
	void jump() override;
	void moveDown() override;
	string getType() override;
	void setVY(float vy) override;

	Animation* aSleep;
	int timeToSleep = 50;
	int const stateStill = -1; //quieto
	bool canSwim;
	Animation* aSwimmingRight;
	Animation* aSwimmingLeft;
	int const stateSwim = -2; //quieto
};

