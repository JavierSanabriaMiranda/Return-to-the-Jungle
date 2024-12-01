#include "Player.h"

/*
* Este constructor nunca se va a llamar pues la clase Player sirve como plantilla a los characters
*/
Player::Player(string img ,float x, float y, int width, int height, Game* game)
	: Actor(img, x, y, width, height, game) {

	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;
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
	animation->draw(x - scrollX, y);
}

void Player::jump() {
	if (!onAir) {
		vy = jumpQuantity;
		onAir = true;
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

void Player::breakBox() {
	//Do nothing
}
