#include "GAMEDATA.h"
#include "cocos2d.h"
using namespace cocos2d;

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){
	this->init();
}

void GAMEDATA::init(){
	gameScore = 0;
	mouseNum = 0;
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

void GAMEDATA::setMouseNum(int mouse_num){
	mouseNum = mouse_num;
}

int GAMEDATA::getMouseNum(){
	return mouseNum;
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

int GAMEDATA::getTotalMouseNum(){
	return UserDefault::getInstance()->getIntegerForKey("totalMouseNum",0);
}

void GAMEDATA::setTotalMouseNum(int totalMouseNum){
	UserDefault::getInstance()->setIntegerForKey("totalMouseNum",totalMouseNum);
}

int GAMEDATA::getPowerValue(){
	return UserDefault::getInstance()->getIntegerForKey("powerValue",0);
}

void GAMEDATA::setPowerValue(int powerValue){
	UserDefault::getInstance()->setIntegerForKey("powerValue",powerValue);
}

int GAMEDATA::getNightFightTimes(){
	return UserDefault::getInstance()->getIntegerForKey("nightFightTimes",0);
}

void GAMEDATA::setNightFightTimes(int nightFightTimes){
	UserDefault::getInstance()->setIntegerForKey("nightFightTimes",nightFightTimes);
}

bool GAMEDATA::isFirstLogin(){
	return firstLognin;
}

void GAMEDATA::setFirstLogin(bool first_login){
	firstLognin = first_login;
}

int GAMEDATA::getPlayRounds(){
	return UserDefault::getInstance()->getIntegerForKey("playRounds",0);
}

void GAMEDATA::setPlayRounds(int playRounds){
	UserDefault::getInstance()->setIntegerForKey("playRounds",playRounds);
}

