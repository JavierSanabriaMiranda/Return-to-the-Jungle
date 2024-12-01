#include "TunnelTile.h"
#include "Coche.h"
#include "Enemy.h"

TunnelTile::TunnelTile(string orientacion, float x, float y, Game* game, GameLayer* gameLayer)
	: Tile("res/Tile_tunel_" + orientacion + ".png", x, y, 65, 92, game) {

	vy = 0;
	this->gameLayer = gameLayer;

	timeSinceLastCar = 0.0f; // Inicializamos el tiempo transcurrido
	carGenerationInterval = 3.0f; // Generar un coche cada 5 segundos (por ejemplo)
}

void TunnelTile::update() {
	// Obtener el tiempo actual
    static Uint32 lastUpdateTime = SDL_GetTicks(); // Momento de la �ltima actualizaci�n
    Uint32 currentTime = SDL_GetTicks(); // Tiempo actual

    // Calcular el tiempo transcurrido en segundos
    float deltaTime = (currentTime - lastUpdateTime) / 1000.0f;

    // Actualizar el temporizador
    timeSinceLastCar += deltaTime;

	// Si ha pasado el intervalo, genera un coche y reinicia el temporizador
	if (timeSinceLastCar >= carGenerationInterval) {
		generateCar();
		timeSinceLastCar = 0.0f; // Reinicia el temporizador
	}
	// Actualizar el �ltimo tiempo de actualizaci�n
	lastUpdateTime = currentTime;

	for (auto it = gameLayer->enemies.begin(); it != gameLayer->enemies.end(); ) {
		Enemy* enemy = *it;
		TunnelTile* otherTunnel = getTunnelContaining(enemy->x, enemy->y);

		if (otherTunnel != nullptr && otherTunnel != this) {
			// Elimina el coche del espacio f�sico y de la lista
			gameLayer->space->removeDynamicActor(enemy);
			delete enemy;
			it = gameLayer->enemies.erase(it); // Elimina el coche y actualiza el iterador
		}
		else {
			++it; // Avanza al siguiente coche si no se elimin�
		}
	}
}

void TunnelTile::generateCar() {
	Enemy* enemy = new Coche(x, y, game);
	this->gameLayer->enemies.push_back(enemy);
	this->gameLayer->space->addDynamicActor(enemy);
}

bool TunnelTile::contains(float carX, float carY) {
	// Verifica si las coordenadas del coche (carX, carY) est�n dentro del �rea del t�nel
	return carX >= x && carX <= x + width && carY >= y && carY <= y + height;
}

TunnelTile* TunnelTile::getTunnelContaining(float carX, float carY) {
	for (Tile* tile : gameLayer->tiles) {
		TunnelTile* tunnel = dynamic_cast<TunnelTile*>(tile);
		if (tunnel != nullptr) {
			// Verificamos si el coche est� dentro de este t�nel
			if (tunnel->contains(carX, carY)) {
				return tunnel;
			}
		}
	}
	return nullptr; // Si no est� en ning�n t�nel
}

