//
//  DialogSecondLayer.cpp
//  Snail
//
//  Created by yzq on 2017/12/8.
//

#include "DialogSecondLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "AppFunc.h"
#include "GameScene.h"
#include "TaskMgr.h"
#include "MenuLayer.h"
#include "PropMgr.h"
#include "UserDefaultUtil.h"
#include "UpdateLayer.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "JniMethods.h"
#endif


USING_NS_CC;

//auto binstance = DataMgr::getInstance();

bool DialogSecondLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch*, Event*) ->bool{
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto winSize = Director::getInstance()->getWinSize();
    auto dialog = CSLoader::createNode("csd/Layer.csb");
    addChild(dialog,100);
    
    auto imageBg = (ui::ImageView*)dialog->getChildByTag(2);
    
    dialogText = (ui::Text*)imageBg->getChildByTag(6);
    text1(TaskMgr::Instance().numType);
    dialogText->setString(str);
    
    auto backBtn = (ui::Button*)imageBg->getChildByTag(4);
    backBtn->addTouchEventListener(CC_CALLBACK_2(DialogSecondLayer::cancelCallBack, this));
    
    auto sureBtn = (ui::Button*)imageBg->getChildByTag(5);
    sureBtn->addTouchEventListener(CC_CALLBACK_2(DialogSecondLayer::sureCallBack, this));
    
    return true;
}

void DialogSecondLayer::text1(int type)
{
    setSdkParam(type);
    switch (type)
    {
        case 0:
            str = "幸运之子，获取幸运道具，资费4元/次，(不含通信费)，确认购买？";
            break;
        case 1:
            str = "开局飞行，开局飞行400米，资费5元/次，(不含通信费)，确认购买？";
            break;
        case 2:
            str = "超级护盾，拥有坚实防御一次，资费2元/次，(不含通信费)，确认购买?";
            break;
        case 3:
            str = "800金币，获取800金币，资8元/次，(不含通信费)，确认购买?";
            break;
        case 4:
            str = "超值礼包，获得超值礼包，资费10元/次，(不含通信费)，确认购买?";
            break;
        case 5:
            str = "回复精力，回复精力，资费12元/次，(不含通信费)，确认购买?";
            break;
        case 6:
            str = "一键满级，一键快速满级，资费15元/次，(不含通信费)，确认购买?";
            break;
        case 7:
            str = "复活礼包，复活一次，资费1元/次，(不含通信费)，确认购买?";
            break;
        default:
            break;
    }
//    return str;
}
void DialogSecondLayer::text2(int type)
{
    //    std::string str = "";
    switch (type)
    {
        case 0:
            str = "您将购买“经典天天酷跑“的4元“幸运之子”产品，本次费用4元/次，(不含通信费)，将由本机话费中扣除。您还未购买，点击取消不订购，是否购买？";
            break;
        case 1:
            str = "您将购买“经典天天酷跑“的5元“开局飞行”产品，本次费用5元/次，(不含通信费)，将由本机话费中扣除。您还未购买，点击取消不订购，是否购买？";
            break;
        case 2:
            str = "您将购买“经典天天酷跑“的2元“超级护盾”产品，本次费用2元/次，(不含通信费)，将由本机话费中扣除。您还未购买，点击取消不订购，是否购买？";
            break;
        case 3:
            str = "您将购买“经典天天酷跑“的8元“800金币”产品，本次费用8元/次，(不含通信费)，将由本机话费中扣除。您还未购买，点击取消不订购，是否购买？";
            break;
        case 4:
            str = "您将购买“经典天天酷跑“的10元“超值礼包”产品，本次费用10元/次，(不含通信费)，将由本机话费中扣除。您还未购买，点击取消不订购，是否购买？";
            break;
        case 5:
            str = "您将购买“经典天天酷跑“的12元“回复精力”产品，本次费用12元/次，(不含通信费)，将由本机话费中扣除。您还未购买，点击取消不订购，是否购买？";
            break;
        case 6:
            str = "您将购买“经典天天酷跑“的15元“一键满级”产品，本次费用15元/次，(不含通信费)，将由本机话费中扣除。您还未购买，点击取消不订购，是否购买？";
            break;
        case 7:
            str = "您将购买“经典天天酷跑“的1元“复活礼包”产品，本次费用1元/次，(不含通信费)，将由本机话费中扣除。您还未购买，点击取消不订购，是否购买？";
            break;
        default:
            break;
    }
    //    return str;
}

void DialogSecondLayer::cancelCallBack(Ref *selector, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        
        if(TaskMgr::Instance().numType == 4 || TaskMgr::Instance().numType == 3 || TaskMgr::Instance().numType == 5 || TaskMgr::Instance().numType == 6)
        {
            auto menuLayer = static_cast<MenuLayer*>(this->getParent());
            menuLayer->setWhiteColorBg();
        }
        if(TaskMgr::Instance().numType == 7)
        {
            GEventDispatch->dispatchCustomEvent("CancelResurgence");
        }
        else
        {
            this->removeFromParentAndCleanup(true);
        }
        
    }
}

