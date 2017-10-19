#include "ClockLayer.h"
bool ClockLayer::init() {
	Size size = Director::getInstance()->getWinSize();
	MenuItemLabel * item = MenuItemLabel::create(Label::createWithSystemFont("Back", "", 24), CC_CALLBACK_1(ClockLayer::menuCallBack, this));
	item->setPosition(Vec2(size.width*0.9, size.height*0.9));
	Menu * menu = Menu::create(item, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	clock = Sprite::create("background.jpg");
	clock->setPosition(Vec2(size.width/2, size.height/2));
	clock->setScale(0.5);
	this->addChild(clock);
	hour = Sprite::create("shi.png");
	hour->setPosition(Vec2(size.width/2, size.height/2));
	hour->setScale(0.4);
	hour->setAnchorPoint(Vec2(0.5, 0.1));
	this->addChild(hour);
	minute = Sprite::create("fen.png");
	minute->setPosition(Vec2(size.width / 2, size.height / 2));
	minute->setScale(0.3);
	minute->setAnchorPoint(Vec2(0.6, 0.1));
	this->addChild(minute);
	second = Sprite::create("miao.png");
	second->setPosition(Vec2(size.width / 2, size.height / 2));
	second->setScale(0.3);
	second->setAnchorPoint(Vec2(0.55, 0.1));
	this->addChild(second);

	time_t time_sec = time(NULL);
	struct tm * tm;
	tm = localtime(&time_sec);
	CCLOG("Hour=%d, Minute=%d, Second=%d", tm->tm_hour, tm->tm_min, tm->tm_sec);
	secRotation = tm->tm_sec * 6;
	minRotation = tm->tm_min * 6;
	if (tm->tm_hour > 12) {
		hourRotation = (tm->tm_hour - 12) * 5 * 6 + minRotation / 72 * 6;
	} else {
		hourRotation = tm->tm_hour * 5 * 6 + minRotation / 72 * 6;
	}
	hour->setRotation(hourRotation);
	second->setRotation(secRotation);
	minute->setRotation(minRotation);
	schedule(CC_SCHEDULE_SELECTOR(ClockLayer::onSchedule), 1.0);
	return true;
}

void ClockLayer::menuCallBack(Ref * pSender) {
	tsm->goOpenScene();
}

void ClockLayer::onSchedule(float t) {
	second->setRotation(second->getRotation() + 6);
	if ((int)second->getRotation() % 360 == 0) {
		minute->setRotation(minute->getRotation() + 6);
		second->setRotation(0);
		if ((int)minute->getRotation() % 72 == 0) {
			hour->setRotation(hour->getRotation() + 6);
			if ((int)minute->getRotation() % 360 == 0) {
				minute->setRotation(0);
			}
		}
	}
}