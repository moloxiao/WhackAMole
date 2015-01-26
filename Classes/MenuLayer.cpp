#include "MenuLayer.h"
#include "GameScene.h"

bool MenuLayer::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("mouse_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	// 飘雪粒子效果
	//ParticleSnow* effect = ParticleSnow::create();
	//effect->setTotalParticles(100);
	//addChild(effect);

	 auto BtnStart = MenuItemImage::create(
		"btn-start.png",
        "btn-start.png",
        CC_CALLBACK_0(MenuLayer::startGame, this));
    

    // create menu, it's an autorelease object
    auto menu = Menu::create(BtnStart, NULL);
    menu->setPosition(visibleSize.width/2,100);
    this->addChild(menu, 1);

	// 将精灵表单添加到缓存
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("resources.plist");

	// 木槌动画
    Animation* malletAnimation = getAnimationByName("mallet", 0.05f, 3);
    AnimationCache::getInstance()->addAnimation(malletAnimation, "malletAnimation");

	return true;
}

void MenuLayer::startGame(){
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}

/**
 * 获得动画动作函数
 * animName：动画帧的名字
 * delay：动画帧与帧之间的间隔时间
 * animNum：动画帧的数量
 */
Animation* MenuLayer::getAnimationByName(std::string animName,float delay,int animNum){
    Animation* animation = Animation::create();
    // 循环从精灵帧缓存中获取与图片名称相对应的精灵帧组成动画
	for(unsigned int i = 1;i<=animNum;i++){
        // 获取动画图片名称，例如plane0.png
        std::string frameName = animName;
        frameName.append(StringUtils::format("%d",i)).append(".png");
		// 将单张图片添加为精灵帧（即动画帧）
		animation->addSpriteFrameWithFile(frameName.c_str());
    }
    // 设置动画播放的属性
	animation->setDelayPerUnit(delay);
	// 让精灵对象在动画执行完后恢复到最初状态
	animation->setRestoreOriginalFrame(true);
    return animation;
}