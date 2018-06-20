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
	// �޴� ������ ���� �� �ʱ�ȭ
	auto pItem = MenuItemFont::create(
		"���ư���", CC_CALLBACK_1(Friend::doClose, this));
	pItem->setColor(Color3B::BLACK);
	// �޴� ����
	auto pMenu = Menu::create(pItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);
	return true;
}
void Friend::doClose(Ref * pSender)
{
	auto pScene = MainScene::createScene();
	Director::getInstance()->replaceScene(pScene); // replace ���ġ, pScene���� �ٲ���
}
