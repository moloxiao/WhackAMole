#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_


#include "cocos2d.h"
#include "TopMenu.h"

using namespace cocos2d;

class GameLayer : public Layer{
	
public:
	static const int DEFAULT_GAME_TIME = 20;
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void randomPopMoles(float delta);
    void setHit(Ref* pSender);	// 设置可以敲打地鼠
    void unHit(Ref* pSender);	// 设置不可以敲打地鼠
	void toResultScene();
	void updateGameTime(float delta);
private:
	Vector<Sprite*> _mousesVector;
	TopMenu* menu;
	int gameTime;	// 游戏结束时间
	bool gamePause;
	bool gameOver;
};
#endif