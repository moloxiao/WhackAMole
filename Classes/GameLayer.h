#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_


#include "cocos2d.h"
#include "TopMenu.h"

using namespace cocos2d;

class GameLayer : public Layer{
	
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void randomPopMoles(float delta);
    void setHit(Ref* pSender);	// ���ÿ����ô����
    void unHit(Ref* pSender);	// ���ò������ô����
	void toResultScene();
private:
	Vector<Sprite*> _mousesVector;
	TopMenu* menu;
};
#endif