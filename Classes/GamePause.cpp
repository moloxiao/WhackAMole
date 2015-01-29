#include "GamePause.h"
#include "GameState.h"

bool GamePause::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//========================================
	ClippingNode* clippingNode = ClippingNode::create();
	Node* stencil = Node::create(); 

	auto Mole3X1 = Sprite::create("mouse_hole.png");
	Mole3X1->setPosition(90, 100);
	stencil->addChild(Mole3X1);
	clippingNode->setStencil(stencil);

	auto draw = DrawNode::create();
	draw->drawSolidRect(Vec2(0,0), Vec2(480,800), Color4F::BLACK);
	clippingNode->addChild(draw); 

	clippingNode->setInverted(true);     
	clippingNode->setAlphaThreshold(0.5f);

	this->addChild(clippingNode);

	//========================================
	

	auto btnPause = MenuItemImage::create(
		"b_helpc.png",
        "b_helpc_.png",
        CC_CALLBACK_0(GamePause::returnGame, this));
    auto menu = Menu::create(btnPause, NULL);
    menu->setPosition(visibleSize.width/2, 150);
    this->addChild(menu, 1);

	return true;
}

void GamePause::returnGame() {
	this->removeFromParentAndCleanup(true);
	GAMESTATE::getInstance()->setGamePause(false);
}


