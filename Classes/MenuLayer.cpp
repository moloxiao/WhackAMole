#include "MenuLayer.h"
#include "GameScene.h"
#include "Audio.h"
#include "CallAndroidMethod.h"
#include "SignIn.h"
#include "About.h"
#include "GAMEDATA.h"
#include "Chinese.h"
#include "SimpleAudioEngine.h"

bool MenuLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Audio::getInstance()->prepare();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("pr_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	// Ʈѩ����Ч��
	//ParticleSnow* effect = ParticleSnow::create();
	//effect->setTotalParticles(100);
	//addChild(effect);

	 auto BtnStart = MenuItemImage::create(
		"btn-start.png",
        "btn-start.png",
        CC_CALLBACK_0(MenuLayer::startGame, this));
    

    auto menu = Menu::create(BtnStart, NULL);
    menu->setPosition(visibleSize.width/2,200);
    this->addChild(menu, 1);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("resources.plist");

    Animation* malletAnimation = getAnimationByName("mallet", 0.05f, 3);
    AnimationCache::getInstance()->addAnimation(malletAnimation, "malletAnimation");
	Animation* laughAnimation = getAnimationByName("mole_laugh", 0.2f, 3);
	AnimationCache::getInstance()->addAnimation(laughAnimation, "laughAnimation");
	Animation* hitAnimation = getAnimationByName("mole_thump", 0.05f, 4);
	AnimationCache::getInstance()->addAnimation(hitAnimation, "hitAnimation");

	auto about = Label::create(ChineseWord("about"),"Arial",24);
	about->setPosition(450,40);
	about->setAnchorPoint(Point(1,0.5));
	this->addChild(about);

	auto aboutListener = EventListenerTouchOneByOne::create();
	aboutListener->onTouchBegan = CC_CALLBACK_2(MenuLayer::showAbout,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(aboutListener,about);

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
	MenuItemImage* soundEffectOn = MenuItemImage::create("sound_effect_on.png","sound_effect_on.png");
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
//	schedule(schedule_selector(MenuLayer::autoStartGame), 0.2f, 0, 0);

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
			Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
		}
    #endif
}

bool MenuLayer::showAbout(Touch* touch,Event* event){
	if(event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())){
		if(signIn->isVisible() || quitBg->isVisible()){
			return true;
		}
		aboutLayer->setVisible(true);
		return true;
	}
	return false;
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
