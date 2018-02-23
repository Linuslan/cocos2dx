#include "OpenLayer.h"

bool OpenLayer::init() {
	Size size = Director::getInstance()->getWinSize();
    Label * label = Label::createWithSystemFont("Clock", "", 48);
    label->setPosition(Vec2(size.width/2, size.height*0.8));
	this->addChild(label);
	MenuItemLabel * startItem = MenuItemLabel::create(Label::createWithSystemFont("Start", "", 38), CC_CALLBACK_1(OpenLayer::menuCallBack, this));
	startItem->setPosition(Vec2(size.width/2, size.height*0.4));
	startItem->setTag(100);

	MenuItemLabel * quitItem = MenuItemLabel::create(Label::createWithSystemFont("Quit", "", 38), CC_CALLBACK_1(OpenLayer::menuCallBack, this));
	quitItem->setPosition(Vec2(size.width/2, size.height*0.25));
	quitItem->setTag(101);
	MenuItemLabel * tileMapItem = MenuItemLabel::create(Label::createWithSystemFont("TiledMap", "", 38), CC_CALLBACK_1(OpenLayer::menuCallBack, this));
	tileMapItem->setPosition(Vec2(size.width/2, size.height*0.15));
	tileMapItem->setTag(102);
	Menu * menu = Menu::create(startItem, quitItem, tileMapItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	return true;
}

void OpenLayer::menuCallBack(Ref * pSender) {
	switch(((MenuItemLabel *)pSender)->getTag()) {
        case 100: {
            tsm->goClockScene();
            break;
        }
        case 101: {
            Director::getInstance()->end();
            exit(0);
            break;
        }
        case 102: {
            tsm->goTileMapScene();
            break;
        }
	}
}