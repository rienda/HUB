#ifndef __GAME_MAIN_H__
#define __GAME_MAIN_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "GamePuzzle.h"

USING_NS_CC;

using namespace std;

class GameMain : public cocos2d::Scene
{
public:
	enum {
		BOARDX = 7,
		BOARDY = 6,
		TOTALPUZTYPE = 4,
		TOTALADJPUZ = 6	// 터치한 퍼즐에 인접한 퍼즐 갯수
	};

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(GameMain);

	Size winSize;

	ProgressTimer* _progressTimeBar;

	Array* _gamePuzzles;
	vector<Vec2> _gamePuzs;
	Array* _selectMask;
	Array* _selectPuzzles;

	int _selectPuzCount;
	int _lineDeadPuzzle[BOARDX];

	Layer *BGLayer;

	Sprite *pEnemy;
	Sprite *pAtkdEnemy;

	int _lastPuzzle;
	static int _adjPuzzle[BOARDX * BOARDY][TOTALADJPUZ];

	int _score;
	int _enemyHp;
	int _atkScore;
	int _gameTime;

	Label *_scoreFont;
	Label *_enemyHpFont;

	Label *pCompleteLabel;
	Label *pFailedLabel;

	EventListenerTouchAllAtOnce *pListener;

	~GameMain();

	void initGameScene();
	void addAction(Sprite *pSpr);

	void addAtkdAction(Sprite *pSpr);

	void initGamePuzzle();
	GamePuzzle* createGamePuzzle(const Point &pos, int type, int state);

	void onEnter();
	void onExit(); 

	bool isTouchInside(Sprite *pSpr, Touch *pTouch);

	bool onTouchesBegan(const vector<Touch *> &pTouches, Event *pEvent);
	void onTouchesMoved(const vector<Touch *> &pTouches, Event *pEvent);
	void onTouchesEnded(const vector<Touch *> &pTouches, Event *pEvent);

	int checkPushGamePuz(Point &touchPos);

	int checkAdjacentPuz(Point &touchPos);
	bool inLastPuz(Point &touchPos);
	int addSelectPuzzles(int index);
	bool comparePuzType(int index1, int index2);

	void clearSelectPuzzle();
	void resetSelectMask();
	void resetGameInfo();

	void moveUpDeadPuzzle();
	void changePuzzle(int index1, int index2);

	void movePuzzle(GamePuzzle* puz, Point& pos);
	void PuzMoveDone(Node* pSender);

	void addNewPuzzle();
	void setNewPuzzle(GamePuzzle* Puz);
	void addNewPuzzleAction();

	void addScore(int deadPuzzleNum);

	void timeCount(float dt);
	void changeToMainScene();
	TransitionScene *transScene(Scene * pScene, float t);

};

#endif // __GAME_MAIN_H__
