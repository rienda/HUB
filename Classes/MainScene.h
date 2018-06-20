#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(MainScene);

	Size winSize;

	Sprite *pStatus;
	Sprite *pStatusP;
	Sprite *pFamily;
	Sprite *pFamilyP;
	Sprite *pStory;
	Sprite *pStoryP;
	Sprite *pStore;
	Sprite *pStoreP;
	Sprite *pFriend;
	Sprite *pFriendP;

	bool isStatusP;
	bool isFamilyP;
	bool isStoryP;
	bool isStoreP;
	bool isFriendP;

	Layer *pBGLayer;
	Layer *pBTLayer;

	EventListenerTouchAllAtOnce *pListener;

	void createBG();
	void createButton();

	void onEnter();
	void onExit();

	bool isTouchInside(Sprite *pSpr, Touch *pTouch);

	bool onTouchesBegan(const vector<Touch *> &pTouches, Event *pEvent);
	void onTouchesMoved(const vector<Touch *> &pTouches, Event *pEvent);
	void onTouchesEnded(const vector<Touch *> &pTouches, Event *pEvent);


};

#endif // __HELLOWORLD_SCENE_H__
