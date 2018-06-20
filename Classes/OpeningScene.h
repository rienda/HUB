#pragma once
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

class OpeningScene : public Scene
{
public:
	static Scene * createScene();
	virtual bool init();
	CREATE_FUNC(OpeningScene);

	Size winSize;

	Layer *pBGLayer;

	Sprite *pSprite;

	void initOpScene();
	TransitionScene* transScene(Scene *pScene, float t);

	EventListenerTouchAllAtOnce *pListener;

	void onEnter();
	void onExit();

	bool isTouchInside(Layer *pLayer, Touch *pTouch);

	bool onTouchesBegan(const vector<Touch *> &pTouches, Event *pEvent);
	void onTouchesMoved(const vector<Touch *> &pTouches, Event *pEvent);
	void onTouchesEnded(const vector<Touch *> &pTouches, Event *pEvent);
};
