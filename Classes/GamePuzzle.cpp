#include "GamePuzzle.h"

GamePuzzle::~GamePuzzle(){
}

GamePuzzle::GamePuzzle()
	: _type(0),
	_state(GamePuzzle::LIVE)
{
}

GamePuzzle* GamePuzzle::sprWithFile(const char* pszFileName)
{
	GamePuzzle* sprite = new GamePuzzle();
	if (sprite && sprite->initWithFile(pszFileName)) {
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}