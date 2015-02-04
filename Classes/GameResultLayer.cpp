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
	gameScore = GAMEDATA::getInstance()->getGameScore();
	scoreNum = 0;
	hasShowRank = false;
	hasShowScore = false;
	hasShowScoreUp = false;
	hasShowkillMole = false;
	hasShowSaveFood = false;
	canClick = false;
	Audio::getInstance()->playBGM("Music/bg.mp3");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	Sprite* background = Sprite::create("result_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	auto shineBg = Sprite::create("result_light.png");
	shineBg->setPosition(240,560);
	this->addChild(shineBg);
	shineBg->runAction(RepeatForever::create(RotateBy::create(5,360)));

	Sprite* starLeftShandow = Sprite::create("star_shandow.png");
	starLeftShandow->setPosition(70,670);
	starLeftShandow->setAnchorPoint(Point(0,0.5));
	this->addChild(starLeftShandow, 0);

	Sprite* starMiddleShandow = Sprite::create("star_shandow.png");
	starMiddleShandow->setPosition(240,695);
	starMiddleShandow->setAnchorPoint(Point(0.5,0.5));
	this->addChild(starMiddleShandow, 0);

	Sprite* starRightShandow = Sprite::create("star_shandow.png");
	starRightShandow->setPosition(410,670);
	starRightShandow->setAnchorPoint(Point(1,0.5));
	this->addChild(starRightShandow, 0);

	Sprite* starLeft = Sprite::create("star_lignt.png");
	starLeft->setPosition(70,670);
	starLeft->setAnchorPoint(Point(0,0.5));
	this->addChild(starLeft, 0);

	Sprite* starMiddle = Sprite::create("star_lignt.png");
	starMiddle->setPosition(240,695);
	starMiddle->setAnchorPoint(Point(0.5,0.5));
	this->addChild(starMiddle, 0);

	Sprite* starRight = Sprite::create("star_lignt.png");
	starRight->setPosition(410,670);
	starRight->setAnchorPoint(Point(1,0.5));
	this->addChild(starRight, 0);

	score = LabelAtlas::create("0","num_result_score.png",43,70,48);
	score->setAnchorPoint(Point(0.5,0.5));
	score->setPosition(240+480,560);
	this->addChild(score);

	int rankNum = PLAYERRANK::getInstance()->getRankList(gameScore);
	if(rankNum < 10){
		rankNumLength = 1;
	}else if(rankNum < 100){
		rankNumLength = 2;
	}else if(rankNum < 1000){
		rankNumLength = 3;
	}else if(rankNum < 10000){
		rankNumLength = 4;
	}else if(rankNum < 100000){
		rankNumLength = 5;
	}else if(rankNum < 1000000){
		rankNumLength = 6;
	}

	rankTxt = Sprite::create("result_rank.png");
	rankTxt->setPosition(228-(rankNumLength-1)/2*24+480,460);
	this->addChild(rankTxt);

	rank = LabelAtlas::create(String::createWithFormat("%d",rankNum)->_string,
			"num_rank_up.png",24,34,48);
	rank->setAnchorPoint(Point(0.5,0.5));
	rank->setPosition(264+(rankNumLength-1)/2*24+480,460);
	this->addChild(rank);

	int scoreUpNum = CCRANDOM_0_1()*10000;
	if(scoreUpNum < 10){
		scoreUpNumLength = 1;
	}else if(scoreUpNum < 100){
		scoreUpNumLength = 2;
	}else if(scoreUpNum < 1000){
		scoreUpNumLength = 3;
	}else if(scoreUpNum < 10000){
		scoreUpNumLength = 4;
	}
	scoreUpTxt = Sprite::create("score_up.png");
	scoreUpTxt->setPosition(228-(scoreUpNumLength-1)/2*24+480,408);
	this->addChild(scoreUpTxt);

	scoreUp = LabelAtlas::create(String::createWithFormat("%d",scoreUpNum)->_string,
			"num_rank_up.png",24,34,48);
	scoreUp->setAnchorPoint(Point(0.5,0.5));
	scoreUp->setPosition(311+(scoreUpNumLength-1)/2*24+480,408);
	this->addChild(scoreUp);

	int rankUpNum = PLAYERRANK::getInstance()->getRankList(scoreNum+scoreUpNum);

	if(rankUpNum < 10){
		rankUpNumLength = 1;
	}else if(rankUpNum < 100){
		rankUpNumLength = 2;
	}else if(rankUpNum < 1000){
		rankUpNumLength = 3;
	}else if(rankUpNum < 10000){
		rankUpNumLength = 4;
	}else if(rankUpNum < 100000){
		rankUpNumLength = 5;
	}else if(rankUpNum < 1000000){
		rankUpNumLength = 6;
	}

	rankUpTxt = Sprite::create("rank_up.png");
	rankUpTxt->setPosition(228-(rankUpNumLength-1)/2*24+480,356);
	this->addChild(rankUpTxt);

	rankUp = LabelAtlas::create(String::createWithFormat("%d",rankUpNum)->_string,
			"num_rank_up.png",24,34,48);
	rankUp->setAnchorPoint(Point(0.5,0.5));
	rankUp->setPosition(363.6+(rankUpNumLength-1)/2*24+480,356);
	this->addChild(rankUp);

	int killMoleNum = GAMEDATA::getInstance()->getMouseNum();
	if(killMoleNum == 0){
		killMoleNumLength = 1;
		saveFoodNumLength = 1;
	}else if(killMoleNum < 10){
		killMoleNumLength = 1;
		saveFoodNumLength = 4;
	}else if(killMoleNum < 100){
		killMoleNumLength = 2;
		saveFoodNumLength = 5;
	}else if(killMoleNum < 1000){
		killMoleNumLength = 3;
		saveFoodNumLength = 6;
	}else if(killMoleNum < 10000){
		killMoleNumLength = 4;
		saveFoodNumLength = 7;
	}
	killMoleTxt1 = Sprite::create("result_kill.png");
	killMoleTxt1->setPosition(192.5-(killMoleNumLength-1)/2*18+480,280);
	this->addChild(killMoleTxt1);

	killMoleTxt2 = Sprite::create("result_mouse.png");
	killMoleTxt2->setPosition(287.5+(killMoleNumLength-1)/2*18+480,280);
	this->addChild(killMoleTxt2);

	killMole = LabelAtlas::create(String::createWithFormat("%d",killMoleNum)->_string,
			"num_result_kill.png",18,26,48);
	killMole->setAnchorPoint(Point(0.5,0.5));
	killMole->setPosition(240+480,280);
	this->addChild(killMole);

	saveFoodTxt1 = Sprite::create("result_kill.png");
	saveFoodTxt1->setPosition(179.5-(saveFoodNumLength-1)/2*18+480,240);
	this->addChild(saveFoodTxt1);

	saveFoodTxt2 = Sprite::create("result_mouse.png");
	saveFoodTxt2->setPosition(287.5+(saveFoodNumLength-1)/2*18+480,240);
	this->addChild(saveFoodTxt2);

	saveFood = LabelAtlas::create(String::createWithFormat("%d",GAMEDATA::getInstance()->getMouseNum()*1000)->_string,
			"num_result_kill.png",18,26,48);
	saveFood->setAnchorPoint(Point(0.5,0.5));
	saveFood->setPosition(227-(saveFoodNumLength-1)/2*18+480,240);
	this->addChild(saveFood);

	auto contiBtn = MenuItemImage::create(
		"btn_bg_normal.png","btn_bg_click.png",CC_CALLBACK_0(GameResultLayer::contiGame,this)
		);
	contiMenu = Menu::create(contiBtn, NULL);
	contiMenu->setPosition(348,138);
	contiMenu->setAnchorPoint(Point(1,0.5));
	contiMenu->setOpacity(0);
	this->addChild(contiMenu);

	contiTxt = Sprite::create("conti_game_txt.png");
	contiTxt->setPosition(444,138);
	contiTxt->setAnchorPoint(Point(1,0.5));
	contiTxt->setOpacity(0);
	this->addChild(contiTxt);

	auto backBtn = MenuItemImage::create(
		"btn_bg_normal.png","btn_bg_click.png",CC_CALLBACK_0(GameResultLayer::back,this)
		);
	backMenu = Menu::create(backBtn, NULL);
	backMenu->setPosition(132,138);
	backMenu->setAnchorPoint(Point(0,0.5));
	backMenu->setOpacity(0);
	this->addChild(backMenu);

	backTxt = Sprite::create("back_menu_txt.png");
	backTxt->setPosition(39,138);
	backTxt->setAnchorPoint(Point(0,0.5));
	backTxt->setOpacity(0);
	this->addChild(backTxt);

	this->scheduleUpdate();

	return true;
}

