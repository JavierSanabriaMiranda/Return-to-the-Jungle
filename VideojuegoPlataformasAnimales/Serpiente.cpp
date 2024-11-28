#include "Serpiente.h"

Serpiente::Serpiente(float x, float y, Game* game)
	: Player("res/Serpiente.png", x, y, 82, 25, game) {

	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;

	bigIcon = "res/serpiente_icono_grande.png";
	smallIcon = "res/serpiente_icono_pequeno.png";

	aJumpingRight = new Animation("res/Serpiente_saltando_derecha.png",
		width, height, 342, 25, 6, 3, true, game);
	aJumpingLeft = new Animation("res/Serpiente_saltando_izquierda.png",
		width, height, 342, 25, 6, 3, true, game);
	aRunningRight = new Animation("res/Serpiente_andando_derecha.png", width, height,
		745, 25, 6, 8, true, game);
	aRunningLeft = new Animation("res/Serpiente_andando_izquierda.png", width, height,
		745, 25, 6, 8, true, game);
	aIdleRight = new Animation("res/Serpiente_estatico_derecha.png", width, height,
		327, 25, 6, 4, true, game);
	aIdleLeft = new Animation("res/Serpiente_estatico_izquierda.png", width, height,
		327, 25, 6, 4, true, game);

	animation = aRunningRight;
}

void Serpiente::moveX(float axis) {
	vx = axis * 4;
}

void Serpiente::jump() {
	if (!onAir) {
		vy = jumpQuantity;
		onAir = true;
	}
}

string Serpiente::getBigIcon() {
	return bigIcon;
}

string Serpiente::getSmallIcon() {
	return smallIcon;
}