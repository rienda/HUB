#include "GameMain.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

USING_NS_CC;

int GameMain::_adjPuzzle[BOARDX * BOARDY][TOTALADJPUZ] = {
	{ -1, -1,  1,  7,  6, -1 },   // 0, line 1
{ -1, -1,  2,  8,  7,  0 },
{ -1, -1,  3,  9,  8,  1 },
{ -1, -1,  4, 10,  9,  2 },
{ -1, -1,  5, 11, 10,  3 },
{ -1, -1, -1, -1, 11,  4 },
{ -1,  0,  7, 12, -1, -1 },   // 6, line 2
{ 0,  1,  8, 13, 12,  6 },
{ 1,  2,  9, 14, 13,  7 },
{ 2,  3, 10, 15, 14,  8 },
{ 3,  4, 11, 16, 15,  9 },
{ 4,  5, -1, 17, 16, 10 },
{ 6,  7, 13, 19, 18, -1 },   // 12, line 3
{ 7,  8, 14, 20, 19, 12 },
{ 8,  9, 15, 21, 20, 13 },
{ 9, 10, 16, 22, 21, 14 },
{ 10, 11, 17, 23, 22, 15 },
{ 11, -1, -1, -1, 23, 16 },
{ -1, 12, 19, 24, -1, -1 },   // 18, line 4
{ 12, 13, 20, 25, 24, 18 },
{ 13, 14, 21, 26, 25, 19 },
{ 14, 15, 22, 27, 26, 20 },
{ 15, 16, 23, 28, 27, 21 },
{ 16, 17, -1, 29, 28, 22 },
{ 18, 19, 25, 31, 30, -1 },   // 24, line 5
{ 19, 20, 26, 32, 31, 24 },
{ 20, 21, 27, 33, 32, 25 },
{ 21, 22, 28, 34, 33, 26 },
{ 22, 23, 29, 35, 34, 27 },
{ 23, -1, -1, -1, 35, 28 },
{ -1, 24, 31, 36, -1, -1 },   // 30, line 6
{ 24, 25, 32, 37, 36, 30 },
{ 25, 26, 33, 38, 37, 31 },
{ 26, 27, 34, 39, 38, 32 },
{ 27, 28, 35, 40, 39, 33 },
{ 28, 29, -1, 41, 40, 34 },
{ 30, 31, 37, -1, -1, -1 },   // 36, line 7
{ 31, 32, 38, -1, -1, 36 },
{ 32, 33, 39, -1, -1, 37 },
{ 33, 34, 40, -1, -1, 38 },
{ 34, 35, 41, -1, -1, 39 },
{ 35, -1, -1, -1, -1, 40 },
};

Scene* GameMain::createScene()
{
    return GameMain::create();
}

bool GameMain::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	initGameScene();

	this->schedule(schedule_selector(GameMain::timeCount), 1.0f);

    return true;
}

GameMain::~GameMain()
{
	CC_SAFE_RELEASE(_gamePuzzles);
	CC_SAFE_RELEASE(_selectPuzzles);
	CC_SAFE_RELEASE(_selectMask);
}

