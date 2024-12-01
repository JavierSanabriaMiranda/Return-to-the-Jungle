#include "Mono.h"

Mono::Mono(float x, float y, Game* game)
	: Player("res/Mono.png", x, y, 40, 40, game) {

	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;

	bigIcon = "res/mono_icono_grande.png";
	smallIcon = "res/mono_icono_pequeno.png";

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
	aClimbingRight = new Animation("res/Mono_trepando_derecha.png", width, height,
		304, 45, 6, 6, true, game);
	aClimbingLeft = new Animation("res/Mono_trepando_izquierda.png", width, height,
		304, 45, 6, 6, true, game);

	animation = aRunningRight;
}

string Mono::getType() {
	return "Mono";
}

void Mono::jump() {
	if (!canClimb) {
		Player::jump();
	}
	else {
		vy = -4;
		y = y + vy;
	}
}

void Mono::setVY(float vy) {
	if (!canClimb) {
		Player::setVY(vy);
	}
	else {
		this->vy = 0;
	}
}

void Mono::moveX(float axis) {
	vx = axis * 5;
}

void Mono::update() {
	// En el aire y moviéndose o trepando, PASA a estar saltando
	if (onAir && (state == game->stateMoving || state == stateClimbing)) {
		state = game->stateJumping;
	}
	// No está en el aire y estaba saltando o trepando, PASA a moverse
	if (!onAir && (state == game->stateJumping || state == stateClimbing)) {
		state = game->stateMoving;
	}
	if (canClimb) {
		state = stateClimbing;
	}

	bool endAnimation = animation->update();

	if (collisionDown == true) {
		onAir = false;
	}
	else {
		onAir = true;
	}


	// Establecer orientación
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}


	// Selección de animación basada en estados
	if (state == game->stateJumping) {
		if (orientation == game->orientationRight) {
			animation = aJumpingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aJumpingLeft;
		}
	}
	if (state == game->stateMoving) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeft;
			}
		}
		if (vx == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
		}
	}
	if (state == stateClimbing) {
		if (orientation == game->orientationRight) {
			animation = aClimbingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aClimbingLeft;
		}
	}
}

string Mono::getBigIcon() {
	return bigIcon;
}

string Mono::getSmallIcon() {
	return smallIcon;
}