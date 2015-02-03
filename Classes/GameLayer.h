#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"
#include "TopMenu.h"
#include "FloatWord.h"

using namespace cocos2d;

class GameLayer : public Layer{
	
public:
	static const int DEFAULT_GAME_TIME = 20;
	static const int DEFAUL_SCORE_ADD = 100;

	virtual bool init();
	CREATE_FUNC(GameLayer);

	void randomPopMoles(float delta);
    void setHit(Ref* pSender);	// ���ÿ����ô����
    void unHit(Ref* pSender);	// ���ò������ô����
	void toResultScene();
	void updateGameTime(float delta);
	void doStartGame();
	void buyPower(float dt);
	void newPlayerPack(float dt);
public:
	static bool needAddTime;
	static bool needDoStartGame;
private:
	Vector<Sprite*> _mousesVector;
	TopMenu* menu;
	int gameTime;	// ��Ϸ����ʱ��
	int gameScore;
	int gameScoreAdd;
	int mouseNum;
	bool hasShowPay;
	Sprite* blackBg;
	FloatWord* leftStarMsg1;
};
#endif