void GameMain::initGameScene()
{
	winSize = Director::getInstance()->getWinSize();

	BGLayer = Layer::create();
	this->addChild(BGLayer, 1);


	auto pBG1 = Sprite::create("battle/background_2.png");
	pBG1->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.5f));
	pBG1->setScale(1.3f);
	BGLayer->addChild(pBG1);
	
	auto pBG2 = Sprite::create("battle/background_1.png");
	pBG2->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.5f));
	pBG2->setScaleY(0.9f);
	BGLayer->addChild(pBG2,1);

	pEnemy = Sprite::create("battle/witch_2.png");
	pEnemy->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.6f));
	pEnemy->setScale(0.7f);
	//pEnemy->runAction(enemyMove);
	pEnemy->setAnchorPoint(Vec2(0.5f, 0));
	addAction(pEnemy);
	BGLayer->addChild(pEnemy);

	pAtkdEnemy = Sprite::create("battle/witch_4.png");
	pAtkdEnemy->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.6f));
	pAtkdEnemy->setScale(0.7f);
	pAtkdEnemy->setAnchorPoint(Vec2(0.5f, 0));
	addAction(pAtkdEnemy);
	pAtkdEnemy->setVisible(false);
	BGLayer->addChild(pAtkdEnemy);

	initGamePuzzle();


	// font 설정

	TTFConfig ttfConfig1("fonts/SF Slapstick Comic Bold.ttf", 24);

	_scoreFont = Label::createWithTTF(ttfConfig1, "0");
	_scoreFont->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.72f));
	//_scoreFont->setScale(0.3f);
	_scoreFont->setColor(Color3B(255, 100, 100));
	_scoreFont->enableShadow(Color4B::BLACK);
	_scoreFont->setVisible(false);
	BGLayer->addChild(_scoreFont);

	TTFConfig ttfConfig2("fonts/SF Slapstick Comic Bold.ttf", 18);

	_enemyHpFont = Label::createWithTTF(ttfConfig2, "12000 / 12000");
	_enemyHpFont->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.95f));
	_enemyHpFont->setColor(Color3B(255, 204, 51));
	_enemyHpFont->enableShadow(Color4B::BLACK);
	_enemyHpFont->setVisible(true);
	BGLayer->addChild(_enemyHpFont);

	// battle complite / failed

	pCompleteLabel = Label::createWithTTF("Battle Complete!", "fonts/Angelow.ttf", 50);
	pCompleteLabel->setPosition(Vec2(winSize.width * 0.5f, winSize.height*0.5f));
	pCompleteLabel->setColor(Color3B(255, 214, 67));
	pCompleteLabel->setVisible(false);
	this->addChild(pCompleteLabel, 5);

	pFailedLabel = Label::createWithTTF("Failed ...", "fonts/Angelow.ttf", 50);
	pFailedLabel->setPosition(Vec2(winSize.width * 0.5f, winSize.height*0.5f));
	pFailedLabel->setColor(Color3B(155, 155, 155));
	pFailedLabel->setVisible(false);
	this->addChild(pFailedLabel, 5);


	// progressTimer 설정

	Sprite* timeBar = Sprite::create("battle_ui/timebar.png");
	_progressTimeBar = ProgressTimer::create(timeBar);
	_progressTimeBar->setPosition(Vec2(winSize.width * 0.5f, winSize.height*0.02f));
	_progressTimeBar->setPercentage(100.0f);
	_progressTimeBar->setMidpoint(Vec2(0, 0.5f));
	_progressTimeBar->setBarChangeRate(Vec2(1, 0));
	_progressTimeBar->setType(kCCProgressTimerTypeBar);
	_progressTimeBar->setScale(0.4f);
	BGLayer->addChild(_progressTimeBar,4);

	ProgressFromTo* progressToZero = ProgressFromTo::create(60, 100, 0);
	_progressTimeBar->runAction(progressToZero);

	Sprite* timeOutline = Sprite::create("battle_ui/timeoutline.png");
	timeOutline->setPosition(Vec2(winSize.width * 0.5f, winSize.height*0.02f));
	timeOutline->setScale(0.4f);
	timeOutline->setVisible(true);
	BGLayer->addChild(timeOutline, 4);
}

void GameMain::addAction(Sprite *pSpr)
{
	auto pEnemyAct = Sequence::create(
		EaseInOut::create(MoveBy::create(1.2f, Vec2(10, 0)), 2),
		EaseInOut::create(MoveBy::create(1.2f, Vec2(-10, 0)), 2),
		EaseInOut::create(MoveBy::create(1.2f, Vec2(-10, 0)), 2),
		EaseInOut::create(MoveBy::create(1.2f, Vec2(10, 0)), 2),nullptr);

	auto enemyMove = RepeatForever::create(pEnemyAct);

	pSpr->runAction(enemyMove);

}

