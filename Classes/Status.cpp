#include "Status.h"
#include "MainScene.h"
Scene * Status::createScene()
{
	return Status::create();
}
bool Status::init()
{
	if (!Scene::init())
	{
		return false;
	}

	createBG();

	createButton();


	return true;

}
void Status::createBG()
{
	winSize = Director::getInstance()->getWinSize();

	pBGLayer = Layer::create();
	this->addChild(pBGLayer);

	pBTLayer = Layer::create();
	this->addChild(pBTLayer);

	auto pSpr = Sprite::create("Images/bg_temple.png");
	pSpr->setScale(0.8f);
	pSpr->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	pBGLayer->addChild(pSpr);

}
void Status::createButton()
{
	pBack = Sprite::create("use_ui/ui_23.png");
	pBack->setPosition(Vec2(winSize.width - 20, winSize.height - 20));
	pBack->setScale(0.3f);
	pBTLayer->addChild(pBack, 2);

	pBackP = Sprite::create("use_ui/ui_24.png");
	pBackP->setPosition(Vec2(winSize.width - 20, winSize.height - 20));
	pBackP->setScale(0.3f);
	pBTLayer->addChild(pBackP, 1);
}
void Status::onEnter()
{
	Scene::onEnter();

	pListener = EventListenerTouchAllAtOnce::create();

	pListener->onTouchesBegan = CC_CALLBACK_2(Status::onTouchesBegan, this);
	pListener->onTouchesMoved = CC_CALLBACK_2(Status::onTouchesMoved, this);
	pListener->onTouchesEnded = CC_CALLBACK_2(Status::onTouchesEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
}

void Status::onExit()
{
	_eventDispatcher->removeEventListener(pListener);

	Scene::onExit();
}

bool Status::isTouchInside(cocos2d::Sprite *pSprite, cocos2d::Touch * pTouch)
{
	auto touchPoint = pTouch->getLocation();
	bool isTouch = pSprite->getBoundingBox().containsPoint(touchPoint);
	return isTouch;
}
bool Status::onTouchesBegan(const vector<Touch*>& pTouches, Event * pEvent)
{
	auto pTouch = pTouches[0];

	isBackP = false;

	if (this->isTouchInside(pBack, pTouch) == true)
	{
		pBack->setVisible(false);
		isBackP = true;
	}

	return true;
}
void Status::onTouchesMoved(const vector<Touch*>& pTouches, Event * pEvent)
{
}
void Status::onTouchesEnded(const vector<Touch*>& pTouches, Event * pEvent)
{
	auto pTouch = pTouches[0];

	if (isBackP && !isTouchInside(pBack, pTouch) == false)
	{
		pBack->setVisible(true);
		auto pScene = MainScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}

	if (isBackP)
	{
		pBack->setVisible(true);
	}
}
