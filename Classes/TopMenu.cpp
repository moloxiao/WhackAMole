#include "TopMenu.h"
#include "GameLayer.h"
#include "GameState.h"
#include "GamePause.h"
#include "Audio.h"
#include "GAMEDATA.h"

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

	auto powerNum = LabelAtlas::create(String::createWithFormat(":%d",GAMEDATA::getInstance()->getPowerValue())->_string,"num_power.png",
			24,29,48);
	powerNum->setAnchorPoint(Point(0,0.5));
	powerNum->setPosition(62,749);
	this->addChild(powerNum);

	auto scoreTxt = Sprite::create("score_txt.png");
	scoreTxt->setPosition(240,749);
	this->addChild(scoreTxt);

	// ��ʼ������
	// 1-��ʼ���÷�
	curScore = LabelAtlas::create("0","num_game_score.png",25,32,48);
	curScore->setAnchorPoint(Point(0.5,0.5));
	curScore->setPosition(240,695);
	this->addChild(curScore);

	auto clock = Sprite::create("clock_icon.png");
	clock->setPosition(32,695);
	clock->setAnchorPoint(Point(0,0.5));
	this->addChild(clock);

	// 2-��ʼ��ʱ�� labelTime
	labelTime = LabelAtlas::create("0","num_time.png",20,26,48);
	labelTime->setPosition(82,695);
	labelTime->setAnchorPoint(Point(0,0.5));
	this->addChild(labelTime);

	// 3-��ʼ����ͣ����
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

