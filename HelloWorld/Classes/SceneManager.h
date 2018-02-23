#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_
#include "cocos2d.h"
USING_NS_CC;
class SceneManager {
public:
	Scene* loadScene;
	Scene* openScene;
	Scene* clockScene;
	Scene* tileMapScene;
	void createLoadScene();
	void goOpenScene();
	void goClockScene();
	void goTileMapScene();
};
#endif
