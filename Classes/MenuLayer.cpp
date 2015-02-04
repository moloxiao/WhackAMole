#include "MenuLayer.h"
#include "GameScene.h"
#include "Audio.h"
#include "CallAndroidMethod.h"
#include "SignIn.h"
#include "About.h"
#include "GAMEDATA.h"
#include "Chinese.h"
#include "SimpleAudioEngine.h"
#include "Power.h"

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
	power->setAnchorPoint(Point(0,0.5));
	this->addChild(power);

	auto powerNum = Power::getInstance();
	this->addChild(powerNum);

	auto btnBuyPower = MenuItemImage::create(
		"power_buy_btn_normal.png",
		"power_buy_btn_click.png",
		CC_CALLBACK_0(MenuLayer::buyPower, this));
	auto buyPowerMenu = Menu::create(btnBuyPower, NULL);
	buyPowerMenu->setPosition(135,749);
	this->addChild(buyPowerMenu);

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
//	Animation* laughAnimation = getAnimationByName("mole_laugh", 0.2f, 3);
//	AnimationCache::getInstance()->addAnimation(laughAnimation, "laughAnimation");
//	Animation* hitAnimation = getAnimationByName("mole_thump", 0.05f, 4);
//	AnimationCache::getInstance()->addAnimation(hitAnimation, "hitAnimation");

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
	musicMenu->setPosition(329,745);
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
	soundEffectMenu->setPosition(427,745);
	this->addChild(musicMenu,2);
	this->addChild(soundEffectMenu,2);

	quitBg = Sprite::create("sign_in_bg.png");
	quitBg->setPosition(244,400);
	quitBg->setVisible(false);
	this->addChild(quitBg,2);

	quitTitle = Sprite::create("quit_title.png");
	quitTitle->setPosition(244,566);
	quitTitle->setVisible(false);
	this->addChild(quitTitle,2);

	quitDesc = Sprite::create("quit_desc.png");
	quitDesc->setPosition(244,412);
	quitDesc->setVisible(false);
	this->addChild(quitDesc,2);

	MenuItemImage* confirmBtn = MenuItemImage::create(
		"btn_bg_normal.png","btn_bg_click.png",CC_CALLBACK_0(MenuLayer::quit,this)
		);
	confirmMenu = Menu::create(confirmBtn, NULL);
	confirmMenu->setPosition(338,283);
	confirmMenu->setVisible(false);
	this->addChild(confirmMenu,2);

	confirmTxt = Sprite::create("confirm_txt.png");
	confirmTxt->setPosition(338,283);
	confirmTxt->setVisible(false);
	this->addChild(confirmTxt,2);

	MenuItemImage* cancelBtn = MenuItemImage::create(
		"btn_bg_normal.png","btn_bg_click.png",CC_CALLBACK_0(MenuLayer::cancel,this)
		);
	cancelMenu = Menu::create(cancelBtn, NULL);
	cancelMenu->setPosition(142,283);
	cancelMenu->setVisible(false);
	this->addChild(cancelMenu,2);

	MenuItemImage* closeBtn = MenuItemImage::create(
		"close_btn_normal.png","close_btn_click.png",CC_CALLBACK_0(MenuLayer::cancel,this)
		);
	closeMenu = Menu::create(closeBtn, NULL);
	closeMenu->setPosition(430,587);
	closeMenu->setVisible(false);
	this->addChild(closeMenu,2);

	cancelTxt = Sprite::create("cancel_txt.png");
	cancelTxt->setPosition(142,283);
	cancelTxt->setVisible(false);
	this->addChild(cancelTxt,2);

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

	aboutBg = Sprite::create("result_bg.png");
	aboutBg->setPosition(240,400);
	this->addChild(aboutBg,3);

	aboutTitle1 = Sprite::create("about_title_1.png");
	aboutTitle1->setPosition(80,710);
	aboutTitle1->setAnchorPoint(Point(0,0.5));
	this->addChild(aboutTitle1,3);

	int mouse = GAMEDATA::getInstance()->getTotalMouseNum();

	mouseNum = LabelAtlas::create(String::createWithFormat("%d",mouse)->_string,"num_about.png",16,23,48);
	mouseNum->setAnchorPoint(Point(0,0.5));
	mouseNum->setPosition(80,670);
	this->addChild(mouseNum,3);

	aboutTitle2 = Sprite::create("about_title_2.png");
	aboutTitle2->setAnchorPoint(Point(0,0.5));
	if(mouse<10){
		aboutTitle2->setPosition(96,670);
	}else if(mouse<100){
		aboutTitle2->setPosition(112,670);
	}else if(mouse<1000){
		aboutTitle2->setPosition(128,670);
	}else if(mouse<10000){
		aboutTitle2->setPosition(144,670);
	}else if(mouse<100000){
		aboutTitle2->setPosition(160,670);
	}else if(mouse<1000000){
		aboutTitle2->setPosition(172,670);
	}
	this->addChild(aboutTitle2,3);

	aboutTitle3 = Sprite::create("about_title_3.png");
	aboutTitle3->setPosition(80,630);
	aboutTitle3->setAnchorPoint(Point(0,0.5));
	this->addChild(aboutTitle3,3);

	miceNum = LabelAtlas::create(String::createWithFormat("%d",mouse*1000)->_string,"num_about.png",16,23,48);
	miceNum->setAnchorPoint(Point(0,0.5));
	miceNum->setPosition(80,590);
	this->addChild(miceNum,3);

	aboutTitle4 = Sprite::create("about_title_4.png");
	if(mouse == 0){
		aboutTitle4->setPosition(102,590);
	}else if(mouse<10){
		aboutTitle4->setPosition(150,590);
	}else if(mouse<100){
		aboutTitle4->setPosition(166,590);
	}else if(mouse<1000){
		aboutTitle4->setPosition(178,590);
	}else if(mouse<10000){
		aboutTitle4->setPosition(194,590);
	}else if(mouse<100000){
		aboutTitle4->setPosition(210,590);
	}else if(mouse<1000000){
		aboutTitle4->setPosition(226,590);
	}
	aboutTitle4->setAnchorPoint(Point(0,0.5));
	this->addChild(aboutTitle4,3);

	aboutDesc = Sprite::create("about_desc.png");
	aboutDesc->setPosition(80,352);
	aboutDesc->setAnchorPoint(Point(0,0.5));
	this->addChild(aboutDesc,3);

	auto contiBtn = MenuItemImage::create(
		"btn_bg_normal.png","btn_bg_click.png",CC_CALLBACK_0(MenuLayer::startGameT,this)
		);
	contiMenu = Menu::create(contiBtn, NULL);
	contiMenu->setPosition(348,90);
	contiMenu->setAnchorPoint(Point(1,0.5));
	this->addChild(contiMenu,3);

	startTxt = Sprite::create("start_game_txt.png");
	startTxt->setPosition(449,90);
	startTxt->setAnchorPoint(Point(1,0.5));
	this->addChild(startTxt,3);

	auto backBtn = MenuItemImage::create(
		"btn_bg_normal.png","btn_bg_click.png",CC_CALLBACK_0(MenuLayer::hideAbout,this)
		);
	backMenu = Menu::create(backBtn, NULL);
	backMenu->setPosition(132,90);
	backMenu->setAnchorPoint(Point(0,0.5));
	this->addChild(backMenu,3);

	backTxt = Sprite::create("back_menu_txt.png");
	backTxt->setPosition(39,90);
	backTxt->setAnchorPoint(Point(0,0.5));
	this->addChild(backTxt,3);
	setAboutVisible(false);

	Audio::getInstance()->playBGM("Music/bg.mp3");
	return true;
}

