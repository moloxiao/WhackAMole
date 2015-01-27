#include "GameResultLayer.h"
#include "MenuScene.h"

bool GameResultLayer::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("pr_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	return true;
}


