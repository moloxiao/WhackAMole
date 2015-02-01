#include "GameLayer.h"
#include "GameResultScene.h"
#include "GAMEDATA.h"
#include "GameState.h"
#include "Audio.h"
#include "FloatWord.h"
#include "Chinese.h"

bool GameLayer::init(){
	if(!Layer::init()){
		return false;
	}
	GAMEDATA::getInstance()->setPlayRounds(GAMEDATA::getInstance()->getPlayRounds()+1);
		int powerValue = GAMEDATA::getInstance()->getPowerValue();
		if(powerValue == 0){
			//TODO 启购买体力值的支付
			powerValue = 1;
		}
		GAMEDATA::getInstance()->setPowerValue(powerValue-1);
	Audio::getInstance()->playBGM("Music/fightbg.mp3");

	gameTime = DEFAULT_GAME_TIME;
	GAMESTATE::getInstance()->reset();

	gameScore = 0;
	gameScoreAdd = DEFAUL_SCORE_ADD;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("mouse_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	for(int i=0; i< 4;i++) {
		auto Mole3X1 = Sprite::create("mouse_hole.png");
		Mole3X1->setPosition(90, 100 + i*160);
		this->addChild(Mole3X1, 0);
		auto Mouse3X1 = Sprite::create("mole_1.png");
		Mouse3X1->setPosition(90, 130 + i*160);
		Mouse3X1->setScale(0);
		Mouse3X1->setTag(0);
		this->addChild(Mouse3X1, 1);
		_mousesVector.pushBack(Mouse3X1);
	}

	for(int i=0; i< 4;i++) {
		auto Mole3X1 = Sprite::create("mouse_hole.png");
		Mole3X1->setPosition(visibleSize.width/2, 100 + i*160);
		this->addChild(Mole3X1, 0);
		auto Mouse3X1 = Sprite::create("mole_1.png");
		Mouse3X1->setPosition(visibleSize.width/2, 130 + i*160);
		Mouse3X1->setScale(0);
		Mouse3X1->setTag(0);
		this->addChild(Mouse3X1, 1);
		_mousesVector.pushBack(Mouse3X1);
	}

	for(int i=0; i< 4;i++) {
		auto Mole3X1 = Sprite::create("mouse_hole.png");
		Mole3X1->setPosition(visibleSize.width-90, 100 + i*160);
		this->addChild(Mole3X1, 0);
		auto Mouse3X1 = Sprite::create("mole_1.png");
		Mouse3X1->setPosition(visibleSize.width-90, 130 + i*160);
		Mouse3X1->setScale(0);
		Mouse3X1->setTag(0);
		this->addChild(Mouse3X1, 1);
		_mousesVector.pushBack(Mouse3X1);
	}

	 this->schedule(schedule_selector(GameLayer::randomPopMoles), 1.0f);

	 // 锟斤拷锟斤拷锟斤拷锟姐触锟斤拷锟斤拷锟斤拷锟斤拷
    auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *unused_event){
		// 锟斤拷touch锟斤拷锟斤拷转锟斤拷锟斤拷Node锟斤拷锟斤拷
		Point touchLocation = this->convertTouchToNodeSpace(touch);

		 // 锟斤拷锟斤拷锟斤拷锟襟集猴拷
        for (auto* mole : _mousesVector) {
			// 锟斤拷锟斤拷锟角帮拷锟街伙拷锟斤拷锟斤拷tag锟斤拷锟轿�0锟斤拷锟斤拷示锟斤拷锟斤拷锟斤拷锟矫达拷锟斤拷么锟斤拷直锟接硷拷锟斤拷锟揭伙拷锟斤拷锟斤拷锟�
            if (mole->getTag() == 0 ) {
				continue;
			}
			// 锟斤拷锟絫ouch锟斤拷锟斤拷锟斤拷围锟角碉拷锟斤拷时
            if (mole->getBoundingBox().containsPoint(touchLocation)) {
				// 锟斤拷锟斤拷木槌ｏ拷锟斤拷木锟斤拷锟绞撅拷锟斤拷屑锟侥碉拷锟斤拷头锟斤拷
                auto mallet = Sprite::create("mallet1.png");
				// 锟斤拷锟侥鹃扯锟斤拷锟�
                auto malletAnimation = Animate::create(AnimationCache::getInstance()->getAnimation("malletAnimation"));
				mallet->setScale(0.6f);
                mallet->setPosition(mole->getPosition().x+30, mole->getPosition().y+70);
                this->addChild(mallet, 1);
                // 锟斤拷锟斤拷木槌讹拷锟斤拷
                mallet->runAction(Sequence::create(malletAnimation, CallFunc::create([=]{
					Audio::getInstance()->playSound("Music/normalhit.ogg");
					// 锟斤拷锟襟被达拷锟叫后播凤拷锟斤拷锟斤拷效锟斤拷
                    auto aswoon = ParticleSystemQuad::create("aswoon.plist");
                    aswoon->setPosition(mole->getPosition().x, mole->getPosition().y);
                    this->addChild(aswoon);
                    // 删锟斤拷木锟�
                    this->removeChild(mallet);
                }), NULL));

				
				// 锟斤拷锟襟被达拷锟叫猴拷锟睫革拷tag锟斤拷锟轿�0锟斤拷锟斤拷示锟斤拷锟斤拷锟窖撅拷锟斤拷锟斤拷锟叫ｏ拷锟斤拷锟斤拷锟截革拷锟矫达拷
                mole->setTag(0);
				// 锟斤拷锟斤拷顺锟斤拷执锟叫诧拷锟脚憋拷锟斤拷锟叫讹拷锟斤拷锟斤拷锟斤拷锟截地讹拷锟斤拷锟斤拷
				mole->stopAllActions();
				//auto scale2Action = ScaleTo::create(0.1f, 1.0f);
				
				auto hitAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("hitAnimation"));
				auto scale3Action = ScaleTo::create(0.1f, 0.0f);
                mole->runAction(Sequence::create( hitAnimate, scale3Action, CallFuncN::create(CC_CALLBACK_1(GameLayer::unHit, this)), NULL));

				// TODO : 锟斤拷锟斤拷锟斤拷戏锟斤拷锟斤拷
				gameScore += gameScoreAdd;
				gameScoreAdd +=DEFAUL_SCORE_ADD;
				menu->updateGameScore(gameScore);
			}
		}
		return true;
	};
	// 锟斤拷蛹锟斤拷锟斤拷锟�
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	// 锟斤拷锟絋opMenu
	menu = TopMenu::getInstance();
	this->addChild(menu, 10);
	menu->updateGameScore(gameScore);
	menu->updateGameTime(gameTime);

	this->schedule(schedule_selector(GameLayer::updateGameTime), 1.0f, kRepeatForever, 0);

	
	GAMESTATE::getInstance()->setGamePause(true);

	FloatWord* leftStarMsg1 = FloatWord::create(ChineseWord("stargame"), 
		50,Point(-100.0f, visibleSize.height/2));
	this->addChild(leftStarMsg1, 100);
	leftStarMsg1->floatInOut(0.4f, 1.0f, 1.0f,
				[=](){
					GAMESTATE::getInstance()->setGamePause(false);
				});

	return true;
}

// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
void GameLayer::randomPopMoles(float delta){
	if(GAMESTATE::getInstance()->getGamePause() || GAMESTATE::getInstance()->getGameOver()) {
		return ;
	}
	for (auto mole : _mousesVector) {
        int temp = CCRANDOM_0_1()*10000;
        if ( temp % 9 == 0)
        {
            // getNumberOfRunningActions锟斤拷锟斤拷0锟斤拷说锟斤拷锟矫碉拷锟斤拷没锟斤拷执锟叫讹拷锟斤拷锟斤拷也锟斤拷锟角伙拷没锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷0锟斤拷说锟斤拷锟斤拷锟斤拷锟窖撅拷锟斤拷锟斤拷锟斤拷耍锟斤拷锟斤拷锟斤拷玫锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
			if (mole->getNumberOfRunningActions() == 0 && mole->getTag() == 0)
            {
				auto scale1Action = ScaleTo::create(0.2f, 1.0f);
				auto laughAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("laughAnimation"));
				auto scale2Action = ScaleTo::create(2.5f, 1.0f);
				auto scale3Action = ScaleTo::create(0.2f, 0.0f);
				mole->runAction(Sequence::create(
					scale1Action, 
					CallFuncN::create(CC_CALLBACK_1(GameLayer::setHit, this)),
					laughAnimate,
					scale2Action,
					CallFuncN::create(CC_CALLBACK_1(GameLayer::unHit, this)),
					scale3Action, 
					NULL));
			}

		}
		
	}
}

// 锟节碉拷锟斤拷笑时锟斤拷锟斤拷锟矫匡拷锟斤拷锟矫达拷锟斤拷锟�
void GameLayer::setHit(Ref* pSender)
{
    Sprite* mole = (Sprite*)pSender;
    mole->setTag(1);
    // TODO : 锟斤拷锟脚碉拷锟斤拷笑锟斤拷锟斤拷锟斤拷效
    //SimpleAudioEngine::getInstance()->playEffect("laugh.caf");
}

// 锟节碉拷锟斤拷笑锟斤拷之锟斤拷锟斤拷锟矫诧拷锟斤拷锟斤拷锟矫达拷锟斤拷锟�
void GameLayer::unHit(Ref* pSender)
{
    Sprite* mole = (Sprite*)pSender;
    mole->setTag(0);
}

void GameLayer::toResultScene() {
	GAMEDATA::getInstance()->setGameScore(gameScore);
	Director::getInstance()->replaceScene(TransitionSlideInR::create(1,GameResultScene::create()));
}

void GameLayer::updateGameTime(float delta) {
	if(!GAMESTATE::getInstance()->getGameOver() && !GAMESTATE::getInstance()->getGamePause() && gameTime > 0) {
		gameTime--;
	}
	
	if(!GAMESTATE::getInstance()->getGameOver() && gameTime <= 0) {
		gameTime = 0;
		GAMESTATE::getInstance()->setGameOver(true);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		FloatWord* leftStarMsg1 = FloatWord::create(ChineseWord("gameover"), 
		50,Point(-100.0f, visibleSize.height/2));
		this->addChild(leftStarMsg1, 100);
		leftStarMsg1->floatInOut(0.4f, 0.0f, 1.0f,
				[=](){
					toResultScene();
				});
		
	}
	menu->updateGameTime(gameTime);
}
