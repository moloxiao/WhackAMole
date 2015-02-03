#include "TopMenu.h"
#include "GameLayer.h"
#include "GameState.h"
#include "GamePause.h"
#include "Audio.h"
#include "GAMEDATA.h"
#include "CallAndroidMethod.h"
#include "Power.h"

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
	
	auto power = Sprite::create("power.png");
	power->setPosition(32,749);
	power->setAnchorPoint(Point(0,0.5));
	this->addChild(power);

	auto powerNum = Power::getInstance();
	this->addChild(powerNum);

	auto btnBuyPower = MenuItemImage::create(
		"power_buy_btn.png",
		"power_buy_btn.png",
		CC_CALLBACK_0(TopMenu::buyPower, this));
	auto buyPowerMenu = Menu::create(btnBuyPower, NULL);
	buyPowerMenu->setPosition(135,749);
	this->addChild(buyPowerMenu);

	auto scoreTxt = Sprite::create("score_txt.png");
	scoreTxt->setPosition(240,749);
	this->addChild(scoreTxt);

	// 初始化界面
	// 1-初始化得分
	curScore = LabelAtlas::create("0","num_game_score.png",25,32,48);
	curScore->setAnchorPoint(Point(0.5,0.5));
	curScore->setPosition(240,695);
	this->addChild(curScore);

	auto clock = Sprite::create("clock_icon.png");
	clock->setPosition(32,695);
	clock->setAnchorPoint(Point(0,0.5));
	this->addChild(clock);

	// 2-初始化时间 labelTime
	labelTime = LabelAtlas::create("0","num_time.png",20,26,48);
	labelTime->setPosition(82,695);
	labelTime->setAnchorPoint(Point(0,0.5));
	this->addChild(labelTime);

	// 3-初始化暂停按键
	auto btnPause = MenuItemImage::create(
		"pause_btn.png",
        "pause_btn.png",
        CC_CALLBACK_0(TopMenu::pauseGame, this));
    auto menu = Menu::create(btnPause, NULL);
    menu->setPosition(428,739);
    menu->setAnchorPoint(Point(1,0.5));
    this->addChild(menu, 1);
	return true;
}

void TopMenu::buyPower(){
	GAMESTATE::getInstance()->setGamePause(true);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(7);
	#endif
}

void TopMenu::pauseGame() {
	Audio::getInstance()->playSound("Music/click.ogg");
	if(!GAMESTATE::getInstance()->getGamePause()) {
		GAMESTATE::getInstance()->setGamePause(true);
		this->addChild(GamePause::create(), 10);
	}
	
}


void TopMenu::updateGameTime(int gameTime) {
	labelTime->setString(cocos2d::String::createWithFormat("%d",gameTime)->_string);
}

void TopMenu::updateGameScore(int gameTime) {
	curScore->setString(cocos2d::String::createWithFormat("%d",gameTime)->_string);
}

