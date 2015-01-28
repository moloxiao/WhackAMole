#include "MenuLayer.h"
#include "GameScene.h"
#include "Audio.h"
#include "CallAndroidMethod.h"

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
    

    // create menu, it's an autorelease object
    auto menu = Menu::create(BtnStart, NULL);
    menu->setPosition(visibleSize.width/2,100);
    this->addChild(menu, 1);

	// ���������ӵ�����
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("resources.plist");

	// ľ鳶���
    Animation* malletAnimation = getAnimationByName("mallet", 0.05f, 3);
    AnimationCache::getInstance()->addAnimation(malletAnimation, "malletAnimation");
	Animation* laughAnimation = getAnimationByName("mole_laugh", 0.2f, 3);
	AnimationCache::getInstance()->addAnimation(laughAnimation, "laughAnimation");
	Animation* hitAnimation = getAnimationByName("mole_thump", 0.05f, 4);
	AnimationCache::getInstance()->addAnimation(hitAnimation, "hitAnimation");

	Audio::getInstance()->playBGM("Music/bg.mp3");
	return true;
}

void MenuLayer::startGame(){
	Audio::getInstance()->playSound("Music/click.ogg");
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}

/**
 * ��ö�����������
 * animName������֡������
 * delay������֡��֮֡��ļ��ʱ��
 * animNum������֡������
 */
Animation* MenuLayer::getAnimationByName(std::string animName,float delay,int animNum){
    Animation* animation = Animation::create();
    // ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
	for(unsigned int i = 1;i<=animNum;i++){
        // ��ȡ����ͼƬ���ƣ�����plane0.png
        std::string frameName = animName;
        frameName.append(StringUtils::format("%d",i)).append(".png");
		// ������ͼƬ���Ϊ����֡��������֡��
		animation->addSpriteFrameWithFile(frameName.c_str());
    }
    // ���ö������ŵ�����
	animation->setDelayPerUnit(delay);
	// �þ�������ڶ���ִ�����ָ������״̬
	animation->setRestoreOriginalFrame(true);
    return animation;
}
