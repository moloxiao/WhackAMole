#include "GameResultLayer.h"
#include "MenuScene.h"
#include "Audio.h"

bool GameResultLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Audio::getInstance()->playBGM("Music/bg.mp3");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("pr_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	return true;
}


