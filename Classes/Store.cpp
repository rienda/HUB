#include "Store.h"
#include "MainScene.h"
Scene * Store::createScene()
{
	return Store::create();
}
bool Store::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto pLayer = LayerColor::create(Color4B(180, 140, 255, 255));
	this->addChild(pLayer);
	////////////////////////////////////////////////
	// �޴� ������ ���� �� �ʱ�ȭ
	auto pItem = MenuItemFont::create(
		"���ư���", CC_CALLBACK_1(Store::doClose, this));
	pItem->setColor(Color3B::BLACK);
	// �޴� ����
	auto pMenu = Menu::create(pItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);
	return true;
}
void Store::doClose(Ref * pSender)
{
	auto pScene = MainScene::createScene();
	Director::getInstance()->replaceScene(pScene); // replace ���ġ, pScene���� �ٲ���
}

