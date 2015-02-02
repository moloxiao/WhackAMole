#include "MenuLayer.h"
#include "GameScene.h"
#include "Audio.h"
#include "CallAndroidMethod.h"
#include "SignIn.h"
#include "About.h"
#include "GAMEDATA.h"
#include "Chinese.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

bool MenuLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Audio::getInstance()->prepare();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("menu_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	// Ʈѩ����Ч��
	//ParticleSnow* effect = ParticleSnow::create();
	//effect->setTotalParticles(100);
	//addChild(effect);

	auto power = Sprite::create("power.png");
	power->setPosition(32,749);
	this->addChild(power);

	auto powerNum = LabelAtlas::create(String::createWithFormat(":%d",GAMEDATA::getInstance()->getPowerValue())->_string,"num_power.png",
			24,29,48);
	powerNum->setAnchorPoint(Point(0,0.5));
	powerNum->setPosition(62,749);
	this->addChild(powerNum);

	auto cat = Sprite::create("cat.png");
	cat->setPosition(visibleSize.width/2,280);
	this->addChild(cat);

	auto titleDay = Sprite::create("title_1.png");
	titleDay->setPosition(240,629);
	this->addChild(titleDay);

	auto titleDa = Sprite::create("title_2.png");
	titleDa->setPosition(90,498);
	this->addChild(titleDa);

	auto titleDi = Sprite::create("title_3.png");
	titleDi->setPosition(243,512);
	this->addChild(titleDi);

	auto titleShu = Sprite::create("title_4.png");
	titleShu->setPosition(398,501);
	this->addChild(titleShu);

	auto BtnStart = MenuItemImage::create(
		"btn_bg_normal.png",
        "btn_bg_click.png",
        CC_CALLBACK_0(MenuLayer::startGame, this));
    auto startMenu = Menu::create(BtnStart, NULL);
    startMenu->setPosition(visibleSize.width/2,300);
    this->addChild(startMenu, 1);

    auto startGameTxt = Sprite::create("start_game_txt.png");
    startGameTxt->setPosition(visibleSize.width/2,300);
    this->addChild(startGameTxt, 1);

    auto BtnAbout = MenuItemImage::create(
    		"btn_bg_normal.png",
            "btn_bg_click.png",
            CC_CALLBACK_0(MenuLayer::showAbout, this));
	auto aboutMenu = Menu::create(BtnAbout, NULL);
	aboutMenu->setPosition(visibleSize.width/2,200);
	this->addChild(aboutMenu,1);

	auto aboutTxt = Sprite::create("game_about_txt.png");
	aboutTxt->setPosition(visibleSize.width/2,200);
	this->addChild(aboutTxt, 1);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("resources.plist");

    Animation* malletAnimation = getAnimationByName("mallet", 0.05f, 3);
    AnimationCache::getInstance()->addAnimation(malletAnimation, "malletAnimation");
	Animation* laughAnimation = getAnimationByName("mole_laugh", 0.2f, 3);
	AnimationCache::getInstance()->addAnimation(laughAnimation, "laughAnimation");
	Animation* hitAnimation = getAnimationByName("mole_thump", 0.05f, 4);
	AnimationCache::getInstance()->addAnimation(hitAnimation, "hitAnimation");

	MenuItemImage* musicBtnOn = MenuItemImage::create("bg_music_open.png","bg_music_open.png");
	MenuItemImage* musicBtnOff = MenuItemImage::create("bg_music_close.png","bg_music_close.png");
	MenuItemToggle* musicTog = MenuItemToggle::createWithTarget(this,menu_selector(MenuLayer::getMusicState),musicBtnOn,musicBtnOff,NULL);
	 if (GAMEDATA::getInstance()->getMusicState())
		{
			musicTog->setSelectedIndex(0);
		}
		else
		{
			musicTog->setSelectedIndex(1);
		}
	auto musicMenu = Menu::create(musicTog,NULL);
	musicMenu->setPosition(349,760);
	MenuItemImage* soundEffectOn = MenuItemImage::create("sound_effect_open.png","sound_effect_open.png");
	MenuItemImage* soundEffectOff = MenuItemImage::create("sound_effect_close.png","sound_effect_close.png");
	MenuItemToggle* soundEffectTog = MenuItemToggle::createWithTarget(this,menu_selector(MenuLayer::getSoudState),soundEffectOn,soundEffectOff,NULL);
	 if (GAMEDATA::getInstance()->getSoundState())
		{
			soundEffectTog->setSelectedIndex(0);
		}
		else
		{
			soundEffectTog->setSelectedIndex(1);
		}
	auto soundEffectMenu = Menu::create(soundEffectTog,NULL);
	soundEffectMenu->setPosition(427,760);
	this->addChild(musicMenu,2);
	this->addChild(soundEffectMenu,2);

	quitBg = Sprite::create("quit_bg.png");
	quitBg->setPosition(240,116);
	quitBg->setVisible(false);
	this->addChild(quitBg,2);

	quitDesc = Sprite::create("quit_desc.png");
	quitDesc->setPosition(240,144);
	quitDesc->setVisible(false);
	this->addChild(quitDesc,2);

	MenuItemImage* confirmBtn = MenuItemImage::create(
		"quit_confirm_up.png","quit_confirm_down.png",CC_CALLBACK_0(MenuLayer::quit,this)
		);
	confirmMenu = Menu::create(confirmBtn, NULL);
	confirmMenu->setPosition(316,71);
	confirmMenu->setVisible(false);
	this->addChild(confirmMenu,2);

	MenuItemImage* cancelBtn = MenuItemImage::create(
		"quit_cancel_up.png","quit_cancel_down.png",CC_CALLBACK_0(MenuLayer::cancel,this)
		);
	cancelMenu = Menu::create(cancelBtn, NULL);
	cancelMenu->setPosition(164,71);
	cancelMenu->setVisible(false);
	this->addChild(cancelMenu,2);

	this->setKeypadEnabled(true);
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
			{
			case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
				showQuit();
				break;
			default:
				break;
			}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	signIn = SignIn::getInstance();
	signIn->setVisible(false);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if(CallAndroidMethod::getInstance()->isSignToday()){
			CCLOG("result:%d",2);
		}else{
			CCLOG("result:%d",1);
			signIn->setVisible(true);
			this->addChild(signIn,5);
		}
	#endif
	schedule(schedule_selector(MenuLayer::autoStartGame), 0.2f, 0, 0);

	aboutLayer = About::getInstance();
	this->addChild(aboutLayer,3);
	aboutLayer->setVisible(false);

	Audio::getInstance()->playBGM("Music/bg.mp3");
	return true;
}

