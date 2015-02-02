#ifndef _POWER_H_
#define _POWER_H_
#include <string>
#include "cocos2d.h"
using namespace cocos2d;
class Power : public Node{
public:
	static Power* getInstance();
	virtual bool init();
	void refreshPower();
private:
	static Power* _instance;
	LabelAtlas* powerNum;
private:
	Power();

};
#endif
