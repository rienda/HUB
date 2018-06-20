#pragma once
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

class Status : public Scene
{
public:
	static Scene * createScene();
	virtual bool init();
	CREATE_FUNC(Status);

	Size winSize;

	Layer *pBGLayer;
	Layer *pBTLayer;

	Sprite *pBack;
	Sprite *pBackP;

	bool isBackP;

	void createBG();
	void createButton();

	EventListenerTouchAllAtOnce *pListener;

	void onEnter();
	void onExit();

	bool isTouchInside(Sprite *pSpr, Touch *pTouch);

	bool onTouchesBegan(const vector<Touch *> &pTouches, Event *pEvent);
	void onTouchesMoved(const vector<Touch *> &pTouches, Event *pEvent);
	void onTouchesEnded(const vector<Touch *> &pTouches, Event *pEvent);
};
