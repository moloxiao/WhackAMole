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
	Menu* closeMenu;
	Sprite* quitTitle;
	Sprite* confirmTxt;
	Sprite* cancelTxt;
	SignIn* signIn;
	bool hasShowQuitPay;
	Sprite* aboutBg;
	Sprite* aboutTitle1;
	Sprite* aboutTitle2;
	Sprite* aboutTitle3;
	Sprite* aboutTitle4;
	LabelAtlas* mouseNum;
	LabelAtlas* miceNum;
	Sprite* aboutDesc;
	Menu* backMenu;
	Menu* contiMenu;
	Sprite* startTxt;
	Sprite* backTxt;
};
#endif