void GameMain::addAtkdAction(Sprite * pSpr)
{
	if (pSpr == pAtkdEnemy)
	{
		pAtkdEnemy->setVisible(true);
		auto pEnemyAct = Sequence::create(
			FadeIn::create(0.1f),
			EaseInOut::create(MoveBy::create(0.2f, Vec2(0, 10)), 0.2f),
			EaseInOut::create(MoveBy::create(0.2f, Vec2(0, -10)), 0.2f),
			FadeOut::create(0.1f), nullptr);

		pSpr->runAction(pEnemyAct);
	}
	else
	{
		auto pEnemyAct = Sequence::create(
			EaseInOut::create(MoveBy::create(0.2f, Vec2(0, 10)), 0.2f),
			EaseInOut::create(MoveBy::create(0.2f, Vec2(0, -10)), 0.2f), nullptr);

		pSpr->runAction(pEnemyAct);
	}
}
 
void GameMain::initGamePuzzle()
{
	//_enemyHp = 12000; test
	_enemyHp = 12000;

	_gameTime = 60;

	_score = 0;

	_selectPuzzles = Array::createWithCapacity(BOARDX * BOARDY);
	_selectPuzzles->retain();

	_selectMask = Array::createWithCapacity(BOARDX * BOARDY);
	_selectMask->retain();

	_lastPuzzle = -1;
	_selectPuzCount = 0;

	int PuzzleXPos = 0;
	int PuzzleYPos = 0;
	/*int diffX = 104;
	int diffY = 120;
	int initPuzzleXPos = 72;
	int initPuzzleYPos = 778;*/

	int diffX = 43;
	int diffY = 45;
	int initPuzzleXPos = 31;
	int initPuzzleYPos = 291;


	GamePuzzle* gamePuzzle;

	// init array
	_gamePuzzles = Array::createWithCapacity(BOARDX * BOARDY);
	_gamePuzzles->retain();

	_gamePuzs.resize(BOARDX*BOARDY);

	srand((int)time(nullptr));

	// init gameCoin
	for (int xIndex = 0; xIndex < BOARDX; xIndex++) {
		PuzzleXPos = initPuzzleXPos + (xIndex * diffX);
		PuzzleYPos = initPuzzleYPos;
		if (xIndex % 2 == 0)
			PuzzleYPos -= diffY / 2;

		for (int yIndex = 0; yIndex < BOARDY; yIndex++) {
			gamePuzzle = createGamePuzzle(Vec2(PuzzleXPos, PuzzleYPos),
				rand() % TOTALPUZTYPE + 1,
				GamePuzzle::LIVE);

			_gamePuzzles->addObject(gamePuzzle);

			PuzzleYPos -= diffY;
		}
	}

	// selectMask setup
	//Sprite* selectMask;

	for (int xIndex = 0; xIndex < BOARDX; xIndex++) {
		PuzzleXPos = initPuzzleXPos + (xIndex * diffX);
		PuzzleYPos = initPuzzleYPos;
		if (xIndex % 2 == 0)
			PuzzleYPos -= diffY / 2;

		for (int yIndex = 0; yIndex < BOARDY; yIndex++) {
			auto selectMask = Sprite::create("puzs/selectPuz.png");
			selectMask->setVisible(false);
			selectMask->setPosition(Vec2(PuzzleXPos, PuzzleYPos));
			selectMask->setScale(0.35f);
			this->addChild(selectMask, 3);
			_selectMask->addObject(selectMask);

			PuzzleYPos -= diffY;
		}
	}
}

GamePuzzle * GameMain::createGamePuzzle(const Point & pos, int type, int state)
{
	GamePuzzle* gamePuzzle;
	String* name;

	name = String::createWithFormat("puzs/puzzle_0%d.png", type);
	gamePuzzle = GamePuzzle::sprWithFile(name->getCString());
	gamePuzzle->setVisible(true);
	gamePuzzle->setPosition(pos);
	gamePuzzle->setState(state);
	gamePuzzle->setType(type);
	gamePuzzle->setScale(0.6f);

	this->addChild(gamePuzzle, 2);

	return gamePuzzle;
}

