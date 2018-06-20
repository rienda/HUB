#ifndef __GAME_PUZZLE_H__
#define __GAME_PUZZLE_H__

#include "cocos2d.h"

USING_NS_CC;

class GamePuzzle : public Sprite
{
private:

public:
	enum gameState {
		LIVE,
		DEAD,
		SELECT,
		MOVE
	};

	CC_SYNTHESIZE(int, _type, Type);
	CC_SYNTHESIZE(int, _state, State);

	static GamePuzzle* sprWithFile(const char* pszFileName);

	GamePuzzle();
	~GamePuzzle();
};

#endif // __GAME_PUZZLE_H__
