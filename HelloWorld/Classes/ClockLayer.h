#ifndef _CLOCK_LAYER_H_
#define _CLOCK_LAYER_H_
#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;
class ClockLayer : public Layer {
public:
	Sprite * clock;
	Sprite * hour;
	Sprite * minute;
	Sprite * second;
	SceneManager * tsm;
	int hourRotation;
	int minRotation;
	int secRotation;
	virtual bool init();
	CREATE_FUNC(ClockLayer);
	void menuCallBack(Ref * pSender);
	void onSchedule(float t);
};
#endif
