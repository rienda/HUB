#include "PuzzleBattle.h"
#include "MainScene.h"
#include "Story.h"
Scene * PuzzleBattle::createScene()
{
	return PuzzleBattle::create();
}
bool PuzzleBattle::init()
{
	if (!Scene::init())
	{
		return false;
	}

	InitBG();

	// 메뉴 아이템 생성 및 초기화
	auto pItem = MenuItemFont::create(
		"돌아가기", CC_CALLBACK_1(PuzzleBattle::doClose, this));
	pItem->setColor(Color3B::BLACK);
	// 메뉴 생성
	auto pMenu = Menu::create(pItem, nullptr);
	pMenu->setPosition(Vec2(winSize.width/2, winSize.height - 400));
	this->addChild(pMenu);
	return true;
}
void PuzzleBattle::InitBG()
{
	winSize = Director::getInstance()->getWinSize();
	pBGLayer = Layer::create();
	this->addChild(pBGLayer);

	auto pBgSp = Sprite::create("battle_ui/background_01.png");
	pBGLayer->setPosition(Vec2(winSize.width *0.5f, winSize.height *0.5f));
	//pBgSp->setScaleX();
	pBgSp->setScaleY(0.9f);
	pBGLayer->addChild(pBgSp, 1);
	
	InitBT();
	//InitPuzInfo();
	InitEnemyInfo();
}
void PuzzleBattle::InitBT()
{
	// 배틀 하고나서 이후에 하기
	pBTLayer = Layer::create();
	this->addChild(pBTLayer, 2);

}
void PuzzleBattle::InitUserInfo()
{
}
void PuzzleBattle::InitEnemyInfo()
{
	auto pEnemy = Sprite::create("battle_ui/enemy_03.png");
	pEnemy->setScale(0.8f);
	pEnemy->setPosition(Vec2(winSize.width*0.5f, winSize.height * 0.85f));
	InitEnemyAction(*pEnemy);
	this->addChild(pEnemy, 2);
}

void PuzzleBattle::InitEnemyAction(Sprite &pEnemy)
{
	if (!&pEnemy)
	{
		return;
	}

	auto ptEnemy = (Sprite*)&pEnemy;
	
	auto pRot1 = RotateTo::create(1.5, 10);
	auto pRot2 = RotateTo::create(1.5, 350);
	auto pSeq = Sequence::create(
		pRot1, DelayTime::create(0.5),
		pRot2, DelayTime::create(0.5),
		nullptr
	);
	auto pRep = RepeatForever::create(pSeq);
	ptEnemy->runAction(pRep);
}

void PuzzleBattle::InitPuzInfo()
{
	srand(time(NULL));
	for (int i = 0; i < CULUMN_COUNT; i++)
	{
		for (int j = 0; j < ROW_COUNT; j++)
		{
			int type = rand() % 5;

			pBlock = Sprite::create("battle_ui/block.png");
			pBlock->setPosition(Vec2((winSize.width / 9)*(i + 1), (winSize.height / 12)*(j + 2) - 10));
			pBlock->setScale(0.08f);
			pBlock->setColor(Color3B(199, 196, 255));
			this->addChild(pBlock, 3);

	 		Sprite *pPuz = Sprite::create(puzType[type]);
			pPuz->setPosition(Vec2((winSize.width / 9)*(i+1), (winSize.height / 12)*(j + 2)-10));
			//pPuz->setAnchorPoint(Vec2::ZERO);
			//pPuz->setPosition(pBlock->getPosition());
			pPuz->setScale(0.35f);
			//pPuz->setScale(1.5f);
			this->addChild(pPuz, 4);
			puzBox[i][j] = pPuz;
		}
	}

}

void PuzzleBattle::onEnter()
{
	Scene::onEnter();

	pListener = EventListenerTouchAllAtOnce::create();

	pListener->onTouchesBegan = CC_CALLBACK_2(PuzzleBattle::onTouchesBegan, this);
	pListener->onTouchesMoved = CC_CALLBACK_2(PuzzleBattle::onTouchesMoved, this);
	pListener->onTouchesEnded = CC_CALLBACK_2(PuzzleBattle::onTouchesEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
}
void PuzzleBattle::onExit()
{
	_eventDispatcher->removeEventListener(pListener);

	Scene::onExit();
}

bool PuzzleBattle::isTouchInside(cocos2d::Sprite *pSprite, cocos2d::Touch * pTouch)
{
	auto touchPoint = pTouch->getLocation();
	bool isTouch = pSprite->getBoundingBox().containsPoint(touchPoint);
	return isTouch;
}
bool PuzzleBattle::onTouchesBegan(const vector<Touch*>& pTouches, Event * pEvent)
{
	auto pTouch = pTouches[0];

	auto Touchpoint = pTouch->getLocation();

	/*Sprite *pClick = Sprite::create("battle_ui/blockBack.png");
	pClick->setPosition(Touchpoint);
	pClick->setScale(0.2f);
	pClick->setOpacity(0.4f);
	this->addChild(pClick, 5);*/

	/*if (isTouchInside(pBlock, pTouch))
	{
		pBlock->setColor(Color3B::BLUE);
		pBlock->setOpacity(125);
	}*/


	return true;
}
void PuzzleBattle::onTouchesMoved(const vector<Touch*>& pTouches, Event * pEvent)
{

	//for (auto p : pTouches)
	//{
	//	//auto pTouch = pTouches[0];
	//	auto Touchpoint = p->getLocation();

	//	pClick = Sprite::create("battle_ui/blockBack.png");
	//	pClick->setPosition(Touchpoint);
	//	pClick->setScale(0.2f);
	//	pClick->setOpacity(125);
	//	this->addChild(pClick, 4);
	//}
}
void PuzzleBattle::onTouchesEnded(const vector<Touch*>& pTouches, Event * pEvent)
{

}

void PuzzleBattle::doClose(Ref * pSender)
{
	auto pScene = Story::createScene();
	Director::getInstance()->replaceScene(pScene); // replace 재배치, pScene으로 바꿔줌
}

