#include "Power.h"
#include "GameData.h"

Power* Power::_instance = nullptr;
Power::Power(){
	this->init();
}

Power* Power::getInstance(){
	if(_instance == 0){
		_instance = new Power();
	}
	return _instance;
}

bool Power::init(){
	if(!Node::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	powerNum = LabelAtlas::create(String::createWithFormat(":%d",GAMEDATA::getInstance()->getPowerValue())->_string,"num_power.png",
			24,29,48);
	powerNum->setPosition(62,749);
	powerNum->setAnchorPoint(Point(0, 0.5));
	this->addChild(powerNum);
	return true;
}

void Power::refreshPower(){
	powerNum->setString(String::createWithFormat(":%d",GAMEDATA::getInstance()->getPowerValue())->_string);
}
