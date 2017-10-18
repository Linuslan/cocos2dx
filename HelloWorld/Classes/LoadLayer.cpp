#include "LoadLayer.h"
bool LoadLayer::init() {
	Size size = Director::getInstance()->getVisibleSize();
	Label * label = Label::createWithTTF("Loading...", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(label);
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(LoadLayer::onScheduleOnce), 2.0);
	return true;
}

void LoadLayer::onScheduleOnce(float t) {
	tsm->goOpenScene();
}