#include "PayHandler.h"
#include "GAMEDATA.h"
#include "GameLayer.h"
#include "GameState.h"
#include "Power.h"
#include "MenuScene.h"

static PayHandler* _instance = nullptr;
PayHandler* PayHandler::getInstance()
{
	if (!_instance)
	{
		_instance = new PayHandler();
	}
	return _instance;
}

void PayHandler::payCallback(int requestId,int resultId){
	if(resultId == 0){
		GAMEDATA::getInstance()->setPaySuccess(true);
	}

	switch (requestId)
	{
	case 1:
		if(resultId == 0){
			GameLayer::needDoStartGame = true;
			GAMEDATA::getInstance()->setPowerValue(GAMEDATA::getInstance()->getPowerValue()+10);
			Power::getInstance()->refreshPower();
		}else{
			GameLayer::needDoStartGame = true;
		}
		break;
	case 2:
		if(resultId == 0){
			GAMEDATA::getInstance()->setPowerValue(GAMEDATA::getInstance()->getPowerValue()+10);
			Power::getInstance()->refreshPower();
		}
		break;
	case 3:
		if(resultId == 0){
			GAMEDATA::getInstance()->setNightFightTimes(GAMEDATA::getInstance()->getNightFightTimes()+9);
			GAMESTATE::getInstance()->setGamePause(false);
			GameLayer::payResult = true;
			GameLayer::needAddTime = true;
		}else{
			GameLayer::payResult = false;
			GameLayer::needAddTime = false;
			GAMESTATE::getInstance()->setGamePause(false);
		}
		break;
	case 4:
		if(resultId == 0){
			GAMEDATA::getInstance()->setPowerValue(GAMEDATA::getInstance()->getPowerValue()+5);
			Power::getInstance()->refreshPower();
			GAMEDATA::getInstance()->setNightFightTimes(GAMEDATA::getInstance()->getNightFightTimes()+5);
		}
		break;
	case 5:
		if(resultId == 0){
			GAMEDATA::getInstance()->setNightFightTimes(GAMEDATA::getInstance()->getNightFightTimes()-1);
			GAMESTATE::getInstance()->setGamePause(false);
			GameLayer::needAddTime = true;
		}else{
			GameLayer::needAddTime = false;
			GAMESTATE::getInstance()->setGamePause(false);
		}
		break;
	case 6:
		if(resultId == 0){
			GAMEDATA::getInstance()->setPowerValue(GAMEDATA::getInstance()->getPowerValue()+5);
			Power::getInstance()->refreshPower();
			GAMEDATA::getInstance()->setNightFightTimes(GAMEDATA::getInstance()->getNightFightTimes()+5);
		}
		break;
	case 7:
		GAMESTATE::getInstance()->setGamePause(false);
		if(resultId == 0){
			GAMEDATA::getInstance()->setPowerValue(GAMEDATA::getInstance()->getPowerValue()+10);
			Power::getInstance()->refreshPower();
		}
		break;
	case 8:
		if(resultId == 0){
			GameLayer::needDoStartGame = true;
			GAMEDATA::getInstance()->setPowerValue(GAMEDATA::getInstance()->getPowerValue()+10);
			Power::getInstance()->refreshPower();
		}else{
			GAMESTATE::getInstance()->setGameOver(true);
			GAMESTATE::getInstance()->setGamePause(false);
			Director::getInstance()->replaceScene(TransitionFade::create(1,MenuScene::create()));
		}
		break;
	default:
		break;
	}
}