void GameResultLayer::update(float delta){
	if(this->isVisible()){
		animTime += delta/0.05;
		if(animTime >= 60000000){
			animTime = 6000;
		}
		if(animTime > 5){
			if(!hasShowScore){
				hasShowScore = true;
				score->runAction(MoveTo::create(0.3f,Point(240,560)));
			}
		}
		if(animTime >= 11){
			scoreNum = (animTime-11)/30 * gameScore;
		}
		if(scoreNum > gameScore){
			scoreNum = gameScore;
		}
		score->setString(cocos2d::String::createWithFormat("%d",(int)scoreNum)->_string);

		if(animTime >= 41 && !hasShowRank){
			hasShowRank = true;
			rankTxt->runAction(MoveTo::create(0.4f,Point(228,460)));
			rank->runAction(MoveTo::create(0.4f,Point(264,460)));
		}

		if(animTime >= 53 && !hasShowScoreUp){
			hasShowScoreUp = true;
			scoreUpTxt->runAction(MoveTo::create(0.4f,Point(228,408)));
			scoreUp->runAction(MoveTo::create(0.4f,Point(311,408)));
			rankUpTxt->runAction(MoveTo::create(0.4f,Point(228,356)));
			rankUp->runAction(MoveTo::create(0.4f,Point(363.5,356)));
		}

		if(animTime >= 47 && !hasShowkillMole){
			hasShowkillMole = true;
			killMoleTxt1->runAction(MoveTo::create(0.4f,Point(192.5-(killMoleNumLength-1)/2*18,280)));
			killMoleTxt2->runAction(MoveTo::create(0.4f,Point(287.5+(killMoleNumLength-1)/2*18,280)));
			killMole->runAction(MoveTo::create(0.4f,Point(240,280)));
		}

		if(animTime >= 47 && !hasShowSaveFood){
			hasShowSaveFood = true;
			saveFoodTxt1->runAction(MoveTo::create(0.4f,Point(179.5-(saveFoodNumLength-1)/2*18,240)));
			saveFoodTxt2->runAction(MoveTo::create(0.4f,Point(287.5+(saveFoodNumLength-1)/2*18,240)));
			saveFood->runAction(MoveTo::create(0.4f,Point(227-(saveFoodNumLength-1)/2*18,240)));
		}

		if(animTime >= 59 && !hasShowBtn){
			hasShowBtn = true;
			contiMenu->runAction(FadeTo::create(2.2f,255));
			backMenu->runAction(FadeTo::create(2.2f,255));
			contiTxt->runAction(FadeTo::create(2.2f,255));
			backTxt->runAction(FadeTo::create(2.2f,255));
		}

		if(animTime > 82){
			canClick = true;
		}
	}
}

void GameResultLayer::contiGame(){
	if(!canClick){
		return;
	}
	Director::getInstance()->replaceScene(TransitionSlideInL::create(1,GameScene::create()));
}

void GameResultLayer::back(){
	if(!canClick){
		return;
	}
	Director::getInstance()->replaceScene(TransitionFade::create(1,MenuScene::create()));
}


