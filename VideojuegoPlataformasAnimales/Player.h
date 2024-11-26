#pragma once

#include "Actor.h"
#include "Animation.h" // incluir animacion 

class Player : public Actor
{
public:
	Player(string img, float x, float y, int width, int height, Game* game);
	void virtual update() ;
	void virtual jump();
	void virtual moveDown();
	string virtual getType();
	void virtual moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0) override; // Va a sobrescribir
	void loseLife();
	void setLocation(float x, float y);
	
	int lifes = 3;
	int invulnerableTime = 0;
	bool onAir;
	bool moving;
	int orientation;
	int state;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aJumpingRight;
	Animation* aJumpingLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	
	Animation* animation; // Referencia a la animación mostrada

};