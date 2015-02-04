#include "SignIn.h"
#include "Chinese.h"
#include "CallAndroidMethod.h"
#include "GameData.h"
#include "GameScene.h"
#include "Power.h"
#include "Audio.h"

SignIn* SignIn::_instance = nullptr;
SignIn::SignIn(){
	this->init();
}

SignIn* SignIn::getInstance(){
	if(_instance == 0){
		_instance = new SignIn();
	}
	return _instance;
}

bool SignIn::init(){
	if(!Node::init()){
		return false;
	}

	auto bg = Sprite::create("black.png");
	bg->setScaleX(480);
	bg->setScaleY(800);
	bg->setPosition(240,400);
	this->addChild(bg);

	auto signInbg = Sprite::create("sign_in_bg.png");
	signInbg->setPosition(244,400);
	this->addChild(signInbg);

	auto title = Sprite::create("sign_in_title.png");
	title->setPosition(244,560);
	this->addChild(title);

	auto itemBg1 = Sprite::create("sign_in_item_bg_2.png");
	itemBg1->setPosition(40.5,470);
	itemBg1->setAnchorPoint(Point(0,0.5));
	this->addChild(itemBg1);

	auto itemBg12 = Sprite::create("sign_in_item_bg_1.png");
	itemBg12->setPosition(40.5,470);
	itemBg12->setAnchorPoint(Point(0,0.5));
	this->addChild(itemBg12);

	auto itemGold1 = Sprite::create("sign_in_day_1.png");
	itemGold1->setPosition(40.5,470);
	itemGold1->setAnchorPoint(Point(0,0.5));
	this->addChild(itemGold1);

	auto hasSign1 = Sprite::create("sign_in_has_sign.png");
	hasSign1->setPosition(109,512);
	this->addChild(hasSign1);

	auto itemBg2 = Sprite::create("sign_in_item_bg_2.png");
	itemBg2->setPosition(187.5,470);
	this->addChild(itemBg2);

	auto itemBg22 = Sprite::create("sign_in_item_bg_1.png");
	itemBg22->setPosition(187.5,470);
	this->addChild(itemBg22);

	auto itemGold2 = Sprite::create("sign_in_day_2.png");
	itemGold2->setPosition(187.5,470);
	this->addChild(itemGold2);

	auto hasSign2 = Sprite::create("sign_in_has_sign.png");
	hasSign2->setPosition(212.5,512);
	this->addChild(hasSign2);

	auto itemBg3 = Sprite::create("sign_in_item_bg_2.png");
	itemBg3->setPosition(291.5,470);
	this->addChild(itemBg3);

	auto itemBg32 = Sprite::create("sign_in_item_bg_1.png");
	itemBg32->setPosition(291.5,470);
	this->addChild(itemBg32);

	auto itemGold3 = Sprite::create("sign_in_day_3.png");
	itemGold3->setPosition(291.5,470);
	this->addChild(itemGold3);

	auto hasSign3 = Sprite::create("sign_in_has_sign.png");
	hasSign3->setPosition(316.5,512);
	this->addChild(hasSign3);

	auto itemBg4 = Sprite::create("sign_in_item_bg_2.png");
	itemBg4->setPosition(439.5,470);
	itemBg4->setAnchorPoint(Point(1,0.5));
	this->addChild(itemBg4);

	auto itemBg42 = Sprite::create("sign_in_item_bg_1.png");
	itemBg42->setPosition(439.5,470);
	itemBg42->setAnchorPoint(Point(1,0.5));
	this->addChild(itemBg42);

	auto itemGold4 = Sprite::create("sign_in_day_4.png");
	itemGold4->setPosition(439.5,470);
	itemGold4->setAnchorPoint(Point(1,0.5));
	this->addChild(itemGold4);

	auto hasSign4 = Sprite::create("sign_in_has_sign.png");
	hasSign4->setPosition(421,512);
	this->addChild(hasSign4);

	auto itemBg5 = Sprite::create("sign_in_item_bg_2.png");
	itemBg5->setPosition(40.5,365);
	itemBg5->setAnchorPoint(Point(0,0.5));
	this->addChild(itemBg5);

	auto itemBg52 = Sprite::create("sign_in_item_bg_1.png");
	itemBg52->setPosition(40.5,365);
	itemBg52->setAnchorPoint(Point(0,0.5));
	this->addChild(itemBg52);

	auto itemGold5 = Sprite::create("sign_in_day_5.png");
	itemGold5->setPosition(40.5,365);
	itemGold5->setAnchorPoint(Point(0,0.5));
	this->addChild(itemGold5);

	auto hasSign5 = Sprite::create("sign_in_has_sign.png");
	hasSign5->setPosition(109,407);
	this->addChild(hasSign5);

	auto itemBg6 = Sprite::create("sign_in_item_bg_2.png");
	itemBg6->setPosition(187.5,365);
	this->addChild(itemBg6);

	auto itemBg62 = Sprite::create("sign_in_item_bg_1.png");
	itemBg62->setPosition(187.5,365);
	this->addChild(itemBg62);

	auto itemGold6 = Sprite::create("sign_in_day_5.png");
	itemGold6->setPosition(187.5,365);
	this->addChild(itemGold6);

	auto hasSign6 = Sprite::create("sign_in_has_sign.png");
	hasSign6->setPosition(212.5,407);
	this->addChild(hasSign6);

	auto itemBg7 = Sprite::create("sign_in_item_bg_2.png");
	itemBg7->setPosition(291.5,365);
	this->addChild(itemBg7);

	auto itemBg72 = Sprite::create("sign_in_item_bg_1.png");
	itemBg72->setPosition(291.5,365);
	this->addChild(itemBg72);

	auto itemGold7 = Sprite::create("sign_in_day_5.png");
	itemGold7->setPosition(291.5,365);
	this->addChild(itemGold7);

	auto hasSign7 = Sprite::create("sign_in_has_sign.png");
	hasSign7->setPosition(316.5,407);
	this->addChild(hasSign7);

	hasSign1->setVisible(false);
	hasSign2->setVisible(false);
	hasSign3->setVisible(false);
	hasSign4->setVisible(false);
	hasSign5->setVisible(false);
	hasSign6->setVisible(false);
	hasSign7->setVisible(false);
	itemBg12->setVisible(false);
	itemBg22->setVisible(false);
	itemBg32->setVisible(false);
	itemBg42->setVisible(false);
	itemBg52->setVisible(false);
	itemBg62->setVisible(false);
	itemBg72->setVisible(false);

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		signDay = CallAndroidMethod::getInstance()->getCurrentSignDayas();
		CCLOG("signDay=%d",signDay);
		if(signDay == 0){
			hasSign1->setVisible(true);
			itemBg12->setVisible(true);
		}else if(signDay == 1){
			hasSign1->setVisible(true);
			hasSign2->setVisible(true);
			itemBg12->setVisible(true);
			itemBg22->setVisible(true);
		}else if(signDay == 2){
			hasSign1->setVisible(true);
			hasSign2->setVisible(true);
			hasSign3->setVisible(true);
			itemBg12->setVisible(true);
			itemBg22->setVisible(true);
			itemBg32->setVisible(true);
		}else if(signDay == 3){
			hasSign1->setVisible(true);
			hasSign2->setVisible(true);
			hasSign3->setVisible(true);
			hasSign4->setVisible(true);
			itemBg12->setVisible(true);
			itemBg22->setVisible(true);
			itemBg32->setVisible(true);
			itemBg42->setVisible(true);
		}else if(signDay >= 4){
			hasSign1->setVisible(true);
			hasSign2->setVisible(true);
			hasSign3->setVisible(true);
			hasSign4->setVisible(true);
			hasSign5->setVisible(true);
			itemBg12->setVisible(true);
			itemBg22->setVisible(true);
			itemBg32->setVisible(true);
			itemBg42->setVisible(true);
			itemBg52->setVisible(true);
		}else if(signDay >= 5){
			hasSign1->setVisible(true);
			hasSign2->setVisible(true);
			hasSign3->setVisible(true);
			hasSign4->setVisible(true);
			hasSign5->setVisible(true);
			hasSign6->setVisible(true);
			itemBg12->setVisible(true);
			itemBg22->setVisible(true);
			itemBg32->setVisible(true);
			itemBg42->setVisible(true);
			itemBg52->setVisible(true);
			itemBg62->setVisible(true);
		}else if(signDay >= 6){
			hasSign1->setVisible(true);
			hasSign2->setVisible(true);
			hasSign3->setVisible(true);
			hasSign4->setVisible(true);
			hasSign5->setVisible(true);
			hasSign6->setVisible(true);
			hasSign7->setVisible(true);
			itemBg12->setVisible(true);
			itemBg22->setVisible(true);
			itemBg32->setVisible(true);
			itemBg42->setVisible(true);
			itemBg52->setVisible(true);
			itemBg62->setVisible(true);
			itemBg72->setVisible(true);
		}
    #endif

	MenuItemImage* confirmBtn = MenuItemImage::create(
			"btn_bg_normal.png","btn_bg_click.png",CC_CALLBACK_0(SignIn::hideSelf,this)
			);
	auto confirmMenu = Menu::create(confirmBtn, NULL);
	confirmMenu->setPosition(244,266);
	this->addChild(confirmMenu);

	auto confirmTxt = Sprite::create("confirm_txt.png");
	confirmTxt->setPosition(244,266);
	this->addChild(confirmTxt);

	return true;
}

void SignIn::hideSelf(){
	Audio::getInstance()->playSound("Music/click.ogg");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->sign();
		if(signDay == 6){
			CallAndroidMethod::getInstance()->cleanSign();
		}
    #endif
	if(signDay >= 4){
		signDay = 4;
	}
	GAMEDATA::getInstance()->setPowerValue(GAMEDATA::getInstance()->getPowerValue()+(signDay+1)*2);
	Power::getInstance()->refreshPower();
	this->setVisible(false);
	this->removeFromParentAndCleanup(true);
}
