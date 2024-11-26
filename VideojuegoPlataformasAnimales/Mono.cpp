#include "Mono.h"

Mono::Mono(float x, float y, Game* game)
	: Player("res/Mono.png", x, y, 40, 40, game) {

	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;

	aJumpingRight = new Animation("res/Mono_saltando_derecha.png",
		width, height, 185, 45, 6, 3, true, game);
	aJumpingLeft = new Animation("res/Mono_saltando_izquierda.png",
		width, height, 185, 45, 6, 3, true, game);
	aRunningRight = new Animation("res/Mono_andando_derecha.png", width, height,
		540, 45, 6, 8, true, game);
	aRunningLeft = new Animation("res/Mono_andando_izquierda.png", width, height,
		540, 45, 6, 8, true, game);
	aIdleRight = new Animation("res/Mono_estatico_derecha.png", width, height,
		347, 40, 6, 6, true, game);
	aIdleLeft = new Animation("res/Mono_estatico_izquierda.png", width, height,
		347, 40, 6, 6, true, game);

	animation = aRunningRight;
}