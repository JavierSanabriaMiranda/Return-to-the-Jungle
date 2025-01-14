#include "Tucan.h"

Tucan::Tucan(float x, float y, Game* game)
	: Player("res/Tucan.png", x, y, 60, 40, game) {

	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;

	smallIcon = "res/tucan_icono_pequeno.png";
	bigIcon = "res/tucan_icono_grande.png";

	aJumpingRight = new Animation("res/Tucan_saltando_derecha.png",
		width, height, 560, 43, 6, 8, true, game);
	aJumpingLeft = new Animation("res/Tucan_saltando_izquierda.png",
		width, height, 560, 43, 6, 8, true, game);
	aRunningRight = new Animation("res/Tucan_andando_derecha.png", width, height,
		420, 41, 6, 6, true, game);
	aRunningLeft = new Animation("res/Tucan_andando_izquierda.png", width, height,
		420, 41, 6, 6, true, game);
	aIdleRight = new Animation("res/Tucan_estatico_derecha.png", width, height,
		350, 40, 6, 6, true, game);
	aIdleLeft = new Animation("res/Tucan_estatico_izquierda.png", width, height,
		350, 40, 6, 6, true, game);

	animation = aRunningRight;
}

void Tucan::update() {
	Player::update();
	if (collisionDown == true) {
		onAir = false;
		remainingJumps = 1;
	}
	else {
		onAir = true;
	}
	jumpCoolDown--;
}

void Tucan::jump() {
	if (onAir && remainingJumps == 0) {
		return;
	}
	if (jumpCoolDown > 0) {
		return;
	}
	vy = jumpQuantity;
	onAir = true;
	remainingJumps--;
	jumpCoolDown = 10;
}

string Tucan::getBigIcon() {
	return bigIcon;
}

string Tucan::getSmallIcon() {
	return smallIcon;
}