void DialogSecondLayer::sureCallBack(Ref *selector, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        //todo 计费点
        //第二次提示购买
        text2(TaskMgr::Instance().numType);
        dialogText->setString(str);

        effectClick();
        
    }
}

void DialogSecondLayer::effectClick()
{
    if(buySecond && (TaskMgr::Instance().numType == 0 || TaskMgr::Instance().numType == 1|| TaskMgr::Instance().numType == 2 || TaskMgr::Instance().numType == 3 || TaskMgr::Instance().numType == 4 || TaskMgr::Instance().numType == 5 || TaskMgr::Instance().numType == 6 || TaskMgr::Instance().numType == 7))
    {
        
        if(TaskMgr::Instance().numType == 0)
        {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            //设置sdk参数
            JniMethods::getInstance()->callBackJavaCode(chargeId, chargeName, price);
            //扣钱
            JniMethods::getInstance()->requestPayWith1();
//            resultType = JniMethods::getPayResult();
            JniMethods::getInstance()->s_callfuncOnReceive = [this](int resultCode){
                CCLOG("resultCode: %d", resultCode);
                //支付成功
                if(resultCode == 0)
                {
                    auto menuLayer = static_cast<MenuLayer*>(this->getParent());
                    menuLayer->randNum();
                    //扣钱
                }
                this->removeFromParentAndCleanup(true);
            };
#endif
        }
        if(TaskMgr::Instance().numType == 1) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            //设置sdk参数
            JniMethods::callBackJavaCode(chargeId, chargeName, price);
            //扣钱
            JniMethods::requestPayWith1();
//            resultType = JniMethods::getPayResult();
            JniMethods::getInstance()->s_callfuncOnReceive = [this](int resultCode) {
                CCLOG("resultCode: %d", resultCode);
                //支付成功
                if (resultCode == 0) {
                    //更新飞行道具数额
                    PropMgr::Instance().AddPropNumber(PROP_SPRINT, 1);
                    EventCustom eventCustom1("fly_custom_event_update");
                    _eventDispatcher->dispatchEvent(&eventCustom1);
                    this->removeFromParentAndCleanup(true);
                }
            };
#endif
        }
        if(TaskMgr::Instance().numType == 2) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            //设置sdk参数
            JniMethods::callBackJavaCode(chargeId, chargeName, price);
            //扣钱
            JniMethods::requestPayWith1();
//            resultType = JniMethods::getPayResult();
            JniMethods::getInstance()->s_callfuncOnReceive = [this](int resultCode) {
                CCLOG("resultCode: %d", resultCode);
                //支付成功
                if (resultCode == 0) {
                    //更新光能护盾道具
                    PropMgr::Instance().AddPropNumber(PROP_PROTECT, 1);
                    EventCustom eventCustom1("shield_custom_event_update");
                    _eventDispatcher->dispatchEvent(&eventCustom1);
                    this->removeFromParentAndCleanup(true);
                }
            };
#endif
        }
        if(TaskMgr::Instance().numType == 3)
        {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            //设置sdk参数
            JniMethods::callBackJavaCode(chargeId, chargeName, price);
            //扣钱
            JniMethods::requestPayWith1();
//            resultType = JniMethods::getPayResult();
            JniMethods::getInstance()->s_callfuncOnReceive = [this](int resultCode) {
                CCLOG("resultCode: %d", resultCode);
                //支付成功
                if (resultCode == 0) {
                    auto menuLayer = static_cast<MenuLayer *>(this->getParent());
                    menuLayer->setWhiteColorBg();
                    UserDefaultUtil::setGoldNumber(UserDefaultUtil::getGoldNumber() + 800);
                    EventCustom eventCustom2("gold_custom_event_update");
                    GEventDispatch->dispatchEvent(&eventCustom2);
                    this->removeFromParentAndCleanup(true);
                }
            };
#endif
        }
        if(TaskMgr::Instance().numType == 4)
        {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            //设置sdk参数
            JniMethods::callBackJavaCode(chargeId, chargeName, price);
            //扣钱
            JniMethods::requestPayWith1();
//            resultType = JniMethods::getPayResult();
            JniMethods::getInstance()->s_callfuncOnReceive = [this](int resultCode) {
                CCLOG("resultCode: %d", resultCode);
                //支付成功
                if (resultCode == 0) {
                    auto menuLayer = static_cast<MenuLayer *>(this->getParent());
                    menuLayer->setWhiteColorBg();
                    UserDefaultUtil::setGoldNumber(UserDefaultUtil::getGoldNumber() + 2000);
                    UserDefaultUtil::setDiamondNumber(UserDefaultUtil::getDiamondNumber() + 120);
                    PropMgr::Instance().AddPropNumber(PROP_LAND, 1);
                    PropMgr::Instance().AddPropNumber(PROP_ULTIMATE_SPRINT, 1);
                    PropMgr::Instance().AddPropNumber(PROP_SPRINT, 1);

                    //更新金币数额
                    EventCustom eventCustom("gold_custom_event_update");
                    GEventDispatch->dispatchEvent(&eventCustom);

                    //更新钻石数额
                    //            EventCustom eventCustom1("diamond_custom_event_update");
                    //            GEventDispatch->dispatchEvent(&eventCustom1);

                    //更新飞行道具数量
                    EventCustom eventCustom2("fly_custom_event_update");
                    GEventDispatch->dispatchEvent(&eventCustom2);

                    //更新护盾道具数量
                    EventCustom eventCustom3("shield_custom_event_update");
                    GEventDispatch->dispatchEvent(&eventCustom3);

                    //更新安全降落数量
                    //            EventCustom eventCustom4("land_custom_event_update");
                    //            GEventDispatch->dispatchEvent(&eventCustom4);

                    //更新终极冲刺道具数量
                    EventCustom eventCustom5("sprint_custom_event_update");
                    GEventDispatch->dispatchEvent(&eventCustom5);
                    this->removeFromParentAndCleanup(true);
                    menuLayer->setWhiteColorBg();
                }
            };
#endif
        }
        if(TaskMgr::Instance().numType == 5)
        {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            //设置sdk参数
            JniMethods::callBackJavaCode(chargeId, chargeName, price);
            //扣钱
            JniMethods::requestPayWith1();
//            resultType = JniMethods::getPayResult();
            JniMethods::getInstance()->s_callfuncOnReceive = [this](int resultCode) {
                CCLOG("resultCode: %d", resultCode);
                //支付成功
                if (resultCode == 0) {
                    auto menuLayer = static_cast<MenuLayer *>(this->getParent());
                    menuLayer->setWhiteColorBg();
                    UserDefaultUtil::setHoneyNumber(UserDefaultUtil::getHoneyNumber() + 1);
                    EventCustom eventCustom2("honey_custom_event_update");
                    GEventDispatch->dispatchEvent(&eventCustom2);
                    this->removeFromParentAndCleanup(true);
                }
            };
#endif
        }
        if(TaskMgr::Instance().numType == 6)
        {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            //设置sdk参数
            JniMethods::callBackJavaCode(chargeId, chargeName, price);
            //扣钱
            JniMethods::requestPayWith1();
//            resultType = JniMethods::getPayResult();
            JniMethods::getInstance()->s_callfuncOnReceive = [this](int resultCode) {
                CCLOG("resultCode: %d", resultCode);
                //支付成功
                if (resultCode == 0) {
                    auto menuLayer = static_cast<MenuLayer *>(this->getParent());
                    menuLayer->updateHero();
                    this->removeFromParentAndCleanup(true);
                }
            };
#endif
        }
        if(TaskMgr::Instance().numType == 7)
        {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            //设置sdk参数
            JniMethods::callBackJavaCode(chargeId, chargeName, price);
            //扣钱
            JniMethods::requestPayWith1();
//            resultType = JniMethods::getPayResult();
            JniMethods::getInstance()->s_callfuncOnReceive = [this](int resultCode) {
                CCLOG("resultCode: %d", resultCode);
                //支付成功
                if (resultCode == 0) {
                    GEventDispatch->dispatchCustomEvent("SureResurgence");
                }
            };
#endif
        }
        
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        JniMethods::requestPayWith2();
//#endif
        return;
    }
    buySecond = true;
    //        buyThird = true;
}

