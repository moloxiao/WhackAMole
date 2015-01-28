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
	bool showAbout(Touch* touch,Event* event);
	void getSoudState(CCObject* pSender);
	void getMusicState(CCObject* pSender);
	void quit();
	void cancel();
	void showQuit();
	void setSignIn(bool signIn);

	/** 
     ��ö������� 
     ��һ����������������
     �ڶ�������������¼�
     ����������������ͼƬ����
     */
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
	Node* aboutLayer;
};
#endif
