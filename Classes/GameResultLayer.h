#ifndef _GAMERESULTLAYER_H_
#define _GAMERESULTLAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class GameResultLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameResultLayer);
	void update(float delta);

	void contiGame();
	void back();
private:
	bool canClick;
	int gameScore;
	float scoreNum;
	float animTime;
	LabelAtlas* score;
	bool hasShowScore;
	Sprite* rankTxt;
	LabelAtlas* rank;
	bool hasShowRank;
	Sprite* scoreUpTxt;
	LabelAtlas* scoreUp;
	Sprite* rankUpTxt;
	LabelAtlas* rankUp;
	bool hasShowScoreUp;
	Sprite* killMoleTxt1;
	Sprite* killMoleTxt2;
	LabelAtlas* killMole;
	Sprite* saveFoodTxt1;
	Sprite* saveFoodTxt2;
	LabelAtlas* saveFood;
	bool hasShowkillMole;
	bool hasShowSaveFood;
	Menu* contiMenu;
	Menu* backMenu;
	Sprite* contiTxt;
	Sprite* backTxt;
	bool hasShowBtn;
	int rankNum;
	int scoreUpNum;
	int rankUpNum;
	int killMoleNum;
	Sprite* starLeft;
	Sprite* starMiddle;
	Sprite* starRight;
	bool showStar1;
	bool showStar2;
	bool showStar3;
};
#endif
