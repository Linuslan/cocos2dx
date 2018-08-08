#include "ShopLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "UserData.h"
#include "GameConst.h"
#include "JniMethods.h"
#include "DialogLayer.h"

bool ShopLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch*, Event*) -> bool {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->initWithColor(Color4B(0, 0, 0, 100));

	_shopLayer = CSLoader::createNode("csd/ShopLayer.csb");
	auto frameSize = Director::getInstance()->getVisibleSize();
	_shopLayer->setContentSize(frameSize);
	ui::Helper::doLayout(_shopLayer);
	addChild(_shopLayer);

//    auto goldLabel = Label::createWithCharMap("Fnt/write_fnt.png", 25, 29, '0');
//    CCLOG("bestLabel %d", UserData::getInstance()->getBestScore());
//    goldLabel->setString(StringUtils::format("%d", UserData::getInstance()->getGold()));
    goldLabel = Label::createWithBMFont("Fnt/write_fnt.fnt", StringUtils::format("%d", UserData::getInstance()->getGold()));
    this->addChild(goldLabel);
    goldLabel->setPosition(400.0f, 185.0f);

    buyGold();
    

	auto buttonReturn = (ui::Button*)((Sprite*)_shopLayer->getChildByTag(50));
    buttonReturn->getRendererClicked()->setColor(Color3B(150,150,150));
	buttonReturn->addClickEventListener(CC_CALLBACK_1(ShopLayer::menuReturnCallBack, this));

	return true;
}

void ShopLayer::menuReturnCallBack(Ref* pSender)
{
	this->removeFromParentAndCleanup(true);
}
void ShopLayer::buyGold()
{
	auto tag = 41;
	auto shop_bg = (Sprite*)_shopLayer->getChildByTag(40);
	for (int i = 0; i < 5; i++)
	{
		auto btn = (ui::Button*)(shop_bg->getChildByTag(tag++));
        btn->getRendererClicked()->setColor(Color3B(150,150,150));
        btn->getRendererClicked()->setCascadeColorEnabled(true);
        btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::touchBtn, this));
        //todo
        auto goldLabel = Label::createWithBMFont("Fnt/write_fnt.fnt", StringUtils::format("%d", RMB[i]));
		goldLabel->setPosition(100.0f, 33.0f);
        btn->getRendererNormal()->addChild(goldLabel);
        auto goldLabel1 = Label::createWithBMFont("Fnt/write_fnt.fnt", StringUtils::format("%d", RMB[i]));
        goldLabel1->setPosition(100.0f, 33.0f);
        btn->getRendererClicked()->addChild(goldLabel1);
	}
}

void ShopLayer::touchBtn(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
    auto scene = this->getParent();
    auto goldLabelStart = (ui::TextBMFont*)scene->getChildByTag(50)->getChildByTag(87)->getChildByTag(98);
    log("goldLabelStart的地址为：%0x", goldLabelStart);
    goldLabelStart->setString(StringUtils::format("%d", UserData::getInstance()->getGold()));
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        auto btn = (ui::Button*)sender;
        int tag = btn->getTag();
        DialogLayer* dialog = DialogLayer::create();
        double price = 0.0f;
        int gold = 0;
        if(tag == 41) {
            price = 1.0;
            gold = 5;
            dialog->setPrice(price);
        } else if(tag == 42) {
            price = 6.0;
            gold = 15;
            dialog->setPrice(price);
        } else if(tag == 43) {
            gold = 40;
            price = 10.0;
            dialog->setPrice(10.0);
        } else if(tag == 44) {
            gold = 75;
            price = 15.0;
            dialog->setPrice(15.0);
        } else if(tag == 45) {
            gold = 125;
            price = 20.0;
            dialog->setPrice(20.0);
        }
        dialog->setCallback([this, goldLabelStart, gold](int type) {
            log("调用1元特定的callback");
            UserData::getInstance()->setGold(UserData::getInstance()->getGold() + gold);
            log("缓存中增加了5个金币");
            goldLabel->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
            log("goldLabelStart的地址为：%0x", goldLabelStart);
            goldLabelStart->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
            log("更新1元的金币成功");
        });
        this->_shopLayer->addChild(dialog);
        /*
        switch (btn->getTag()) {
            case 41:
                DialogLayer* dialog = DialogLayer::create();
                this->_shopLayer->addChild(dialog);
                JniMethods::getInstance()->setPhone("15959047927");
                CCLOG("设置手机号成功，开始调用支付接口");
                JniMethods::requestPayWith1();
                UserData::getInstance()->setGold(UserData::getInstance()->getGold() + 5);
                goldLabel->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
                goldLabelStart->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
                break;
            case 42:
                UserData::getInstance()->setGold(UserData::getInstance()->getGold() + 30);
                goldLabel->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
                goldLabelStart->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
                break;
            case 43:
                UserData::getInstance()->setGold(UserData::getInstance()->getGold() + 40);
                goldLabel->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
                goldLabelStart->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
                break;
            case 44:
                UserData::getInstance()->setGold(UserData::getInstance()->getGold() + 75);
                goldLabel->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
                goldLabelStart->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
                break;
            case 45:
                UserData::getInstance()->setGold(UserData::getInstance()->getGold() + 125);
                goldLabel->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
                goldLabelStart->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
                break;
            default:
                break;
        }*/
        UserData::getInstance()->saveData();
    }
}
