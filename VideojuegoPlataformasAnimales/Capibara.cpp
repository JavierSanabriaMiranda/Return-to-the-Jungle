#include "Capibara.h"

Capibara::Capibara(float x, float y, Game* game)
	: Player("res/Capibara.png", x, y, 60, 40, game) {

	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;

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

	animation = aRunningRight;
}

//void Capibara::update() {
//	Player::update();
//	if (vx == 0 && !onAir) {
//		state = this->stateStill;
//	} 
//	if (state == stateStill) {
//		this->timeToSleep--;
//	}
//	else {
//		timeToSleep = 50;
//	}
//
//	if (timeToSleep <= 0)
//		animation = aSleep;
//}
