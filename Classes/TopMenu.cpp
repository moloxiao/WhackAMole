#include "TopMenu.h"
#include "GameLayer.h"
#include "GameState.h"
#include "GamePause.h"
#include "Audio.h"

TopMenu* TopMenu::_instance = nullptr;
TopMenu::TopMenu(){
	this->init();
}

TopMenu* TopMenu::getInstance(){
	if(_instance == 0){
		_instance = new TopMenu();
	}
	return _instance;
}

bool TopMenu::init(){
	if(!Node::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	// 初始化界面
	// 1-初始化得分
	curScore = Label::create(
		"0",
		"Verdana-Bold",50	
		);
	curScore->setPosition(visibleSize.width/2,visibleSize.height/2 +300);
	this->addChild(curScore);

	// 2-初始化时间 labelTime
	labelTime = Label::create(
		"Time:" + cocos2d::String::createWithFormat("%d",GameLayer::DEFAULT_GAME_TIME)->_string,
		"Verdana-Bold",30	
		);
	labelTime->setPosition(80,visibleSize.height/2 +350);
	this->addChild(labelTime);

	// 3-初始化暂停按键
	auto btnPause = MenuItemImage::create(
		"pause.png",
        "pause.png",
        CC_CALLBACK_0(TopMenu::pauseGame, this));
    auto menu = Menu::create(btnPause, NULL);
    menu->setPosition(visibleSize.width - 50, visibleSize.height/2 +350);
    this->addChild(menu, 1);
	return true;
}

void TopMenu::pauseGame() {
	Audio::getInstance()->playSound("Music/click.ogg");
	if(!GAMESTATE::getInstance()->getGamePause()) {
		GAMESTATE::getInstance()->setGamePause(true);
		this->addChild(GamePause::create(), 10);
	}
	
}


void TopMenu::updateGameTime(int gameTime) {
	labelTime->setString("Time:" + cocos2d::String::createWithFormat("%d",gameTime)->_string);
}

void TopMenu::updateGameScore(int gameTime) {
	curScore->setString(cocos2d::String::createWithFormat("%d",gameTime)->_string);
}

