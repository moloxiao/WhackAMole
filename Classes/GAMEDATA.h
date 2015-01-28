#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

class GAMEDATA{
public:
	static GAMEDATA* getInstance();
	void setGameScore(int score);
	int getGameScore();
	
	bool isPaySuccess();
	void setPaySuccess(bool paySuccess);

	int getTotalScore();
	void setTotalScore(int totalScore);

	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();
private:
	GAMEDATA();
	void init();
	static GAMEDATA* _instance;
	int gameScore;

};
#endif
