#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Space.h"
#include "Tile.h"
#include "VineTile.h"
#include "Audio.h"
#include "CharacterIcon.h"
#include "ForbiddenSymbol.h"
#include "Enemy.h"
#include "BoxTile.h"


#include <fstream> // Leer ficheros
#include <sstream> // Leer l�neas / String
#include <list>

#pragma once
class GameLayer: public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void firstPrepareGameLayer();
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
	list<Tile*> waterTiles;
	list<VineTile*> vineTiles;
	list<BoxTile*> boxTiles;
	list<Tile*> collectables;
	bool collectablesTaken[3];
	int numCollectables = 0;
	int numeroOsosCargados = 0;
	bool collectableTakenAtCheckpoint[3];
	int numeroOsosCargadosAtCheckpoint = 0;
	int numCollectablesAtCheckpoint = 0;
	list<Tile*> tunnelTilesD;
	list<Tile*> tunnelTilesL;
	bool controlContinue = false;
	Player* characters[3];
	Player* player;
	Background* background;

	Actor* citySign; // Elemento de final de nivel
	Tile* checkpoint; // Elemento de checkpoint
	bool takenCheckpoint; // Marca si se ha cogido o no el checkpoint

	CharacterIcon* firstCharacterIcon;
	CharacterIcon* secondCharacterIcon;
	CharacterIcon* thirdCharacterIcon;

	CharacterIcon* osito1;
	CharacterIcon* osito2;
	CharacterIcon* osito3;

	ForbiddenSymbol* forbiddenSymbol;

	Audio* audioBackground;

	int controlMoveY = 0;
	int controlMoveX = 0;

	int nextCharacter = 1;

	list<Enemy*> enemies;

private:
	void getMainCharacterForLevel();
	void changeCharacter();
	void addCharactersToSpace();
	void dibujarOsitos(int numOsitos);
};

