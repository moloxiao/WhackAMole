#include "GameLayer.h"
#include "GameResultScene.h"
#include "GAMEDATA.h"
#include "GameState.h"

bool GameLayer::init(){
	if(!Layer::init()){
		return false;
	}

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
		Mouse3X1->setPosition(90, 140 + i*160);
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
		Mouse3X1->setPosition(visibleSize.width/2, 140 + i*160);
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
		Mouse3X1->setPosition(visibleSize.width-90, 140 + i*160);
		Mouse3X1->setScale(0);
		Mouse3X1->setTag(0);
		this->addChild(Mouse3X1, 1);
		_mousesVector.pushBack(Mouse3X1);
	}

	 this->schedule(schedule_selector(GameLayer::randomPopMoles), 1.0f);

	 // 创建单点触摸监听器
    auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *unused_event){
		// 把touch坐标转换成Node坐标
		Point touchLocation = this->convertTouchToNodeSpace(touch);

		 // 遍历地鼠集合
        for (auto* mole : _mousesVector) {
			// 如果当前这只地鼠的tag标记为0，表示不可以敲打，那么就直接检查下一个地鼠
            if (mole->getTag() == 0 ) {
				continue;
			}
			// 如果touch触碰范围是地鼠时
            if (mole->getBoundingBox().containsPoint(touchLocation)) {
				// 创建木槌，将木槌显示在中间的地鼠头上
                auto mallet = Sprite::createWithSpriteFrameName("mallet1.png");
				// 获得木槌动画
                auto malletAnimation = Animate::create(AnimationCache::getInstance()->getAnimation("malletAnimation"));
				mallet->setScale(0.6f);
                mallet->setPosition(mole->getPosition().x+40, mole->getPosition().y+90);
                this->addChild(mallet, 1);
                // 播放木槌动画
                mallet->runAction(Sequence::create(malletAnimation, CallFunc::create([=]{
					// 地鼠被打中后播放粒子效果
                    auto aswoon = ParticleSystemQuad::create("aswoon.plist");
                    aswoon->setPosition(mole->getPosition().x, mole->getPosition().y);
                    this->addChild(aswoon);
                    // 删除木槌
                    this->removeChild(mallet);
                }), NULL));

				
				// 地鼠被打中后，修改tag标记为0，表示地鼠已经被打中，不能重复敲打
                mole->setTag(0);
				// 地鼠顺序执行播放被打中动画和缩回地洞动作
				mole->stopAllActions();
				auto scale2Action = ScaleTo::create(0.1f, 0.8f);
				auto scale3Action = ScaleTo::create(0.2f, 0.0f);
                mole->runAction(Sequence::create(scale2Action, scale3Action, CallFuncN::create(CC_CALLBACK_1(GameLayer::unHit, this)), NULL));

				// TODO : 增加游戏分数
				gameScore += gameScoreAdd;
				gameScoreAdd +=DEFAUL_SCORE_ADD;
				menu->updateGameScore(gameScore);
			}
		}
		return true;
	};
	// 添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	// 添加TopMenu
	menu = TopMenu::getInstance();
	this->addChild(menu, 10);
	menu->updateGameScore(gameScore);
	menu->updateGameTime(gameTime);

	this->schedule(schedule_selector(GameLayer::updateGameTime), 1.0f, kRepeatForever, 0);

	return true;
}

// 随机钻出地鼠
void GameLayer::randomPopMoles(float delta){
	for (auto mole : _mousesVector) {
        int temp = CCRANDOM_0_1()*10000;
        if ( temp % 9 == 0)
        {
            // getNumberOfRunningActions等于0，说明该地鼠并没有执行动作，也就是还没有钻出来，如果不等于0，说明地鼠已经钻出来了，则不再让地鼠钻出来。
			if (mole->getNumberOfRunningActions() == 0 && mole->getTag() == 0)
            {
				auto scale1Action = ScaleTo::create(0.2f, 0.8f);
				auto scale2Action = ScaleTo::create(3.6f, 0.8f);
				auto scale3Action = ScaleTo::create(0.2f, 0.0f);
				mole->runAction(Sequence::create(
					scale1Action, 
					CallFuncN::create(CC_CALLBACK_1(GameLayer::setHit, this)),
					scale2Action,
					CallFuncN::create(CC_CALLBACK_1(GameLayer::unHit, this)),
					scale3Action, 
					NULL));
			}

		}
		
	}
}

// 在地鼠笑时，设置可以敲打地鼠
void GameLayer::setHit(Ref* pSender)
{
    Sprite* mole = (Sprite*)pSender;
    mole->setTag(1);
    // TODO : 播放地鼠“笑”的音效
    //SimpleAudioEngine::getInstance()->playEffect("laugh.caf");
}

// 在地鼠笑完之后，设置不可以敲打地鼠
void GameLayer::unHit(Ref* pSender)
{
    Sprite* mole = (Sprite*)pSender;
    mole->setTag(0);
}

void GameLayer::toResultScene() {
	GAMEDATA::getInstance()->setGameScore(gameScore);
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameResultScene::create()));
}

void GameLayer::updateGameTime(float delta) {
	if(!GAMESTATE::getInstance()->getGameOver() && !GAMESTATE::getInstance()->getGamePause() && gameTime > 0) {
		gameTime--;
	}
	
	if(!GAMESTATE::getInstance()->getGameOver() && gameTime <= 0) {
		gameTime = 0;
		GAMESTATE::getInstance()->setGameOver(true);
		toResultScene();
	}
	menu->updateGameTime(gameTime);
}
