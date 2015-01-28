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

	 // �������㴥��������
    auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *unused_event){
		// ��touch����ת����Node����
		Point touchLocation = this->convertTouchToNodeSpace(touch);

		 // �������󼯺�
        for (auto* mole : _mousesVector) {
			// �����ǰ��ֻ�����tag���Ϊ0����ʾ�������ô���ô��ֱ�Ӽ����һ������
            if (mole->getTag() == 0 ) {
				continue;
			}
			// ���touch������Χ�ǵ���ʱ
            if (mole->getBoundingBox().containsPoint(touchLocation)) {
				// ����ľ鳣���ľ���ʾ���м�ĵ���ͷ��
                auto mallet = Sprite::create("mallet1.png");
				// ���ľ鳶���
                auto malletAnimation = Animate::create(AnimationCache::getInstance()->getAnimation("malletAnimation"));
				mallet->setScale(0.6f);
                mallet->setPosition(mole->getPosition().x+30, mole->getPosition().y+70);
                this->addChild(mallet, 1);
                // ����ľ鳶���
                mallet->runAction(Sequence::create(malletAnimation, CallFunc::create([=]{
					Audio::getInstance()->playSound("Music/normalhit.ogg");
					// ���󱻴��к󲥷�����Ч��
                    auto aswoon = ParticleSystemQuad::create("aswoon.plist");
                    aswoon->setPosition(mole->getPosition().x, mole->getPosition().y);
                    this->addChild(aswoon);
                    // ɾ��ľ�
                    this->removeChild(mallet);
                }), NULL));

				
				// ���󱻴��к��޸�tag���Ϊ0����ʾ�����Ѿ������У������ظ��ô�
                mole->setTag(0);
				// ����˳��ִ�в��ű����ж��������صض�����
				mole->stopAllActions();
				//auto scale2Action = ScaleTo::create(0.1f, 1.0f);
				
				auto hitAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("hitAnimation"));
				auto scale3Action = ScaleTo::create(0.1f, 0.0f);
                mole->runAction(Sequence::create( hitAnimate, scale3Action, CallFuncN::create(CC_CALLBACK_1(GameLayer::unHit, this)), NULL));

				// TODO : ������Ϸ����
				gameScore += gameScoreAdd;
				gameScoreAdd +=DEFAUL_SCORE_ADD;
				menu->updateGameScore(gameScore);
			}
		}
		return true;
	};
	// ��Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	// ���TopMenu
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

// ����������
void GameLayer::randomPopMoles(float delta){
	if(GAMESTATE::getInstance()->getGamePause() || GAMESTATE::getInstance()->getGameOver()) {
		return ;
	}
	for (auto mole : _mousesVector) {
        int temp = CCRANDOM_0_1()*10000;
        if ( temp % 9 == 0)
        {
            // getNumberOfRunningActions����0��˵���õ���û��ִ�ж�����Ҳ���ǻ�û������������������0��˵�������Ѿ�������ˣ������õ����������
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

// �ڵ���Цʱ�����ÿ����ô����
void GameLayer::setHit(Ref* pSender)
{
    Sprite* mole = (Sprite*)pSender;
    mole->setTag(1);
    // TODO : ���ŵ���Ц������Ч
    //SimpleAudioEngine::getInstance()->playEffect("laugh.caf");
}

// �ڵ���Ц��֮�����ò������ô����
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
