#ifndef _PLAYERRANK_H_
#define _PLAYERRANK_H_
#include "cocos2d.h"


class PLAYERRANK{
public:
	static PLAYERRANK* getInstance();
	int getRankPer(int score);
	int getRankList(int score);
	const static int LEVEL_0 = 0;
	const static int LEVEL_1 = 2000;
	const static int LEVEL_2 = 2000;
	const static int LEVEL_3 = 40000;
	const static int LEVEL_4 = 80000;
	const static int LEVEL_5 = 100000;
	const static int LEVEL_6 = 120000;
	const static int LEVEL_7 = 160000;
private:
	PLAYERRANK();
private:
	static PLAYERRANK* _instance;
};


#endif
