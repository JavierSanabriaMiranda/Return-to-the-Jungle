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
	string getBigIcon() override;
	string getSmallIcon() override;

	bool canSwim;
	Animation* aSwimmingRight;
	Animation* aSwimmingLeft;
	int const stateSwim = -2; //quieto
};

