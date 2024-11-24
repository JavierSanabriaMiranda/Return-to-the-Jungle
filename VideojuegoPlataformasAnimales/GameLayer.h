#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Space.h"
#include "Tile.h"
#include "Audio.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

#pragma once
class GameLayer: public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	void mouseToControls(SDL_Event event);
	void addCharacter(Player* character);

	Actor* message;
	bool pause;
	Space* space;
	float scrollX;
	int mapWidth;
	list<Tile*> tiles;
	bool controlContinue = false;
	Player* characters[3];
	Player* player;
	Background* background;

	Actor* citySign; // Elemento de final de nivel
	Tile* checkpoint; // Elemento de checkpoint
	bool takenCheckpoint; // Marca si se ha cogido o no el checkpoint

	Audio* audioBackground;

	int controlMoveY = 0;
	int controlMoveX = 0;

	int nextCharacter = 1;

private:
	void getMainCharacterForLevel();
	void changeCharacter();
};

