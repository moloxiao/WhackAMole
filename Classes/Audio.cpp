#include "Audio.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"

Audio* Audio::m_instance = nullptr;
Audio* Audio::getInstance(){
	if(m_instance == nullptr){
		m_instance = new Audio();
	}
	return m_instance;
}

void Audio::playBGM(char* soundName){
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(soundName,true);
	
	if(GAMEDATA::getInstance()->getMusicState()){
		  CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic(); 
	}else{
	  CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic(); 
	}
}

void Audio::playSound(char* soundName){
	if(GAMEDATA::getInstance()->getSoundState()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName,false);
	}
}

void Audio::prepare(){
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/bg.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/fightbg.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/click.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/normalhit.ogg");

	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.4f);
}