void GameMain::onEnter()
{
	Scene::onEnter();

	pListener = EventListenerTouchAllAtOnce::create();

	pListener->onTouchesBegan = CC_CALLBACK_2(GameMain::onTouchesBegan, this);
	pListener->onTouchesMoved = CC_CALLBACK_2(GameMain::onTouchesMoved, this);
	pListener->onTouchesEnded = CC_CALLBACK_2(GameMain::onTouchesEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
}

void GameMain::onExit()
{

	Scene::onExit();
}

bool GameMain::isTouchInside(Sprite * pSpr, Touch * pTouch)
{
	return true;
}

bool GameMain::onTouchesBegan(const vector<Touch*>& pTouches, Event * pEvent)
{
	//for (auto touch = pTouches.begin(); touch != pTouches.end(); touch++)
	//{
	auto touch = pTouches.begin();

	auto touchPoint = (*touch)->getLocation();

	_lastPuzzle = checkPushGamePuz(touchPoint);

	if (_lastPuzzle >= 0) {
		addSelectPuzzles(_lastPuzzle);
	}

	if (_enemyHp <= 0)
	{
		if (BGLayer->getBoundingBox().containsPoint(touchPoint) == true)
		{
			changeToMainScene();
		}
	}
	else if (_gameTime == 0)
	{
		if (BGLayer->getBoundingBox().containsPoint(touchPoint) == true)
		{
			changeToMainScene();
		}
	}

	return true;
}

void GameMain::onTouchesMoved(const vector<Touch*>& pTouches, Event * pEvent)
{
	for (auto touch = pTouches.begin(); touch != pTouches.end(); touch++)
	{
		auto touchPoint = (*touch)->getLocation();
		
		int newCoin = -1;

		if (inLastPuz(touchPoint) == false) {
			newCoin = checkAdjacentPuz(touchPoint);

			if (comparePuzType(_lastPuzzle, newCoin)) {
				_lastPuzzle = newCoin;
				addSelectPuzzles(_lastPuzzle);
			}
		}
	}

}

void GameMain::onTouchesEnded(const vector<Touch*>& pTouches, Event * pEvent)
{
	Point touchPoint;

	for (auto touch = pTouches.begin(); touch != pTouches.end(); touch++)
	{
		touchPoint = (*touch)->getLocation();
	}


	clearSelectPuzzle();
	moveUpDeadPuzzle();
	addNewPuzzle();

	if (_enemyHp <= 0)
	{
	}
}

int GameMain::checkPushGamePuz(Point & touchPos)
{
	int index;
	GamePuzzle *tmpPuzzle;

	for (index = 0; index < _gamePuzzles->count(); index++) {
		tmpPuzzle = (GamePuzzle*)_gamePuzzles->objectAtIndex(index);
		if (tmpPuzzle->getBoundingBox().containsPoint(touchPos) == true) {
			/*if (tmpPuzzle->isVisible() == true)
				tmpPuzzle->setVisible(false);
			else
				tmpPuzzle->setVisible(true);*/

			return index;
		}
	}

	return -1;
}

int GameMain::checkAdjacentPuz(Point & touchPos)
{
	int index;
	GamePuzzle* tmpPuzzle;

	if (_lastPuzzle < 0)
		return -1;

	for (index = 0; index < 6; index++) {
		if (_adjPuzzle[_lastPuzzle][index] == -1) {
			continue;
		}
		tmpPuzzle = (GamePuzzle*)_gamePuzzles->objectAtIndex(_adjPuzzle[_lastPuzzle][index]);

		if (tmpPuzzle->getBoundingBox().containsPoint(touchPos) == true) {
			return _adjPuzzle[_lastPuzzle][index];
		}
	}
	return -1;
}

bool GameMain::inLastPuz(Point & touchPos)
{
	if (_lastPuzzle == -1) {
		return false;
	}

	GamePuzzle* lastPuzzle = (GamePuzzle*)_gamePuzzles->objectAtIndex(_lastPuzzle);

	if (lastPuzzle->getBoundingBox().containsPoint(touchPos) == true) {
		return true;
	}
	return false;
}

int GameMain::addSelectPuzzles(int index)
{
	if (index < 0) {
		return -1;
	}

	GamePuzzle* tmpPuzzle = (GamePuzzle*)_gamePuzzles->objectAtIndex(index);
	Sprite* selectMask = (Sprite*)_selectMask->objectAtIndex(index);

	if (tmpPuzzle->getState() != GamePuzzle::SELECT) {
		tmpPuzzle->setState(GamePuzzle::SELECT);
		_selectPuzzles->addObject(tmpPuzzle);

		selectMask->setVisible(true);
	}

	_selectPuzCount += 1;

	return 0;
}

bool GameMain::comparePuzType(int index1, int index2)
{
	if (index1 < 0 || index2 < 0)
		return false;

	GamePuzzle* tmpPuzzle1 = (GamePuzzle*)_gamePuzzles->objectAtIndex(index1);
	GamePuzzle* tmpPuzzle2 = (GamePuzzle*)_gamePuzzles->objectAtIndex(index2);

	if (tmpPuzzle1->getType() == tmpPuzzle2->getType()) {
		return true;
	}
	return false;
}

void GameMain::clearSelectPuzzle()
{
	int index;
	GamePuzzle* tmpPuzzle;

	if (_selectPuzCount >= 3) {
		addScore(_selectPuzCount);

		for (index = 0; index < _selectPuzzles->count(); index++) {
			tmpPuzzle = (GamePuzzle*)_selectPuzzles->objectAtIndex(index);
			tmpPuzzle->setState(GamePuzzle::DEAD);
			tmpPuzzle->setVisible(false);
		}
	}
	else {
		for (index = 0; index < _selectPuzzles->count(); index++) {
			tmpPuzzle = (GamePuzzle*)_selectPuzzles->objectAtIndex(index);
			tmpPuzzle->setState(GamePuzzle::LIVE);
		}
	}
	resetSelectMask();
	resetGameInfo();
}

void GameMain::resetSelectMask()
{
	Sprite* selectMask;

	for (int i = 0; i < _selectMask->count(); i++) {
		selectMask = (Sprite*)_selectMask->objectAtIndex(i);
		selectMask->setVisible(false);
	}
}

void GameMain::resetGameInfo()
{
	_selectPuzCount = 0;
	_lastPuzzle = -1;

	_selectPuzzles->removeAllObjects();
}

void GameMain::moveUpDeadPuzzle()
{
	/*
	- int deadPuzNum : 내 밑의 DEAD 상태의 퍼즐 수
	- int bottomPos : 현재 라인의 제일 밑의 Position
	- GamePuzzle* puzzle : 현재 퍼즐의 정보 확인을 위해
	*/
	int deadPuzNum = 0;
	int bottomPos = 0;
	GamePuzzle* puzzle;

	for (int x = 0; x < BOARDX; x++) {
		bottomPos = ((x + 1) * BOARDY) - 1;
		deadPuzNum = 0;

		for (int y = bottomPos; y > bottomPos - BOARDY; y--) {
			puzzle = (GamePuzzle*)_gamePuzzles->objectAtIndex(y);
			if (puzzle->getState() == GamePuzzle::DEAD) {
				deadPuzNum++;
				continue;
			}

			if (deadPuzNum > 0)
				changePuzzle(y, y + deadPuzNum);
		}
	}
}

void GameMain::changePuzzle(int index1, int index2)
{
	Point tmpPos;
	GamePuzzle* tmpPuz1 = (GamePuzzle*)_gamePuzzles->objectAtIndex(index1);
	GamePuzzle* tmpPuz2 = (GamePuzzle*)_gamePuzzles->objectAtIndex(index2);

	tmpPos = tmpPuz2->getPosition();
	tmpPuz2->setPosition(tmpPuz1->getPosition());
	//tmpPuz1->setPosition(tmpPos);

	movePuzzle(tmpPuz1, tmpPos);

	_gamePuzzles->exchangeObjectAtIndex(index1, index2);
}

void GameMain::movePuzzle(GamePuzzle * puz, Point & pos)
{
	float duration = 0.0f;
	float coinSpeed = 1000.0f;
	Point prevPos = puz->getPosition();
	puz->setState(GamePuzzle::MOVE);
	puz->stopAllActions();

	duration = prevPos.getDistance(pos) / coinSpeed;

	auto movePos = Sequence::create(
		MoveTo::create(duration, pos),
		CallFuncN::create(this, callfuncN_selector(GameMain::PuzMoveDone)), NULL);

	puz->runAction(movePos);
}

void GameMain::PuzMoveDone(Node * pSender)
{
	GamePuzzle* puzzle = (GamePuzzle*)pSender;

	puzzle->stopAllActions();
	puzzle->setState(GamePuzzle::LIVE);
}

void GameMain::addNewPuzzle()
{
	GamePuzzle* puzzle;
	int line = 0;

	for (int i = 0; i < BOARDX; i++)
	{
		_lineDeadPuzzle[i] = 0;
	}
	for (int i = 0; i < _gamePuzzles->count(); i++)
	{
		puzzle = (GamePuzzle*)_gamePuzzles->objectAtIndex(i);

		if (puzzle->getState() == GamePuzzle::DEAD)
		{
			line = (int)(i / BOARDY);
			_lineDeadPuzzle[line] += 1;

			setNewPuzzle(puzzle);
		}
	}

	addNewPuzzleAction();

}

void GameMain::setNewPuzzle(GamePuzzle * Puz)
{
	char name[100] = "";
	Texture2D* tex;
	int puzzleType = rand() % TOTALPUZTYPE + 1;

	sprintf(name, "puzs/puzzle_0%d.png", puzzleType);
	tex = TextureCache::sharedTextureCache()->addImage(name);

	Puz->setTexture(tex);
	Puz->setVisible(true);
	Puz->setType(puzzleType);
	Puz->setState(GamePuzzle::LIVE);

	//addNewPuzzleAction();
}

void GameMain::addNewPuzzleAction()
{
	GamePuzzle* puzzle;
	Vec2 pos;
	int startIndex;
	int diffY = 45;

	for (int i = 0; i < BOARDX; i++) {
		if (_lineDeadPuzzle[i] > 0) {
			startIndex = i * BOARDY;

			for (int j = startIndex; j < startIndex + _lineDeadPuzzle[i]; j++) {
				puzzle = (GamePuzzle*)_gamePuzzles->objectAtIndex(j);
				pos = puzzle->getPosition();
				puzzle->setPosition(Vec2(pos.x, pos.y + (_lineDeadPuzzle[i] * diffY)));

				movePuzzle(puzzle, pos);
			}
		}
	}
}

void GameMain::addScore(int deadPuzzleNum)
{
	char score[100] = { 0, };
	char enemyHp[100] = { 0, };

	_atkScore = 0;

	_score += (deadPuzzleNum * 100);
	_atkScore += (deadPuzzleNum * 100);

	_enemyHp -= (deadPuzzleNum * 100);
	if (_enemyHp <= 0)
	{
		_enemyHp = 0;
	}

	sprintf(enemyHp, "%i / 12000", _enemyHp);
	_enemyHpFont->setString(enemyHp);

	sprintf(score, "%i", _atkScore);
	_scoreFont->setString(score);

	_scoreFont->setVisible(true);

	auto fontAction = Sequence::create(FadeIn::create(0.05f),
		ScaleTo::create(0.1f, 1.5f),ScaleTo::create(0.2f, 1.0f),
		DelayTime::create(0.1f) ,FadeOut::create(0.2f), nullptr);
	auto pRepFA = RepeatForever::create(fontAction);
	_scoreFont->runAction(fontAction);

	addAtkdAction(pEnemy);
	addAtkdAction(pAtkdEnemy);
}

void GameMain::timeCount(float dt)
{
	if (--_gameTime == 0) {

		pFailedLabel->setVisible(true);

		//changeToMainScene();
	}

	if (_enemyHp <= 0)
	{
		//pEnemy->setVisible(false);

		_progressTimeBar->cleanup();

		pAtkdEnemy->setVisible(false);

		auto pRemoveAct = FadeOut::create(0.5f);
		pEnemy->runAction(pRemoveAct);


		pCompleteLabel->setVisible(true);
		//changeToMainScene();
	}
}


void GameMain::changeToMainScene()
{
	auto *pScene = MainScene::createScene();

	Director::getInstance()->replaceScene(transScene(pScene, 1.0f));
}

TransitionScene * GameMain::transScene(Scene * pScene, float t)
{
	Director::getInstance()->setDepthTest(false);

	return TransitionFade::create(t, pScene);

	return nullptr;
}