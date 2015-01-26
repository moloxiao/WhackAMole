#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

class GAMEDATA{
public:
	static GAMEDATA* getInstance();
	void setGameScore(int score);
	int getGameScore();
private:
	GAMEDATA();
	void init();
	static GAMEDATA* _instance;
	int gameScore;

};
#endif