void MenuLayer::hideAbout(){
	if(signIn->isVisible()){
		return;
	}
	Audio::getInstance()->playSound("Music/click.ogg");
	setAboutVisible(false);
}

void MenuLayer::startGameT(){
	if(signIn->isVisible() ){
		return;
	}
	Audio::getInstance()->playSound("Music/click.ogg");
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}

void MenuLayer::setAboutVisible(bool visible){
	aboutBg->setVisible(visible);
	aboutTitle1->setVisible(visible);
	aboutTitle2->setVisible(visible);
	aboutTitle3->setVisible(visible);
	aboutTitle4->setVisible(visible);
	mouseNum->setVisible(visible);
	miceNum->setVisible(visible);
	aboutDesc->setVisible(visible);
	backMenu->setVisible(visible);
	contiMenu->setVisible(visible);
	startTxt->setVisible(visible);
	backTxt->setVisible(visible);
}

void MenuLayer::startGame(){
	if(signIn->isVisible() || quitBg->isVisible() || aboutBg->isVisible()){
		return;
	}
	Audio::getInstance()->playSound("Music/click.ogg");
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}

void MenuLayer::buyPower(){
	if(signIn->isVisible() || aboutBg->isVisible()){
		return;
	}
	Audio::getInstance()->playSound("Music/click.ogg");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(2);
	#endif
}

void MenuLayer::showQuit(){
	if(signIn->isVisible() || aboutBg->isVisible()){
		return;
	}
	if(GAMEDATA::getInstance()->isPaySuccess()){
		quitBg->setVisible(true);
		quitDesc->setVisible(true);
		confirmMenu->setVisible(true);
		cancelMenu->setVisible(true);
		quitTitle->setVisible(true);
		confirmTxt->setVisible(true);
		cancelTxt->setVisible(true);
		closeMenu->setVisible(true);
	}else{
		if(hasShowQuitPay){
			quitBg->setVisible(true);
			quitDesc->setVisible(true);
			confirmMenu->setVisible(true);
			cancelMenu->setVisible(true);
			quitTitle->setVisible(true);
			confirmTxt->setVisible(true);
			cancelTxt->setVisible(true);
			closeMenu->setVisible(true);
		}else{
			hasShowQuitPay = true;
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				CallAndroidMethod::getInstance()->pay(6);
    		#endif
		}
	}
}

void MenuLayer::quit(){
	Audio::getInstance()->playSound("Music/click.ogg");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->startNativeNotify();
    #endif
	Director::getInstance()->end();
}

void MenuLayer::cancel(){
	Audio::getInstance()->playSound("Music/click.ogg");
	quitBg->setVisible(false);
	quitDesc->setVisible(false);
	confirmMenu->setVisible(false);
	cancelMenu->setVisible(false);
	quitTitle->setVisible(false);
	confirmTxt->setVisible(false);
	cancelTxt->setVisible(false);
	closeMenu->setVisible(false);
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
	Audio::getInstance()->playSound("Music/click.ogg");
	setAboutVisible(true);
}

void MenuLayer::getSoudState(CCObject* pSender){
	Audio::getInstance()->playSound("Music/click.ogg");
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
	Audio::getInstance()->playSound("Music/click.ogg");
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