void MenuLayer::startGame(){
	Audio::getInstance()->playSound("Music/click.ogg");
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}

void MenuLayer::showQuit(){
	if(aboutLayer->isVisible()){
		return;
	}
	if(GAMEDATA::getInstance()->isPaySuccess()){
		quitBg->setVisible(true);
		quitDesc->setVisible(true);
		confirmMenu->setVisible(true);
		cancelMenu->setVisible(true);
	}else{
		if(hasShowQuitPay){
			quitBg->setVisible(true);
			quitDesc->setVisible(true);
			confirmMenu->setVisible(true);
			cancelMenu->setVisible(true);
		}else{
			hasShowQuitPay = true;
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				CallAndroidMethod::getInstance()->pay(1);
    		#endif
		}
	}
}

void MenuLayer::quit(){
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->startNativeNotify();
    #endif
	Director::getInstance()->end();
}

void MenuLayer::cancel(){
	quitBg->setVisible(false);
	quitDesc->setVisible(false);
	confirmMenu->setVisible(false);
	cancelMenu->setVisible(false);
}

void MenuLayer::autoStartGame(float dt){
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if(CallAndroidMethod::getInstance()->notSignToday()){

		}else{
			if(GAMEDATA::getInstance()->isFirstLogin() && GAMEDATA::getInstance()->getPlayRounds()<=2){
				Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
			}
		}
    #endif
}

void MenuLayer::showAbout(){
	if(signIn->isVisible() || quitBg->isVisible()){
		return;
	}
	aboutLayer->setVisible(true);
}

void MenuLayer::getSoudState(CCObject* pSender){
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;

    if (temp->getSelectedIndex()==1)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		GAMEDATA::getInstance()->setSoundState(false);
    }
    if (temp->getSelectedIndex()==0)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		GAMEDATA::getInstance()->setSoundState(true);
    }
}

void MenuLayer::getMusicState(CCObject* pSender){
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;
    if (temp->getSelectedIndex()==1)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        GAMEDATA::getInstance()->setMusicState(false);
    }
    if (temp->getSelectedIndex()==0)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        GAMEDATA::getInstance()->setMusicState(true);
    }
}

Animation* MenuLayer::getAnimationByName(std::string animName,float delay,int animNum){
    Animation* animation = Animation::create();

	for(unsigned int i = 1;i<=animNum;i++){

        std::string frameName = animName;
        frameName.append(StringUtils::format("%d",i)).append(".png");
		animation->addSpriteFrameWithFile(frameName.c_str());
    }
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(true);
    return animation;
}
