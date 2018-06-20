#include "MainScene.h"
#include "OpeningScene.h"

Scene * OpeningScene::createScene()
{
	return OpeningScene::create();
}
bool OpeningScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	initOpScene();


	return true;

}
void OpeningScene::initOpScene()
{
	winSize = Director::getInstance()->getWinSize();

	pBGLayer = Layer::create();
	this->addChild(pBGLayer);

	auto pSpr = Sprite::create("Images/bg_book.png");
	pSpr->setScale(0.8f);
	pSpr->setPosition(Vec2(winSize.width / 2 + 25, winSize.height / 2 + 40));
	pBGLayer->addChild(pSpr);

	auto pTitleLabel = Label::createWithTTF("H U B", "fonts/Angelow.ttf", 50);
	pTitleLabel->setPosition(Vec2(winSize.width * 0.5f + 10, winSize.height*0.65f));
	pBGLayer->addChild(pTitleLabel);

	auto pTouchLabel = Label::createWithTTF("Touch to start", "fonts/Angelow.ttf", 30);
	pTouchLabel->setPosition(Vec2(winSize.width * 0.5f, winSize.height*0.25f));
	pBGLayer->addChild(pTouchLabel);

	auto sprAction = Sequence::create(
		EaseInOut::create(MoveBy::create(2.0f, Vec2(0, 10)), 2.0f),
		EaseInOut::create(MoveBy::create(2.0f, Vec2(0, -10)), 2.0f),
		nullptr);

	auto pRepSA = RepeatForever::create(sprAction);
	//pSpr->runAction(pRepSA);
	pTitleLabel->runAction(pRepSA);
	
	auto touchFontAction = Sequence::create(FadeOut::create(1.5f), FadeIn::create(1.5f), nullptr);
	auto pRepFA = RepeatForever::create(touchFontAction);
	pTouchLabel->runAction(pRepFA);

}

TransitionScene * OpeningScene::transScene(Scene * pScene, float t)
{
	Director::getInstance()->setDepthTest(false);

	return TransitionFade::create(t, pScene);

	return nullptr;
}
void OpeningScene::onEnter()
{
	Scene::onEnter();

	pListener = EventListenerTouchAllAtOnce::create();

	pListener->onTouchesBegan = CC_CALLBACK_2(OpeningScene::onTouchesBegan, this);
	pListener->onTouchesMoved = CC_CALLBACK_2(OpeningScene::onTouchesMoved, this);
	pListener->onTouchesEnded = CC_CALLBACK_2(OpeningScene::onTouchesEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
}

void OpeningScene::onExit()
{
	_eventDispatcher->removeEventListener(pListener);

	Scene::onExit();
}

bool OpeningScene::isTouchInside(cocos2d::Layer *pLayer, cocos2d::Touch * pTouch)
{
	auto touchPoint = pTouch->getLocation();
	bool isTouch = pLayer->getBoundingBox().containsPoint(touchPoint);
	return isTouch;
}
bool OpeningScene::onTouchesBegan(const vector<Touch*>& pTouches, Event * pEvent)
{
	auto touch = pTouches.begin();

	auto touchPoint = (*touch)->getLocation();
	if (this->getBoundingBox().containsPoint(touchPoint) == true)
	{
		//pSprite->setVisible(true);
		auto pScene = MainScene::createScene();
		Director::getInstance()->replaceScene(transScene(pScene, 1.5));
	}

	return true;
}
void OpeningScene::onTouchesMoved(const vector<Touch*>& pTouches, Event * pEvent)
{
}
void OpeningScene::onTouchesEnded(const vector<Touch*>& pTouches, Event * pEvent)
{

}

