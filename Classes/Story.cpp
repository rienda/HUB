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
	// �޴� ������ ���� �� �ʱ�ȭ
	auto pItem1 = MenuItemFont::create(
		"���ư���", CC_CALLBACK_1(Story::doClose, this));
	pItem1->setColor(Color3B::BLACK);
	
	auto pItem2 = MenuItemFont::create(
		"��Ʋ����", CC_CALLBACK_1(Story::doPuzBattle, this));
	pItem2->setColor(Color3B::BLACK);

	// �޴� ����
	auto pMenu = Menu::create(pItem1, pItem2, nullptr);
	pMenu->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	pMenu->alignItemsVertically();
	this->addChild(pMenu);
	return true;
}
void Story::doClose(Ref * pSender)
{
	//// popScene�ؼ� ���� ȭ������ ���ư�
	//Director::getInstance()->popScene();

	auto pScene = MainScene::createScene();
	Director::getInstance()->replaceScene(pScene); // replace ���ġ, pScene���� �ٲ���
}

void Story::doPuzBattle(Ref * pSender)
{
	auto pScene = GameMain::createScene();
	Director::getInstance()->replaceScene(pScene);
}
