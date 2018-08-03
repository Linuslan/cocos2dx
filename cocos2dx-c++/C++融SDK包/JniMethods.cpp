/*
 * JniMethods.cpp
 *
 *  Created on: 2013-2-24
 *      Author: wshao
 */

#include "JniMethods.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#ifdef __cplusplus
extern "C" {
#endif
static int s_result = 1001;				//支付默认失败
static JniMethods* jniMethods = NULL;
JniMethods* JniMethods::getInstance()
{
	if(NULL == jniMethods)
	{
		jniMethods = new JniMethods();
        jniMethods->s_callfuncOnReceive = nullptr;
	}
	return jniMethods;
}
//static bool s_enableBlurry = false;
//bool JniMethods::getEnableBlurry()
//{
//	return s_enableBlurry;
//}
//void Java_org_cocos2dx_cpp_JniMethods_nativeSetGameParamsFromOnline(JNIEnv *env, jobject thiz, jstring jstrBlurry) {
//	const char *nativeString = env -> GetStringUTFChars(jstrBlurry, 0);
//	bool enable = (atoi(nativeString) == 1) ? true : false;
//	s_enableBlurry = enable;
//	env -> ReleaseStringUTFChars(jstrBlurry, nativeString);
//}

int JniMethods::getPayResult()
{
	CCLOG("test getPayResult %d",s_result);
	return s_result;
}


void Java_org_cocos2dx_cpp_JniMethods_nativeGetPayResult(JNIEnv *env, jobject thiz, int type) {
    if (jniMethods->s_callfuncOnReceive != nullptr) {
        jniMethods->s_callfuncOnReceive(type);
    }
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

void JniMethods::requestPayWith1() {
	CCLOG("test requestPayWith1");

	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/JniMethods", "requestPayWith1","()V");
	if (isHave) {
		minfo.env -> CallStaticVoidMethod(minfo.classID, minfo.methodID);
		minfo.env -> DeleteLocalRef(minfo.classID);
	}
}

void JniMethods::requestPayWith2() {
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/JniMethods", "requestPayWith2","()V");
	if (isHave) {
		minfo.env -> CallStaticVoidMethod(minfo.classID, minfo.methodID);
		minfo.env -> DeleteLocalRef(minfo.classID);
	}
}

void JniMethods::onEvent(const char *eventId) {

	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/JniMethods", "onEvent","(Ljava/lang/String;)V");
	if (isHave) {
		jstring stringEventId = minfo.env -> NewStringUTF(eventId);
		minfo.env -> CallStaticVoidMethod(minfo.classID, minfo.methodID, stringEventId);
		minfo.env -> DeleteLocalRef(stringEventId);
		minfo.env -> DeleteLocalRef(minfo.classID);
	}
}

void JniMethods::callBackJavaCode(std::string chargeId, std::string chargeName, int price)
{
    CCLOG("cocos cpp jniMethods %s,%s,%d",chargeId.c_str(),chargeName.c_str(),price);
	JniMethodInfo mInfo;
	bool isHave = JniHelper::getStaticMethodInfo(mInfo, "org/cocos2dx/cpp/JniMethods", "setSdkparam", "(Ljava/lang/String;Ljava/lang/String;I)V");
	if (isHave) {
		jstring id = mInfo.env->NewStringUTF(chargeId.c_str());
		jstring name = mInfo.env->NewStringUTF(chargeName.c_str());
		mInfo.env -> CallStaticVoidMethod(mInfo.classID, mInfo.methodID, id, name, price);
		mInfo.env -> DeleteLocalRef(id);
		mInfo.env -> DeleteLocalRef(name);
		mInfo.env -> DeleteLocalRef(mInfo.classID);

	}
}



#endif

#ifdef __cplusplus
}
#endif

#endif
