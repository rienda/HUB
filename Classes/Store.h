#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Store : public Scene
{
public:
	static Scene * createScene();
	virtual bool init();
	CREATE_FUNC(Store);
	void doClose(Ref *pSender);
};
