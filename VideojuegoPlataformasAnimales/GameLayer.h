#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

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
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
};

