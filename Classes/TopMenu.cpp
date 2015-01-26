#include "TopMenu.h"
#include "GameLayer.h"

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
	std::string buffer = "Score";
	curScore = Label::create(
		buffer,
		"Verdana-Bold",50	
		);
	curScore->setPosition(visibleSize.width/2,visibleSize.height/2 +300);
	this->addChild(curScore);

	// 1-初始化时间 labelTime
	labelTime = Label::create(
		"Time:" + cocos2d::String::createWithFormat("%d",GameLayer::DEFAULT_GAME_TIME)->_string,
		"Verdana-Bold",30	
		);
	labelTime->setPosition(80,visibleSize.height/2 +350);
	this->addChild(labelTime);

	return true;
}

void TopMenu::updateGameTime(int gameTime) {
	labelTime->setString("Time:" + cocos2d::String::createWithFormat("%d",gameTime)->_string);
}