void DialogSecondLayer::setSdkParam(int type)
{
    switch (type)
    {
        case 0:
            chargeName = "幸运之子";
            chargeId = "94A341D0305C4140A0B2890108F7CC8B";
            price = 4;
            break;
        case 1:
            chargeName = "开局飞行";
            chargeId = "19FD569FED6E4EA9B65E38214183CAE9";
            price = 5;
            break;
        case 2:
            chargeName = "超级护盾";
            chargeId = "E6B36313A3274E78AEBFE2CE8724E15A";
            price = 2;
            break;
        case 3:
            chargeName = "800金币";
            chargeId = "FB29C56635794668A5479BF3D268FFE5";
            price = 8;
            break;
        case 4:
            chargeName = "超值礼包";
            chargeId = "72FFBAD7D88A4577A9FF99EBBC373AE4";
            price = 10;
            break;
        case 5:
            chargeName = "回复精力";
            chargeId = "8CA2A1DD6B17498AAC044CF6028AE84F";
            price = 12;
            break;
        case 6:
            chargeName = "一键满级";
            chargeId = "081659002CA24BD8ACB1A31AFC47BAD4";
            price = 15;
            break;
        case 7:
            chargeName = "复活";
            chargeId = "6B0ADFC6D9D844B4B7F1008DEAC34580";
            price = 1;
            break;
        default:
            break;
            CCLOG("cocos cpp DialogSecondLayer %s,%s,%d,%d",chargeId.c_str(),chargeName.c_str(),price,type);
    }
}
