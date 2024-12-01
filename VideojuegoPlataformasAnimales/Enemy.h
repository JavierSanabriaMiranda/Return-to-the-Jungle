#pragma once

#include "Actor.h"
#include "Animation.h"

class Enemy : public Actor
{
public:
	Enemy(string img, float x, float y, int width, int height, Game* game);
	void draw(float scrollX = 0) override; // Va a sobrescribir
	void virtual update();
	//void impacted(); // Recibe impacto y pone animación de morir
	/*float vxIntelligence;*/
	int state;
	int orientation;
	float vxIntelligence;

	//Animation* aDying;
	Animation* aMovingRight;
	Animation* aMovingLeft;
	Animation* animation; // Referencia a la animación mostrada
};