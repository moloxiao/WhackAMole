#include "GamePause.h"
#include "GameState.h"

bool GamePause::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto draw = DrawNode::create();
	draw->drawSolidRect(Vec2(0,0), Vec2(480,800), Color4F::BLACK);
	this->addChild(draw);

	// TODO : 等待添加挖洞效果
	

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


