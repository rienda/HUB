#include "MainScene.h"
#include "Story.h"
#include "PuzzleBattle.h"
#include "GameMain.h"
Scene * Story::createScene()
{
	return Story::create();
}
bool Story::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto pLayer = LayerColor::create(Color4B(199, 196, 255, 255));
	this->addChild(pLayer);


	winSize = Director::getInstance()->getWinSize();

	////////////////////////////////////////////////
	// 메뉴 아이템 생성 및 초기화
	auto pItem1 = MenuItemFont::create(
		"돌아가기", CC_CALLBACK_1(Story::doClose, this));
	pItem1->setColor(Color3B::BLACK);
	
	auto pItem2 = MenuItemFont::create(
		"배틀시작", CC_CALLBACK_1(Story::doPuzBattle, this));
	pItem2->setColor(Color3B::BLACK);

	// 메뉴 생성
	auto pMenu = Menu::create(pItem1, pItem2, nullptr);
	pMenu->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	pMenu->alignItemsVertically();
	this->addChild(pMenu);
	return true;
}
void Story::doClose(Ref * pSender)
{
	//// popScene해서 이전 화면으로 돌아감
	//Director::getInstance()->popScene();

	auto pScene = MainScene::createScene();
	Director::getInstance()->replaceScene(pScene); // replace 재배치, pScene으로 바꿔줌
}

void Story::doPuzBattle(Ref * pSender)
{
	auto pScene = GameMain::createScene();
	Director::getInstance()->replaceScene(pScene);
}
