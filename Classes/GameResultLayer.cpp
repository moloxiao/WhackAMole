#include "GameResultLayer.h"
#include "MenuScene.h"
#include "Audio.h"
#include "GAMEDATA.h"
#include "GameScene.h"

bool GameResultLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Audio::getInstance()->playBGM("Music/bg.mp3");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	Sprite* background = Sprite::create("pr_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	Sprite* title = Sprite::create("co_win.png");
	title->setPosition(visibleSize.width/2,visibleSize.height - 100);
	this->addChild(title, 0);

	auto contiBtn = MenuItemImage::create(
		"game_result_btn_conti.png","game_result_btn_conti.png",CC_CALLBACK_0(GameResultLayer::contiGame,this)
		);
	auto contiMenu = Menu::create(contiBtn, NULL);
	contiMenu->setPosition(120,100);
	this->addChild(contiMenu);

	auto backBtn = MenuItemImage::create(
		"game_result_btn_back.png","game_result_btn_back.png",CC_CALLBACK_0(GameResultLayer::back,this)
		);
	auto backMenu = Menu::create(backBtn, NULL);
	backMenu->setPosition(360,100);
	this->addChild(backMenu);

	return true;
}

void GameResultLayer::contiGame(){
	Director::getInstance()->replaceScene(TransitionSlideInL::create(1,GameScene::create()));
}

void GameResultLayer::back(){
	Director::getInstance()->replaceScene(TransitionFade::create(1,MenuScene::create()));
}


