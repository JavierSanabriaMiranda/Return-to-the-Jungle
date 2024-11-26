#include "Elefante.h"

Elefante::Elefante(float x, float y, Game* game)
	: Player("res/Elefante.png", x, y, 112, 85, game) {

	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;

	aJumpingRight = new Animation("res/Elefante_saltando_derecha.png",
		width, height, 406, 85, 6, 3, true, game);
	aJumpingLeft = new Animation("res/Elefante_saltando_izquierda.png",
		width, height, 406, 85, 6, 3, true, game);
	aRunningRight = new Animation("res/Elefante_andando_derecha.png", width, height,
		706, 85, 6, 6, true, game);
	aRunningLeft = new Animation("res/Elefante_andando_izquierda.png", width, height,
		706, 85, 6, 6, true, game);
	aIdleRight = new Animation("res/Elefante_estatico_derecha.png", width, height,
		673, 85, 6, 6, true, game);
	aIdleLeft = new Animation("res/Elefante_estatico_izquierda.png", width, height,
		673, 85, 6, 6, true, game);

	animation = aRunningRight;
}