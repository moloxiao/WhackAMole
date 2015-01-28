#include "PayHandler.h"
#include "GAMEDATA.h"

static PayHandler* _instance = nullptr;
PayHandler* PayHandler::getInstance()
{
	if (!_instance)
	{
		_instance = new PayHandler();
	}
	return _instance;
}

void PayHandler::payCallback(int requestId,int resultId){
	if(resultId == 0){
		GAMEDATA::getInstance()->setPaySuccess(true);
	}

	switch (requestId)
	{
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	default:
		break;
	}
}

