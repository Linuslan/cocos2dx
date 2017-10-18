#ifndef _OPEN_LAYER_H_
#define _OPEN_LAYER_H_
#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;
class OpenLayer : public Layer {
public:
	SceneManager * tsm;
	virtual bool init();
	void menuCallBack(Ref * pSender);
	CREATE_FUNC(OpenLayer);
};
#endif
