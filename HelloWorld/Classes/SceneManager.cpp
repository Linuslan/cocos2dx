#include "SceneManager.h"
#include "LoadLayer.h"
#include "OpenLayer.h"
#include "ClockLayer.h"
void SceneManager::createLoadScene() {
	loadScene = Scene::create();
	LoadLayer * layer = LoadLayer::create();
	loadScene->addChild(layer);
	layer->tsm = this;
}

void SceneManager::goOpenScene() {
	openScene = Scene::create();
	OpenLayer * layer = OpenLayer::create();
	openScene->addChild(layer);
	layer->tsm = this;
	Director::getInstance()->replaceScene(openScene);
}

void SceneManager::goClockScene() {
	clockScene = Scene::create();
	ClockLayer * layer = ClockLayer::create();
	clockScene->addChild(layer);
	layer->tsm = this;
	Director::getInstance()->replaceScene(clockScene);
}