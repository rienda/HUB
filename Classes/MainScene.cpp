#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "Family.h"
#include "Story.h"
#include "PuzzleBattle.h"
#include "GameMain.h"
#include "Friend.h"
#include "Store.h"
#include "Status.h"


Scene* MainScene::createScene()
{
    return MainScene::create();
}

bool MainScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	/*auto wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(wlayer);*/

	MenuItemFont::setFontSize(24);

	createBG();

	createButton();

    return true;
}


void MainScene::createBG()
{
	winSize = Director::getInstance()->getWinSize();

	pBGLayer = Layer::create();
	this->addChild(pBGLayer);

	pBTLayer = Layer::create();
	this->addChild(pBTLayer);

	auto pSpr = Sprite::create("Images/bg_castle.png");
	pSpr->setScale(0.8f);
	pSpr->setPosition(Vec2(winSize.width/2, winSize.height/2));
	pBGLayer->addChild(pSpr);

	/*auto pLabel = Label::createWithTTF("Touch to start", "fonts/Angelow.ttf", 30);
	pLabel->setPosition(Vec2(winSize.width * 0.5f, winSize.height*0.3f));
	pBGLayer->addChild(pLabel);

	auto fontAction = Sequence::create(FadeOut::create(1.5f), FadeIn::create(1.5f), nullptr);
	auto pRepFA = RepeatForever::create(fontAction);
	pLabel->runAction(pRepFA);*/
}

void MainScene::createButton()
{
	pStatus = Sprite::create("use_ui/ui_33.png");
	pStatus->setPosition(Vec2(winSize.width/6, 20));
	pStatus->setScale(0.4f);
	pBTLayer->addChild(pStatus, 2);

	pStatusP = Sprite::create("use_ui/ui_36.png");
	pStatusP->setPosition(pStatus->getPosition());
	pStatusP->setScale(0.4f);
	pBTLayer->addChild(pStatusP, 1);

	pFamily = Sprite::create("use_ui/ui_41.png");
	pFamily->setPosition(Vec2((winSize.width / 6)*2, 20));
	pFamily->setScale(0.4f);
	pBTLayer->addChild(pFamily, 2);

	pFamilyP = Sprite::create("use_ui/ui_44.png");
	pFamilyP->setPosition(pFamily->getPosition());
	pFamilyP->setScale(0.4f);
	pBTLayer->addChild(pFamilyP, 1);

	pStory = Sprite::create("use_ui/ui_69.png");
	pStory->setPosition(Vec2((winSize.width / 6)*3, 20));
	pStory->setScale(0.4f);
	pBTLayer->addChild(pStory, 2);

	pStoryP = Sprite::create("use_ui/ui_72.png");
	pStoryP->setPosition(pStory->getPosition());
	pStoryP->setScale(0.4f);
	pBTLayer->addChild(pStoryP, 1);

	pStore = Sprite::create("use_ui/ui_57.png");
	pStore->setPosition(Vec2((winSize.width / 6) * 4, 20));
	pStore->setScale(0.4f);
	pBTLayer->addChild(pStore, 2);

	pStoreP = Sprite::create("use_ui/ui_60.png");
	pStoreP->setPosition(pStore->getPosition());
	pStoreP->setScale(0.4f);
	pBTLayer->addChild(pStoreP, 1);

	pFriend = Sprite::create("use_ui/ui_45.png");
	pFriend->setPosition(Vec2((winSize.width / 6) * 5, 20));
	pFriend->setScale(0.4f);
	pBTLayer->addChild(pFriend, 2);

	pFriendP = Sprite::create("use_ui/ui_48.png");
	pFriendP->setPosition(pFriend->getPosition());
	pFriendP->setScale(0.4f);
	pBTLayer->addChild(pFriendP, 1);
}

void MainScene::onEnter()
{
	Scene::onEnter();

	pListener = EventListenerTouchAllAtOnce::create();
	
	pListener->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
	pListener->onTouchesMoved = CC_CALLBACK_2(MainScene::onTouchesMoved, this);
	pListener->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
}

void MainScene::onExit()
{
	_eventDispatcher->removeEventListener(pListener);

	Scene::onExit();
}

bool MainScene::isTouchInside(cocos2d::Sprite *pSprite, cocos2d::Touch * pTouch)
{
	auto touchPoint = pTouch->getLocation();
	bool isTouch = pSprite->getBoundingBox().containsPoint(touchPoint);
	return isTouch;
}


bool MainScene::onTouchesBegan(const vector<Touch *> &pTouches, cocos2d::Event * pEvent)
{
	auto pTouch = pTouches[0];

	isStatusP = false;
	isFamilyP = false;
	isStoryP = false;
	isStoreP = false;
	isFriendP = false;

	if (this->isTouchInside(pStatus, pTouch) == true)
	{
		pStatus->setVisible(false);
		isStatusP = true;
	}
	else if (this->isTouchInside(pFamily, pTouch) == true)
	{
		pFamily->setVisible(false);
		isFamilyP = true;
	}
	else if (this->isTouchInside(pStory, pTouch) == true)
	{
		pStory->setVisible(false);
		isStoryP = true;
	}
	else if (this->isTouchInside(pStore, pTouch) == true)
	{
		pStore->setVisible(false);
		isStoreP = true;
	}
	else if (this->isTouchInside(pFriend, pTouch) == true)
	{
		pFriend->setVisible(false);
		isFriendP = true;
	}

	return true;
}

void MainScene::onTouchesMoved(const vector<Touch *> &pTouches, cocos2d::Event * pEvent)
{

}

void MainScene::onTouchesEnded(const vector<Touch *> &pTouches, cocos2d::Event * pEvent)
{
	auto pTouch = pTouches[0];

	if (isStatusP && !isTouchInside(pStatus, pTouch) == false)
	{
		pStatus->setVisible(true);
		auto pScene = Status::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	else if (isFamilyP && !isTouchInside(pFamily, pTouch) == false)
	{
		pFamily->setVisible(true);
		auto pScene = Family::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	else if (isStoryP && !isTouchInside(pStory, pTouch) == false)
	{
		//auto pScene = Story::createScene();
		//Director::getInstance()->pushScene(pScene);//HelloWorld 씬이 아래에 있음
		pStory->setVisible(true);
		auto pScene = GameMain::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	else if (isStoreP && !isTouchInside(pStore, pTouch) == false)
	{
		pStore->setVisible(true);
		auto pScene = Store::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	else if (isFriendP && !isTouchInside(pFriend, pTouch) == false)
	{
		pFriend->setVisible(true);
		auto pScene = Friend::createScene();
		Director::getInstance()->replaceScene(pScene);
	}

	if (isStatusP)
	{
		pStatus->setVisible(true);
	}
	else if(isFamilyP)
	{
		pFamily->setVisible(true);
	}
	else if (isStoryP)
	{
		pStory->setVisible(true);
	}
	else if (isStoreP)
	{
		pStore->setVisible(true);
	}
	else if (isFriendP)
	{
		pFriend->setVisible(true);
	}
}
