#include "GAMEDATA.h"
#include "cocos2d.h"
using namespace cocos2d;

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){
	this->init();
}

void GAMEDATA::init(){
	gameScore = 0;
}

GAMEDATA* GAMEDATA::getInstance(){
	if(_instance == 0){
		_instance = new GAMEDATA();
	}
	return _instance;
}

void GAMEDATA::setGameScore(int score){
	gameScore = score;
}

int GAMEDATA::getGameScore(){
	return gameScore;
}

void GAMEDATA::setSoundState(bool state) {
	UserDefault::getInstance()->setBoolForKey("soundState",state);
}

bool GAMEDATA::getSoundState() {
	return UserDefault::getInstance()->getBoolForKey("soundState",true);
}

void GAMEDATA::setMusicState(bool state) {
	UserDefault::getInstance()->setBoolForKey("musicState",state);
}

bool GAMEDATA::getMusicState() {
	return UserDefault::getInstance()->getBoolForKey("musicState",true);
}

bool GAMEDATA::isPaySuccess(){
	return UserDefault::getInstance()->getBoolForKey("paySuccess",false);
}

void GAMEDATA::setPaySuccess(bool paySuccess){
	UserDefault::getInstance()->setBoolForKey("paySuccess",paySuccess);
}

int GAMEDATA::getTotalScore(){
	return UserDefault::getInstance()->getIntegerForKey("totalScore",0);
}

void GAMEDATA::setTotalScore(int totalScore){
	UserDefault::getInstance()->setIntegerForKey("totalScore",totalScore);
}

