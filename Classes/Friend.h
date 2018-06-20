#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Friend : public Scene
{
public:
	static Scene * createScene();
	virtual bool init();
	CREATE_FUNC(Friend);
	void doClose(Ref *pSender);
};
