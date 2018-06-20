#include "Friend.h"
#include "MainScene.h"
Scene * Friend::createScene()
{
	return Friend::create();
}
bool Friend::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto pLayer = LayerColor::create(Color4B(221,238,255, 255));
	this->addChild(pLayer);
	////////////////////////////////////////////////
	// 메뉴 아이템 생성 및 초기화
	auto pItem = MenuItemFont::create(
		"돌아가기", CC_CALLBACK_1(Friend::doClose, this));
	pItem->setColor(Color3B::BLACK);
	// 메뉴 생성
	auto pMenu = Menu::create(pItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);
	return true;
}
void Friend::doClose(Ref * pSender)
{
	auto pScene = MainScene::createScene();
	Director::getInstance()->replaceScene(pScene); // replace 재배치, pScene으로 바꿔줌
}
