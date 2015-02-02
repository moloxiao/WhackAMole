#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

class GAMEDATA{
public:
	static GAMEDATA* getInstance();
	void setGameScore(int score);
	int getGameScore();
	
	void setMouseNum(int mouse_num);
	int getMouseNum();

	bool isPaySuccess();
	void setPaySuccess(bool paySuccess);

	int getTotalMouseNum();
	void setTotalMouseNum(int totalMouseNum);

	int getPowerValue();
	void setPowerValue(int powerValue);

	int getNightFightTimes();
	void setNightFightTimes(int nightFightTimes);

	int getPlayRounds();
	void setPlayRounds(int playRounds);

	bool isFirstLogin();
	void setFirstLogin(bool first_login);

	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();
private:
	GAMEDATA();
	void init();
	static GAMEDATA* _instance;
	int gameScore;
	int mouseNum;
	bool firstLognin;

};
#endif
