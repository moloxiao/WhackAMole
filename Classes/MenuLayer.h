#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class MenuLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(MenuLayer);
	void startGame();

	/** 
     获得动画函数 
     第一个参数：动画名称
     第二个参数：间隔事件
     第三个参数：动画图片数量
     */
    Animation* getAnimationByName(std::string animName,float delay,int animNum);
};
#endif