#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class GameLayer : public Layer{
private:
	Vector<Sprite*> _mousesVector;
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void randomPopMoles(float delta);
    void setHit(Ref* pSender);	// ���ÿ����ô����
    void unHit(Ref* pSender);	// ���ò������ô����
};
#endif