#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Family : public Scene
{
public:
	static Scene * createScene();
	virtual bool init();
	CREATE_FUNC(Family);
	void doClose(Ref *pSender);
};
