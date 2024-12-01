#include "Gaviota.h"

Gaviota::Gaviota(float x, float y, Game* game)
	:Enemy("res/Gaviota.png", x, y, 40, 25, game) {

	vxIntelligence = -2;
	vx = vxIntelligence;
	distanciaX = 200;
	distanciaRecorridaX = 0;

	aMovingRight = new Animation("res/Gaviota_volando_derecha.png", width, height,
		350, 35, 6, 6, true, game);

	aMovingLeft = new Animation("res/Gaviota_volando_izquierda.png", width, height,
		350, 35, 6, 6, true, game);

	animation = aMovingRight;
}


void Gaviota::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}


	if (state == game->stateMoving) {
		if (orientation == game->orientationRight) {
			animation = aMovingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aMovingLeft;
		}
	}
	// Aumentamos la distancia recorrida horizontalmente
	distanciaRecorridaX += abs(vx);

	// Comprobamos si la gaviota ha recorrido mas de la distancia establecida
	if (distanciaRecorridaX >= distanciaX) {
		vx = -vx;
		distanciaRecorridaX = 0;  // Reiniciar la distancia recorrida
	}
}

void Gaviota::setVY(float vy) {
	this->vy = 0;
}