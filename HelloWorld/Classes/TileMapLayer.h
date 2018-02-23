//
// Created by LinusLan on 2018/2/23.
//

#ifndef PROJ_ANDROID_STUDIO_TILEMAPLAYER_H
#define PROJ_ANDROID_STUDIO_TILEMAPLAYER_H

#endif //PROJ_ANDROID_STUDIO_TILEMAPLAYER_H

#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;
class TileMapLayer : public Layer {
private:
    std::map<int, Vec2> pMap;
public:
    SceneManager* tsm;
    virtual bool init();
    CREATE_FUNC(TileMapLayer);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
};