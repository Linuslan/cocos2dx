#include "ClockLayer.h"
bool ClockLayer::init() {
	Size size = Director::getInstance()->getWinSize();
	MenuItemLabel * item = MenuItemLabel::create(Label::createWithSystemFont("Quit", "", 24), CC_CALLBACK_1(ClockLayer::menuCallBack, this));
	item->setPosition(Vec2(size.width*0.9, size.height*0.9));
	Menu * menu = Menu::create(item, NULL);
	menu->setPosition(Point::ZERO);
	menu->addChild(item);
	this->addChild(menu);
	clock = Sprite::create("resource/clock.png");
	clock->setPosition(Vec2(size.width/2, size.height/2));
	this->addChild(clock);
	hour = Sprite::create("resource/hour.png");
	hour->setPosition(Vec2(size.width/2, size.height/2));
	this->addChild(hour);
	minute = Sprite::create("resource/minute.png");
	minute->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(minute);
	second = Sprite::create("resource/second.png");
	second->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(second);
	return true;
}

void ClockLayer::menuCallBack(Ref * pSender) {

}