#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include "cocos2d.h"
#include "SignIn.h"

using namespace cocos2d;

class MenuLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(MenuLayer);
	void startGame();
	void autoStartGame(float dt);
	void showAbout();
	void getSoudState(CCObject* pSender);
	void getMusicState(CCObject* pSender);
	void quit();
	void cancel();
	void showQuit();
	void setSignIn(bool signIn);
	void buyPower();
	void hideAbout();
	void startGameT();
	void setAboutVisible(bool visible);

    Animation* getAnimationByName(std::string animName,float delay,int animNum);

private:
	Menu* menuBgMusic;
	Menu* menuSoundEffect;
    Sprite* quitBg;
	Sprite* quitDesc;
	Menu* confirmMenu;
	Menu* cancelMenu;
	SignIn* signIn;
	bool hasShowQuitPay;
	Sprite* aboutBg;
	Label* smallTitle11;
	Label* smallTitle12;
	Label* smallTitle21;
	Label* smallTitle22;
	Label* titleDesc1;
	Label* titleDesc2;
	Label* titleDesc3;
	Label* titleDesc4;
	Label* titleDesc5;
	Label* titleDesc6;
	Label* titleDesc7;
	Label* titleDesc8;
	Label* titleDesc9;
	Menu* backMenu;
	Menu* contiMenu;
	Sprite* startTxt;
	Sprite* backTxt;
};
#endif
