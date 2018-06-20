#include "Family.h"
#include "MainScene.h"
Scene * Family::createScene()
{
	return Family::create();
}
bool Family::init()
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
		"���ư���", CC_CALLBACK_1(Family::doClose, this));
	pItem->setColor(Color3B::BLACK);
	// �޴� ����
	auto pMenu = Menu::create(pItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);
	return true;
}
void Family::doClose(Ref * pSender)
{
	auto pScene = MainScene::createScene();
	Director::getInstance()->replaceScene(pScene); // replace ���ġ, pScene���� �ٲ���
}

