#ifndef SHOP_LAYER_H_
#define SHOP_LAYER_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class ShopLayer : public LayerColor
{
    Label *goldLabel;
public:
	CREATE_FUNC(ShopLayer);
	virtual bool init();
	void menuReturnCallBack(Ref* pSender);
	void buyGold();
    
    void touchBtn(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
//    void touchBtn1(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
//    void touchBtn2(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
//    void touchBtn3(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
//    void touchBtn4(Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	Node* _shopLayer;

};




#endif
