#include "GamePause.h"
#include "GameState.h"

bool GamePause::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("mouse_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	auto btnPause = MenuItemImage::create(
		"b_helpc.png",
        "b_helpc_.png",
        CC_CALLBACK_0(GamePause::returnGame, this));
    auto menu = Menu::create(btnPause, NULL);
    menu->setPosition(visibleSize.width/2, 150);
    this->addChild(menu, 1);

	return true;
}

void GamePause::returnGame() {
	this->removeFromParentAndCleanup(true);
	GAMESTATE::getInstance()->setGamePause(false);
}


