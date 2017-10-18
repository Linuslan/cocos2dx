#include "OpenLayer.h"

char* FontToUTF8(const char* font) {
	int len = MultiByteToWideChar(CP_ACP, 0, font, -1, NULL, 0);
	wchar_t *wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, font, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char *str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr)delete[] wstr;
	return str;
}

bool OpenLayer::init() {
	Size size = Director::getInstance()->getWinSize();
	Label * label = Label::createWithSystemFont(FontToUTF8("时钟程序"), "", 48);
	label->setPosition(Vec2(size.width/2, size.height*0.8));
	this->addChild(label);
	MenuItemLabel * startItem = MenuItemLabel::create(Label::createWithSystemFont(FontToUTF8("开始"), "", 38), CC_CALLBACK_1(OpenLayer::menuCallBack, this));
	startItem->setPosition(Vec2(size.width/2, size.height*0.4));
	startItem->setTag(100);
	MenuItemLabel * quitItem = MenuItemLabel::create(Label::createWithSystemFont(FontToUTF8("结束"), "", 38), CC_CALLBACK_1(OpenLayer::menuCallBack, this));
	quitItem->setPosition(Vec2(size.width/2, size.height*0.25));
	quitItem->setTag(101);
	Menu * menu = Menu::create(startItem, quitItem, NULL);
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
	}
}