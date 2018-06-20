#pragma once
#include "cocos2d.h"

#define CULUMN_COUNT 8
#define ROW_COUNT 8

USING_NS_CC;

using namespace std;

class PuzzleBattle: public Scene
{
public:
	static Scene * createScene();
	virtual bool init();
	CREATE_FUNC(PuzzleBattle);

	char *puzType[5] =
	{
		"battle_ui/puz_red.png" ,
		"battle_ui/puz_blue.png",
		"battle_ui/puz_green.png",
		"battle_ui/puz_yellow.png",
		"battle_ui/puz_gray.png"
	};

	Size winSize;

	Sprite *pBlock;
	
	Sprite *puzBox[CULUMN_COUNT][ROW_COUNT];



	Layer *pBGLayer;
	Layer *pBTLayer;
	Layer *pUserLayer;
	Layer *pEnemyLayer;
	Layer *pBlockLayer;
	Layer *pPuzLayer;

	Sprite *pClick;

	void InitBG();
	void InitBT();
	void InitUserInfo();
	void InitEnemyInfo();
	void InitEnemyAction(Sprite &pEnemy);
	void InitPuzInfo();

	EventListenerTouchAllAtOnce *pListener;

	void onEnter();
	void onExit();

	bool isTouchInside(Sprite *pSpr, Touch *pTouch);

	bool onTouchesBegan(const vector<Touch *> &pTouches, Event *pEvent);
	void onTouchesMoved(const vector<Touch *> &pTouches, Event *pEvent);
	void onTouchesEnded(const vector<Touch *> &pTouches, Event *pEvent);

	void doClose(Ref *pSender);
};