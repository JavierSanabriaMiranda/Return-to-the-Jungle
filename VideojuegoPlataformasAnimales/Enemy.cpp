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
    // Parámetros para el movimiento circular simulado
    static float centerX = -1;    // Centro inicial X del enemigo
    static float centerY = -1;    // Centro inicial Y del enemigo
    static int phase = 0;         // Fase del movimiento (0: derecha, 1: abajo, 2: izquierda, 3: arriba)
    static float step = 2;        // Incremento en cada actualización
    static float distance = 200;  // Distancia máxima en cada dirección
    static float traveled = 0;    // Distancia recorrida en la fase actual

    // Inicializar el centro del círculo
    if (centerX == -1 && centerY == -1) {
        centerX = x;
        centerY = y;
    }

    // Movimiento en función de la fase
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

    // Cambiar de fase si se alcanzó la distancia máxima
    if (traveled >= distance) {
        phase = (phase + 1) % 4; // Cambiar a la siguiente fase
        traveled = 0;           // Reiniciar la distancia recorrida
    }

    // Animación: determinar la orientación
    if (phase == 0) {
        orientation = game->orientationRight; // Derecha
    }
    else if (phase == 2) {
        orientation = game->orientationLeft;  // Izquierda
    }

    // Actualizar animación
    bool endAnimation = animation->update();

    // Configurar la animación en función de la orientación
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
