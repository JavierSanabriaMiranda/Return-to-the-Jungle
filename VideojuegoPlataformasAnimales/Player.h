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
	void setLocation(float x, float y);
	void virtual breakBox();
	string virtual getBigIcon() = 0;
	string virtual getSmallIcon() = 0;

	bool onAir;
	bool moving;
	int orientation;
	int state;
	int jumpQuantity = -16;

	string smallIcon; // Imagen que se muestra del personaje arriba izquierda del HUD cuando es el seleccionado
	string bigIcon; // Imagen que se muestra del personaje arriba izquierda del HUD cuando no es el seleccionado

	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aJumpingRight;
	Animation* aJumpingLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	
	Animation* animation; // Referencia a la animación mostrada

};