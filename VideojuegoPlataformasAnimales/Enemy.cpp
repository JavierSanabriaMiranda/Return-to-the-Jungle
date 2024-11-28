#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/Gaviota.png", x, y, 40, 25, game) {

	vx = 1;
	/*vxIntelligence = -1;*/
	/*vx = vxIntelligence;*/
	orientation = game->orientationRight;
	state = game->stateMoving;

	state = game->stateMoving;

	aMovingRight = new Animation("res/Gaviota_volando_derecha.png", width, height,
		350, 35, 6, 6, true, game);

	aMovingLeft = new Animation("res/Gaviota_volando_izquierda.png", width, height,
		350, 35, 6, 6, true, game);

	animation = aMovingRight;
}

void Enemy::update() {
    // Par�metros para el movimiento circular simulado
    static float centerX = -1;    // Centro inicial X del enemigo
    static float centerY = -1;    // Centro inicial Y del enemigo
    static int phase = 0;         // Fase del movimiento (0: derecha, 1: abajo, 2: izquierda, 3: arriba)
    static float step = 2;        // Incremento en cada actualizaci�n
    static float distance = 200;  // Distancia m�xima en cada direcci�n
    static float traveled = 0;    // Distancia recorrida en la fase actual

    // Inicializar el centro del c�rculo
    if (centerX == -1 && centerY == -1) {
        centerX = x;
        centerY = y;
    }

    // Movimiento en funci�n de la fase
    switch (phase) {
    case 0: // Derecha
        x += step;
        break;
    case 1: // Abajo
        y += step;
        break;
    case 2: // Izquierda
        x -= step;
        break;
    case 3: // Arriba
        y -= step;
        break;
    }

    // Incrementar la distancia recorrida
    traveled += step;

    // Cambiar de fase si se alcanz� la distancia m�xima
    if (traveled >= distance) {
        phase = (phase + 1) % 4; // Cambiar a la siguiente fase
        traveled = 0;           // Reiniciar la distancia recorrida
    }

    // Animaci�n: determinar la orientaci�n
    if (phase == 0) {
        orientation = game->orientationRight; // Derecha
    }
    else if (phase == 2) {
        orientation = game->orientationLeft;  // Izquierda
    }

    // Actualizar animaci�n
    bool endAnimation = animation->update();

    // Configurar la animaci�n en funci�n de la orientaci�n
    if (state == game->stateMoving) {
        if (orientation == game->orientationRight) {
            animation = aMovingRight;
        }
        if (orientation == game->orientationLeft) {
            animation = aMovingLeft;
        }
    }
}


void Enemy::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}

//void Enemy::impacted() {
//	if (state != game->stateDying) {
//		state = game->stateDying;
//	}
//}
