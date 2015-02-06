#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"
#include "TopMenu.h"

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
	void flowSprite(std::function<void()> callback);
public:
	static bool needAddTime;
	static bool needDoStartGame;
	static bool payResult;
private:
	Vector<Sprite*> _mousesVector;
	TopMenu* menu;
	int gameTime;	// ��Ϸ����ʱ��
	int gameScore;
	int gameScoreAdd;
	int mouseNum;
	int showPayTimes;
	Sprite* blackBg;
	Sprite* flowTitle;
	bool showPay;
};
#endif
