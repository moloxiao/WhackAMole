#include "GameResultLayer.h"
#include "MenuScene.h"
#include "Audio.h"
#include "GAMEDATA.h"
#include "GameScene.h"
#include "Chinese.h"
#include "PlayerRank.h"

using namespace cocos2d;

bool GameResultLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Audio::getInstance()->playBGM("Music/bg.mp3");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	Sprite* background = Sprite::create("result_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	auto shineBg = Sprite::create("result_light.png");
	shineBg->setPosition(240,400);
	this->addChild(shineBg);
	shineBg->runAction(RepeatForever::create(RotateBy::create(5,360)));

	Sprite* starLeft = Sprite::create("star_lignt.png");
	starLeft->setPosition(88,638);
	starLeft->setAnchorPoint(Point(0,0.5));
	starLeft->setScale(3.0f);
	this->addChild(starLeft, 0);

	Sprite* starMiddle = Sprite::create("star_lignt.png");
	starMiddle->setPosition(240,663);
	starMiddle->setAnchorPoint(Point(0.5,0.5));
	starMiddle->setScale(3.0f);
	this->addChild(starMiddle, 0);

	Sprite* starRight = Sprite::create("star_lignt.png");
	starRight->setPosition(392,638);
	starRight->setAnchorPoint(Point(1,0.5));
	starRight->setScale(3.0f);
	this->addChild(starRight, 0);

	int scoreNum = GAMEDATA::getInstance()->getGameScore();
	auto score = LabelAtlas::create(String::createWithFormat("%d",scoreNum)->_string,"num_result_score.png",24,30,48);
	score->setAnchorPoint(Point(0.5,0.5));
	score->setScale(2.0f);
	score->setPosition(240,518);
	this->addChild(score);

	auto killMoleTxt = Label::create(ChineseWord("killmole1")+String::createWithFormat("%d",GAMEDATA::getInstance()->getMouseNum())->_string
			+ChineseWord("killmole2"),"Verdana-Bold",36);
	killMoleTxt->setPosition(240,425);
	this->addChild(killMoleTxt);

	auto saveFoodTxt = Label::create(ChineseWord("savefood1")+String::createWithFormat("%d",GAMEDATA::getInstance()->getMouseNum()*1000)->_string
			+ChineseWord("savefood2"),"Verdana-Bold",36);
	saveFoodTxt->setPosition(240,358);
	this->addChild(saveFoodTxt);

	auto rankTxt = Label::create(ChineseWord("rank")+String::createWithFormat(":%d",PLAYERRANK::getInstance()->getRankList(scoreNum))->_string,"Verdana-Bold",36);
	rankTxt->setPosition(240,282);
	this->addChild(rankTxt);

	int scoreUpNum = CCRANDOM_0_1()*10000;
	auto rankUpTxt = Label::create(ChineseWord("scoreup")+String::createWithFormat("%d",scoreUpNum)->_string
			+ChineseWord("rankup")+String::createWithFormat("%d",PLAYERRANK::getInstance()->getRankList(scoreNum+scoreUpNum))->_string,"Verdana-Bold",24);
	rankUpTxt->setPosition(240,251);
	this->addChild(rankUpTxt);

	auto contiBtn = MenuItemImage::create(
		"btn_bg_normal.png","btn_bg_click.png",CC_CALLBACK_0(GameResultLayer::contiGame,this)
		);
	auto contiMenu = Menu::create(contiBtn, NULL);
	contiMenu->setPosition(348,138);
	contiMenu->setAnchorPoint(Point(1,0.5));
	this->addChild(contiMenu);

	auto contiTxt = Sprite::create("conti_game_txt.png");
	contiTxt->setPosition(429,138);
	contiTxt->setAnchorPoint(Point(1,0.5));
	this->addChild(contiTxt);

	auto backBtn = MenuItemImage::create(
		"btn_bg_normal.png","btn_bg_click.png",CC_CALLBACK_0(GameResultLayer::back,this)
		);
	auto backMenu = Menu::create(backBtn, NULL);
	backMenu->setPosition(132,138);
	backMenu->setAnchorPoint(Point(0,0.5));
	this->addChild(backMenu);

	auto backTxt = Sprite::create("back_menu_txt.png");
	backTxt->setPosition(47,138);
	backTxt->setAnchorPoint(Point(0,0.5));
	this->addChild(backTxt);

	return true;
}

void GameResultLayer::contiGame(){
	Director::getInstance()->replaceScene(TransitionSlideInL::create(1,GameScene::create()));
}

void GameResultLayer::back(){
	Director::getInstance()->replaceScene(TransitionFade::create(1,MenuScene::create()));
}


