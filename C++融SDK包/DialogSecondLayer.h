//
//  DialogSecondLayer.h
//  Snail
//
//  Created by yzq on 2017/12/8.
//

#ifndef DialogSecondLayer_h
#define DialogSecondLayer_h

#include <cocos2d.h>
#include "ui/CocosGUI.h"

USING_NS_CC;

class DialogSecondLayer : public Layer
{
public:
    ui::Text* dialogText;
    std::string str;
    bool buySecond = false;                                                         //第二次点击购买
    bool buyThird = false;                                                         //第三次点击购买
    std::string chargeId;			//计费代码 、计费点
	std::string chargeName;		//道具名称
	int  price;				//价格 单位分 1￥=100分
	int resultType;				//支付状态码
public:
    virtual bool init();
    void effectClick();                                                       //响应二次点击效果
    void text1(int type);                                                     //选定txet内容
    void text2(int type);                                                     //选定txet内容
    void cancelCallBack(Ref *selector, ui::Widget::TouchEventType type);            //取消
    void sureCallBack(Ref *selector, ui::Widget::TouchEventType type);              //确定
    void setSdkParam(int type);
    CREATE_FUNC(DialogSecondLayer);
};

#endif /* DialogSecondLayer_h */
