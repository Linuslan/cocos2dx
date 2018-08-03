//
// Created by LinusLan on 2018/5/21.
//

#ifndef PROJ_ANDROID_STUDIO_ROLELAYER_H
#define PROJ_ANDROID_STUDIO_ROLELAYER_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "HomeScene.h"
#include <cocos2d/cocos/ui/UIText.h>
#include <cocos2d/cocos/ui/UIListView.h>
#include <cocos2d/cocos/ui/UIImageView.h>
#include "pthread.h"
USING_NS_CC;
class RoleLoginLayer: public Layer {
private:
    pthread_t thread;
public:
    virtual bool init();
    CREATE_FUNC(RoleLoginLayer);
    int threadStart();
    static void* thread_function(void* arg);    //被启动的线程函数，注意必须是静态方法
};
#endif //PROJ_ANDROID_STUDIO_ROLELAYER_H
