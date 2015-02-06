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
	showStar1 = false;
	showStar2 = false;
	showStar3 = false;
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

	starLeft = Sprite::create("star_lignt.png");
	starLeft->setPosition(70,670);
	starLeft->setAnchorPoint(Point(0,0.5));
	this->addChild(starLeft, 0);
	starLeft->setScale(3);
	starLeft->setVisible(false);

	starMiddle = Sprite::create("star_lignt.png");
	starMiddle->setPosition(240,695);
	starMiddle->setAnchorPoint(Point(0.5,0.5));
	this->addChild(starMiddle, 0);
	starMiddle->setScale(3);
	starMiddle->setVisible(false);

	starRight = Sprite::create("star_lignt.png");
	starRight->setPosition(410,670);
	starRight->setAnchorPoint(Point(1,0.5));
	this->addChild(starRight, 0);
	starRight->setScale(3);
	starRight->setVisible(false);

	score = LabelAtlas::create("0","num_result_score.png",43,70,48);
	score->setAnchorPoint(Point(0.5,0.5));
	score->setPosition(240+480,560);
	this->addChild(score);

	rankNum = PLAYERRANK::getInstance()->getRankList(gameScore);
	rankTxt = Sprite::create("result_rank.png");
	rank = LabelAtlas::create(String::createWithFormat("%d",rankNum)->_string,
			"num_rank_up.png",24,34,48);
	rank->setAnchorPoint(Point(0.5,0.5));
	if(rankNum < 10){
		rankTxt->setPosition(228+480,460);
		rank->setPosition(276+480,460);
	}else if(rankNum < 100){
		rankTxt->setPosition(216+480,460);
		rank->setPosition(276+480,460);
	}else if(rankNum < 1000){
		rankTxt->setPosition(204+480,460);
		rank->setPosition(276+480,460);
	}else if(rankNum < 10000){
		rankTxt->setPosition(192+480,460);
		rank->setPosition(276+480,460);
	}else if(rankNum < 100000){
		rankTxt->setPosition(180+480,460);
		rank->setPosition(276+480,460);
	}else if(rankNum < 1000000){
		rankTxt->setPosition(168+480,460);
		rank->setPosition(276+480,460);
	}

	this->addChild(rankTxt);
	this->addChild(rank);

	scoreUpNum = CCRANDOM_0_1()*10000+2000;
	scoreUpTxt = Sprite::create("score_up.png");scoreUp = LabelAtlas::create(String::createWithFormat("%d",scoreUpNum)->_string,
			"num_rank_up.png",24,34,48);
	scoreUp->setAnchorPoint(Point(0.5,0.5));
	if(scoreUpNum < 10){
		scoreUpTxt->setPosition(228+480,408);
		scoreUp->setPosition(311+480,408);
	}else if(scoreUpNum < 100){
		scoreUpTxt->setPosition(216+480,408);
		scoreUp->setPosition(311+480,408);
	}else if(scoreUpNum < 1000){
		scoreUpTxt->setPosition(204+480,408);
		scoreUp->setPosition(311+480,408);
	}else if(scoreUpNum < 10000){
		scoreUpTxt->setPosition(192+480,408);
		scoreUp->setPosition(311+480,408);
	}else if(scoreUpNum < 100000){
		scoreUpTxt->setPosition(180+480,408);
		scoreUp->setPosition(311+480,408);
	}
	this->addChild(scoreUpTxt);
	this->addChild(scoreUp);

	rankUpNum = PLAYERRANK::getInstance()->getRankList(gameScore+scoreUpNum);
	rankUpTxt = Sprite::create("rank_up.png");
	rankUp = LabelAtlas::create(String::createWithFormat("%d",rankUpNum)->_string,
			"num_rank_up.png",24,34,48);
	rankUp->setAnchorPoint(Point(0.5,0.5));

	if(rankUpNum < 10){
		rankUpTxt->setPosition(228+480,356);
		rankUp->setPosition(363.5+480,356);
	}else if(rankUpNum < 100){
		rankUpTxt->setPosition(216+480,356);
		rankUp->setPosition(363.5+480,356);
	}else if(rankUpNum < 1000){
		rankUpTxt->setPosition(204+480,356);
		rankUp->setPosition(363.5+480,356);
	}else if(rankUpNum < 10000){
		rankUpTxt->setPosition(192+480,356);
		rankUp->setPosition(363.5+480,356);
	}else if(rankUpNum < 100000){
		rankUpTxt->setPosition(180+480,356);
		rankUp->setPosition(363.5+480,356);
	}else if(rankUpNum < 1000000){
		rankUpTxt->setPosition(168+480,356);
		rankUp->setPosition(363.5+480,356);
	}

	this->addChild(rankUpTxt);
	this->addChild(rankUp);

	killMoleNum = GAMEDATA::getInstance()->getMouseNum();
	killMoleTxt1 = Sprite::create("result_kill.png");
	killMoleTxt2 = Sprite::create("result_mouse.png");
	killMole = LabelAtlas::create(String::createWithFormat("%d",killMoleNum)->_string,
			"num_result_kill.png",18,26,48);
	killMole->setAnchorPoint(Point(0.5,0.5));
	saveFoodTxt1 = Sprite::create("result_help.png");
	saveFoodTxt2 = Sprite::create("kg_mice.png");
	saveFood = LabelAtlas::create(String::createWithFormat("%d",killMoleNum*1000)->_string,
			"num_result_kill.png",18,26,48);
	saveFood->setAnchorPoint(Point(0.5,0.5));
	if(killMoleNum == 0){
		killMoleTxt1->setPosition(194.5-9+480,280);
		killMoleTxt2->setPosition(289.5+9+480,280);
		killMole->setPosition(240+480,280);
		saveFoodTxt1->setPosition(179.5+480,240);
		saveFoodTxt2->setPosition(287.5+480,240);
		saveFood->setPosition(227+480,240);
	}else if(killMoleNum < 10){
		killMoleTxt1->setPosition(194.5-9+480,280);
		killMoleTxt2->setPosition(289.5+9+480,280);
		killMole->setPosition(240+480,280);
		saveFoodTxt1->setPosition(157.5+480,240);
		saveFoodTxt2->setPosition(319.5+480,240);
		saveFood->setPosition(232+480,240);
	}else if(killMoleNum < 100){
		killMoleTxt1->setPosition(194.5-18+480,280);
		killMoleTxt2->setPosition(289.5+18+480,280);
		killMole->setPosition(240+480,280);
		saveFoodTxt1->setPosition(143.5+480,240);
		saveFoodTxt2->setPosition(323.5+480,240);
		saveFood->setPosition(227+480,240);
	}else if(killMoleNum < 1000){
		killMoleTxt1->setPosition(194.5-27+480,280);
		killMoleTxt2->setPosition(289.5+27+480,280);
		killMole->setPosition(240+480,280);
		saveFoodTxt1->setPosition(139.5+480,240);
		saveFoodTxt2->setPosition(337.5+480,240);
		saveFood->setPosition(232+480,240);
	}else if(killMoleNum < 10000){
		killMoleTxt1->setPosition(194.5-36+480,280);
		killMoleTxt2->setPosition(289.5+36+480,280);
		killMole->setPosition(240+480,280);
		saveFoodTxt1->setPosition(125.5+480,240);
		saveFoodTxt2->setPosition(341.5+480,240);
		saveFood->setPosition(227+480,240);
	}
	this->addChild(killMoleTxt1);
	this->addChild(killMoleTxt2);
	this->addChild(killMole);
	this->addChild(saveFoodTxt1);
	this->addChild(saveFoodTxt2);
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
				Audio::getInstance()->playSound("Music/score.ogg");
				hasShowScore = true;
				score->runAction(MoveTo::create(0.3f,Point(240,560)));
			}
			if(gameScore < 20000){
				if(!showStar1){
					showStar1 = true;
					starLeft->setVisible(true);
					starLeft->runAction(ScaleTo::create(0.4f,1));
				}
			}else if(gameScore < 120000){
				if(!showStar1){
					showStar1 = true;
					starLeft->setVisible(true);
					starLeft->runAction(ScaleTo::create(0.4f,1));
				}
				if(animTime > 11){
					if(!showStar2){
						showStar2 = true;
						starMiddle->setVisible(true);
						starMiddle->runAction(ScaleTo::create(0.4f,1));
					}
				}
			}else{
				if(!showStar1){
					showStar1 = true;
					starLeft->setVisible(true);
					starLeft->runAction(ScaleTo::create(0.4f,1));
				}
				if(animTime > 11){
					if(!showStar2){
						showStar2 = true;
						starMiddle->setVisible(true);
						starMiddle->runAction(ScaleTo::create(0.4f,1));
					}
				}
				if(animTime > 17){
					if(!showStar3){
						showStar3 = true;
						starRight->setVisible(true);
						starRight->runAction(ScaleTo::create(0.4f,1));
					}
				}
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
			if(rankNum < 10){
				rankTxt->runAction(MoveTo::create(0.4f,Point(228,460)));
				rank->runAction(MoveTo::create(0.4f,Point(276,460)));
			}else if(rankNum < 100){
				rankTxt->runAction(MoveTo::create(0.4f,Point(216,460)));
				rank->runAction(MoveTo::create(0.4f,Point(276,460)));
			}else if(rankNum < 1000){
				rankTxt->runAction(MoveTo::create(0.4f,Point(204,460)));
				rank->runAction(MoveTo::create(0.4f,Point(276,460)));
			}else if(rankNum < 10000){
				rankTxt->runAction(MoveTo::create(0.4f,Point(192,460)));
				rank->runAction(MoveTo::create(0.4f,Point(276,460)));
			}else if(rankNum < 100000){
				rankTxt->runAction(MoveTo::create(0.4f,Point(180,460)));
				rank->runAction(MoveTo::create(0.4f,Point(276,460)));
			}else if(rankNum < 1000000){
				rankTxt->runAction(MoveTo::create(0.4f,Point(168,460)));
				rank->runAction(MoveTo::create(0.4f,Point(276,460)));
			}
		}

		if(animTime >= 47 && !hasShowScoreUp){
			hasShowScoreUp = true;
			if(scoreUpNum < 10){
				scoreUpTxt->runAction(MoveTo::create(0.4f,Point(228,408)));
				scoreUp->runAction(MoveTo::create(0.4f,Point(311,408)));
			}else if(scoreUpNum < 100){
				scoreUpTxt->runAction(MoveTo::create(0.4f,Point(216,408)));
				scoreUp->runAction(MoveTo::create(0.4f,Point(311,408)));
			}else if(scoreUpNum < 1000){
				scoreUpTxt->runAction(MoveTo::create(0.4f,Point(204,408)));
				scoreUp->runAction(MoveTo::create(0.4f,Point(311,408)));
			}else if(scoreUpNum < 10000){
				scoreUpTxt->runAction(MoveTo::create(0.4f,Point(192,408)));
				scoreUp->runAction(MoveTo::create(0.4f,Point(311,408)));
			}else if(scoreUpNum < 100000){
				scoreUpTxt->runAction(MoveTo::create(0.4f,Point(180,408)));
				scoreUp->runAction(MoveTo::create(0.4f,Point(311,408)));
			}
			if(rankUpNum < 10){
				rankUpTxt->runAction(MoveTo::create(0.4f,Point(228,356)));
				rankUp->runAction(MoveTo::create(0.4f,Point(363.5,356)));
			}else if(rankUpNum < 100){
				rankUpTxt->runAction(MoveTo::create(0.4f,Point(216,356)));
				rankUp->runAction(MoveTo::create(0.4f,Point(363.5,356)));
			}else if(rankUpNum < 1000){
				rankUpTxt->runAction(MoveTo::create(0.4f,Point(204,356)));
				rankUp->runAction(MoveTo::create(0.4f,Point(363.5,356)));
			}else if(rankUpNum < 10000){
				rankUpTxt->runAction(MoveTo::create(0.4f,Point(192,356)));
				rankUp->runAction(MoveTo::create(0.4f,Point(363.5,356)));
			}else if(rankUpNum < 100000){
				rankUpTxt->runAction(MoveTo::create(0.4f,Point(180,356)));
				rankUp->runAction(MoveTo::create(0.4f,Point(363.5,356)));
			}else if(rankUpNum < 1000000){
				rankUpTxt->runAction(MoveTo::create(0.4f,Point(168,356)));
				rankUp->runAction(MoveTo::create(0.4f,Point(363.5,356)));
			}
		}

		if(animTime >= 53 && !hasShowkillMole){
			hasShowkillMole = true;
			if(killMoleNum == 0){
				killMoleTxt1->runAction(MoveTo::create(0.4f,Point(194.5-9,280)));
				killMoleTxt2->runAction(MoveTo::create(0.4f,Point(289.5+9,280)));
			}else if(killMoleNum < 10){
				killMoleTxt1->runAction(MoveTo::create(0.4f,Point(194.5-9,280)));
				killMoleTxt2->runAction(MoveTo::create(0.4f,Point(289.5+9,280)));
			}else if(killMoleNum < 100){
				killMoleTxt1->runAction(MoveTo::create(0.4f,Point(194.5-18,280)));
				killMoleTxt2->runAction(MoveTo::create(0.4f,Point(289.5+18,280)));
			}else if(killMoleNum < 1000){
				killMoleTxt1->runAction(MoveTo::create(0.4f,Point(194.5-27,280)));
				killMoleTxt2->runAction(MoveTo::create(0.4f,Point(289.5+27,280)));
			}else if(killMoleNum < 10000){
				killMoleTxt1->runAction(MoveTo::create(0.4f,Point(194.5-36,280)));
				killMoleTxt2->runAction(MoveTo::create(0.4f,Point(289.5+36,280)));
			}
			killMole->runAction(MoveTo::create(0.4f,Point(240,280)));
		}

		if(animTime >= 59 && !hasShowSaveFood){
			hasShowSaveFood = true;
			if(killMoleNum == 0){
				saveFoodTxt1->runAction(MoveTo::create(0.4f,Point(179.5,240)));
				saveFoodTxt2->runAction(MoveTo::create(0.4f,Point(287.5,240)));
				saveFood->runAction(MoveTo::create(0.4f,Point(227,240)));
			}else if(killMoleNum < 10){
				saveFoodTxt1->runAction(MoveTo::create(0.4f,Point(157.5,240)));
				saveFoodTxt2->runAction(MoveTo::create(0.4f,Point(319.5,240)));
				saveFood->runAction(MoveTo::create(0.4f,Point(232,240)));
			}else if(killMoleNum < 100){
				saveFoodTxt1->runAction(MoveTo::create(0.4f,Point(143.5,240)));
				saveFoodTxt2->runAction(MoveTo::create(0.4f,Point(323.5,240)));
				saveFood->runAction(MoveTo::create(0.4f,Point(227,240)));
			}else if(killMoleNum < 1000){
				saveFoodTxt1->runAction(MoveTo::create(0.4f,Point(139.5,240)));
				saveFoodTxt2->runAction(MoveTo::create(0.4f,Point(337.5,240)));
				saveFood->runAction(MoveTo::create(0.4f,Point(232,240)));
			}else if(killMoleNum < 10000){
				saveFoodTxt1->runAction(MoveTo::create(0.4f,Point(125.5,240)));
				saveFoodTxt2->runAction(MoveTo::create(0.4f,Point(341.5,240)));
				saveFood->runAction(MoveTo::create(0.4f,Point(227,240)));
			}
		}

		if(animTime >= 65 && !hasShowBtn){
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
	Audio::getInstance()->playSound("Music/click.ogg");
	Director::getInstance()->replaceScene(TransitionSlideInL::create(1,GameScene::create()));
}

void GameResultLayer::back(){
	if(!canClick){
		return;
	}
	Audio::getInstance()->playSound("Music/click.ogg");
	Director::getInstance()->replaceScene(TransitionFade::create(1,MenuScene::create()));
}


