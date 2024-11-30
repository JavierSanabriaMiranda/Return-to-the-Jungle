#include "Elefante.h"

Elefante::Elefante(float x, float y, Game* game)
	: Player("res/Elefante.png", x, y, 112, 85, game) {

	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;

	bigIcon = "res/elefante_icono_grande.png";
	smallIcon = "res/elefante_icono_pequeno.png";

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
	aBreakingLeft = new Animation("res/Elefante_saltando_izquierda.png", width, height,
		673, 85, 6, 6, true, game);
	aBreakingRight = new Animation("res/Elefante_saltando_derecha.png", width, height,
		673, 85, 6, 6, true, game);

	animation = aRunningRight;
}

void Elefante::jump() {
	if (!onAir) {
		vy = jumpQuantity;
		onAir = true;
	}
}

string Elefante ::getType() {
	return "Elefante";
}

void Elefante::breakBox() {
	if (!breaking) {
		breaking = true;
		state = stateBreaking;
	}
}

void Elefante::update() {
	// En el aire y moviéndose, PASA a estar saltando
	if (onAir && state == game->stateMoving) {
		state = game->stateJumping;
	}
	// No está en el aire y estaba saltando, PASA a moverse
	if (!onAir && state == game->stateJumping) {
		state = game->stateMoving;
	}


	if (invulnerableTime > 0) {
		invulnerableTime--;
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

	//Update del elefante
	if (breaking) {
		timeBreaking--;
		state = stateBreaking;
	}
	else {
		timeBreaking = 15;
	}
	if (timeBreaking <= 0) {
		breaking = false;
		state = game->stateMoving;
	}
	if (state == this->stateBreaking) {
		if (orientation == game->orientationRight) {
			animation = aBreakingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aBreakingLeft;
		}
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
	
	
}

string Elefante::getBigIcon() {
	return bigIcon;
}

string Elefante::getSmallIcon() {
	return smallIcon;
}
