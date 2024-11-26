#include "Player.h"

/*
* Este constructor nunca se va a llamar pues la clase Player sirve como plantilla a los characters
*/
Player::Player(string img ,float x, float y, int width, int height, Game* game)
	: Actor(img, x, y, width, height, game) {

	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;

	aJumpingRight = new Animation("res/Tucan_saltando_derecha.png",
		width, height, 560, 43, 6, 8, true, game);
	aJumpingLeft = new Animation("res/Tucan_saltando_izquierda.png",
		width, height, 560, 43, 6, 8, true, game);
	aRunningRight = new Animation("res/Tucan_andando_derecha.png", width, height,
		420, 41, 6, 6, true, game);
	aRunningLeft = new Animation("res/Tucan_andando_izquierda.png", width, height,
		420, 41, 6, 6, true, game);
	aIdleRight = new Animation("res/Tucan.png", width, height,
		60, 40, 6, 1, true, game);
	aIdleLeft = new Animation("res/Tucan.png", width, height,
		60, 40, 6, 1, true, game);

	animation = aRunningRight;
}


void Player::update() {
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

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

void Player::draw(float scrollX) {
	if (invulnerableTime == 0) {
		animation->draw(x - scrollX, y);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			animation->draw(x - scrollX, y);
		}
	}
}

void Player::jump() {
	if (!onAir) {
		vy = jumpQuantity;
		onAir = true;
	}
}

void Player::loseLife() {
	if (invulnerableTime <= 0) {
		if (lifes > 0) {
			lifes--;
			invulnerableTime = 100;
			// 100 actualizaciones 
		}
	}
}

void Player::setLocation(float x, float y) {
	this->x = x;
	this->y = y;
}

string Player::getType() {
	return "Player";
}

void Player::moveDown() {
	//Do nothing
}
