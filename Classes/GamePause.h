#ifndef _GAMEPAUSE_H_
#define _GAMEPAUSE_H_
#include <string>
#include "cocos2d.h"

using namespace cocos2d;

class GamePause : public Layer {
public:
	virtual bool init();
	CREATE_FUNC(GamePause);
	void returnGame();
	void backMenu();
	void pay();
private:
};
#endif
