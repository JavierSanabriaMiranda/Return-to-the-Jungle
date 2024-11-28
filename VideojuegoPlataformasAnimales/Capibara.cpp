#include "Capibara.h"

Capibara::Capibara(float x, float y, Game* game)
	: Player("res/Capibara.png", x, y, 60, 40, game) {

	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;

	bigIcon = "res/capibara_icono_grande.png";
	smallIcon = "res/capibara_icono_pequeno.png";

	aJumpingRight = new Animation("res/Capibara_saltando_derecha.png",
		width, height, 182, 50, 6, 3, true, game);
	aJumpingLeft = new Animation("res/Capibara_saltando_izquierda.png",
		width, height, 182, 50, 6, 3, true, game);
	aRunningRight = new Animation("res/Capibara_andando_derecha.png", width, height,
		577, 50, 6, 10, true, game);
	aRunningLeft = new Animation("res/Capibara_andando_izquierda.png", width, height,
		577, 50, 6, 10, true, game);
	aIdleRight = new Animation("res/Capibara_estatica_derecha.png", width, height,
		363, 50, 6, 6, true, game);
	aIdleLeft = new Animation("res/Capibara_estatica_izquierda.png", width, height,	
		363, 50, 6, 6, true, game);
	/*aSleep = new Animation("res/Capibara_dormida.png", width, height,
		600, 50, 6, 12, true, game);*/
	aSwimmingLeft = new Animation("res/Capibara_andando_izquierda.png", width, height,
		577, 50, 6, 10, true, game);
	aSwimmingRight = new Animation("res/Capibara_andando_derecha.png", width, height,
		577, 50, 6, 10, true, game);


	animation = aRunningRight;
}

void Capibara::update() {
	//Para la capibara dormida
	/*if (vx == 0 && !onAir) {
		state = this->stateStill;
	} 
	if (state == stateStill) {
		this->timeToSleep--;
	}
	else {
		timeToSleep = 50;
	}

	if (timeToSleep <= 0)
		animation = aSleep;*/




	// En el aire y moviéndose, PASA a estar saltando
	if (onAir && (state == game->stateMoving || state == stateSwim)) {
		state = game->stateJumping;
	}
	// No está en el aire y estaba saltando, PASA a moverse
	if (!onAir && (state == game->stateJumping || state == stateSwim)) {
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
	if (canSwim) {
		state = this->stateSwim;
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
	if (state == this->stateSwim) {
		if (orientation == game->orientationRight) {
			animation = aSwimmingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aSwimmingLeft;
		}
	}
}


string Capibara::getType() {
	return "Capibara";
}


void Capibara::moveDown() {
	if (canSwim) {
		vy = 3;
		y = y + vy;
	}
	else {
		Player::moveDown();
	}
}

void Capibara::setVY(float vy) {
	if (canSwim) {
		this->vy = 0;
	}
	else {
		Player::setVY(vy);
	}
}

void Capibara::jump() {
	if (canSwim) {
		vy = -3;
		y = y + vy;
	}
	else {
		Player::jump();
	}
}

string Capibara::getBigIcon() {
	return bigIcon;
}

string Capibara::getSmallIcon() {
	return smallIcon;
}