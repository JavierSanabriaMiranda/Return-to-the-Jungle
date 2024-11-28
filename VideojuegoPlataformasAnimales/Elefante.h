#pragma once
#include "Player.h"

class Elefante : public Player
{
public:
	Elefante(float x, float y, Game* game);
	void jump() override;
	string getBigIcon() override;
	string getSmallIcon() override;
	string getType() override;
	void breakBox() override;
	void update() override;

	int jumpQuantity = -10;
	bool breaking = false;
	int timeBreaking = 15;

	int stateBreaking = -3;

	Animation* aBreakingLeft;
	Animation* aBreakingRight;
};

