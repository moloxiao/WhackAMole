#include "GamePause.h"
#include "GameState.h"
#include "MenuScene.h"
#include "CallAndroidMethod.h"

bool GamePause::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//========================================
//	ClippingNode* clippingNode = ClippingNode::create();
//	Node* stencil = Node::create();
//
//	auto Mole3X1 = Sprite::create("mouse_hole.png");
//	Mole3X1->setPosition(90, 100);
//	stencil->addChild(Mole3X1);
//	clippingNode->setStencil(stencil);
//
//	auto draw = DrawNode::create();
//	draw->drawSolidRect(Vec2(0,0), Vec2(480,800), Color4F::BLACK);
//	clippingNode->addChild(draw);
//
//	clippingNode->setInverted(true);
//	clippingNode->setAlphaThreshold(0.5f);
//
//	this->addChild(clippingNode);

	//========================================
	

	auto outBg = Sprite::create("black.png");
	outBg->setPosition(240,400);
	outBg->setScaleX(480);
	outBg->setScaleY(800);
	this->addChild(outBg);

//	auto bg = Scale9Sprite::create("pause_bg.9.png");
//	bg->setPosition(240,400);
//	bg->setContentSize(440,300);
//	this->addChild(bg);

	auto propsBtn = MenuItemImage::create(
		"props.png","props.png",CC_CALLBACK_0(GamePause::pay,this)
		);
	auto propsMenu = Menu::create(propsBtn, NULL);
	propsMenu->setPosition(240,420);
	propsMenu->setAnchorPoint(Point(0.5,0.5));
	this->addChild(propsMenu);

	auto contiBtn = MenuItemImage::create(
		"btn_bg_normal.png","btn_bg_click.png",CC_CALLBACK_0(GamePause::returnGame,this)
		);
	auto contiMenu = Menu::create(contiBtn, NULL);
	contiMenu->setPosition(348,238);
	contiMenu->setAnchorPoint(Point(1,0.5));
	this->addChild(contiMenu);

	auto contiTxt = Sprite::create("conti_game_txt.png");
	contiTxt->setPosition(429,238);
	contiTxt->setAnchorPoint(Point(1,0.5));
	this->addChild(contiTxt);

	auto backBtn = MenuItemImage::create(
		"btn_bg_normal.png","btn_bg_click.png",CC_CALLBACK_0(GamePause::backMenu,this)
		);
	auto backMenu = Menu::create(backBtn, NULL);
	backMenu->setPosition(132,238);
	backMenu->setAnchorPoint(Point(0,0.5));
	this->addChild(backMenu);

	auto backTxt = Sprite::create("back_menu_txt.png");
	backTxt->setPosition(47,238);
	backTxt->setAnchorPoint(Point(0,0.5));
	this->addChild(backTxt);

	return true;
}

void GamePause::returnGame() {
	this->removeFromParentAndCleanup(true);
	GAMESTATE::getInstance()->setGamePause(false);
}

void GamePause::backMenu(){
	GAMESTATE::getInstance()->setGamePause(false);
	GAMESTATE::getInstance()->setGameOver(true);
	Director::getInstance()->replaceScene(TransitionFade::create(1,MenuScene::create()));
}

void GamePause::pay(){
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(1);
	#endif
}


