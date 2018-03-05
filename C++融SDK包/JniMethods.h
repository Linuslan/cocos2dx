/*
 * JniMethods.h
 *
 *  Created on: 2013-2-24
 *      Author: wshao
 */

#ifndef JNIMETHODS_H_
#define JNIMETHODS_H_

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "../../cocos2d/cocos/platform/android/jni/JniHelper.h"

class JniMethods {

public:
//	static std::string chargeId;			//计费代码 、计费点
//	static std::string chargeName;		//道具名称
//	static int  price;				//价格 单位分 1￥=100分

public:

	static JniMethods* getInstance();
	static bool getEnableBlurry();
	static int getPayResult();			//返回支付状态码 0：成功 1001：支付失败
	static void requestPayWith1();
	static void requestPayWith2();
	std::function<void(int)> s_callfuncOnReceive;
	static void setSdkParam(int type);
	static void callBackJavaCode(std::string chargeId, std::string chargeName, int price);
	static void onEvent(const char *eventId);
};
#endif

#endif /* JNIMETHODS_H_ */
