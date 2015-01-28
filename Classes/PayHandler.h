#ifndef _PAY_HANDLER_H_
#define _PAY_HANDLER_H_
#include "cocos2d.h"

class PayHandler
{       
public:
	PayHandler() {};
	~PayHandler() {};
	void payCallback(int requestId,int resultId);
	static PayHandler* getInstance();
};
#endif

