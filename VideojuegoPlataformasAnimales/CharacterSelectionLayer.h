#pragma once

#include "Layer.h"
#include "Actor.h"
#include "Background.h"
#include "GameLayer.h"

class CharacterSelectionLayer : public Layer
{
public:
	CharacterSelectionLayer(Game* game, GameLayer* gameLayer);
	void init() override;
	void draw() override;
	void processControls() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event);
	void gamePadToControls(SDL_Event event);
	void setFondo(string filename);
	bool controlContinue;
	SDL_GameController* gamePad; // Mando
	Background* background;
	Actor* buttonTucan;
	Actor* buttonElefante;
	Actor* buttonSerpiente;
	Actor* buttonCapibara;
	Actor* buttonMono;
	GameLayer* currentGameLayer;

	bool selectedTucan = false;
	bool selectedElefante = false;
	bool selectedSerpiente = false;
	bool selectedCapibara = false;
	bool selectedMono = false;

	int charactersSelected = 1;

private:
	void selectTucan();
	void selectElefante();
	void selectSerpiente();
	void selectCapibara();
	void selectMono();
};

