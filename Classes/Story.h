#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Story : public Scene
{
public:
	static Scene * createScene();
	virtual bool init();
	CREATE_FUNC(Story);

	Size winSize;

	void doClose(Ref *pSender);
	void doPuzBattle(Ref *pSender);
};
