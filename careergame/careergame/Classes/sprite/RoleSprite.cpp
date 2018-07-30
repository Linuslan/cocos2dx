//
// Created by LinusLan on 2018/6/13.
//

#include "RoleLevelConfig.h"
#include "RoleSprite.h"
bool RoleSprite::init() {
    log("进入角色初始化方法");
    if(!Sprite::init()) {
        return false;
    }
    try {
        log("开始初始化角色");
        this->roleService = new RoleService();
        this->role = this->roleService->loadRoleById(1);
        SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
        sfc->addSpriteFramesWithFile("images/role/walk/role.plist", "images/role/walk/role.png");
        this->standFront();
        this->setName("role-11");
    } catch(std::exception& ex) {
        log("初始化角色异常，%s", ex.what());
    }
    return true;
}

void RoleSprite::standFront() {
    RoleSprite::unscheduleAllCallbacks();
    this->stopAllActions();
    Vector<SpriteFrame*> frames;
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    SpriteFrame* frame = sfc->getSpriteFrameByName("stand-front.png");
    this->setSpriteFrame(frame);
    RoleSprite::schedule(schedule_selector(RoleSprite::standUpdate), 60.0, kRepeatForever, 0.5);
}

void RoleSprite::standBack() {
    RoleSprite::unscheduleAllCallbacks();
    this->stopAllActions();
    Vector<SpriteFrame*> frames;
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    SpriteFrame* frame = sfc->getSpriteFrameByName("stand-back.png");
    this->setSpriteFrame(frame);
    RoleSprite::schedule(schedule_selector(RoleSprite::standUpdate), 60.0, kRepeatForever, 0.5);
}

void RoleSprite::standSide() {
    RoleSprite::unscheduleAllCallbacks();
    //log("开始侧面站立");
    //this->stopAllActionsByTag(2);
    this->stopAllActions();
    Vector<SpriteFrame*> frames;
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    SpriteFrame* frame = sfc->getSpriteFrameByName("stand-side.png");
    this->setSpriteFrame(frame);
    RoleSprite::schedule(schedule_selector(RoleSprite::standUpdate), 60.0, kRepeatForever, 0.5);
}

void RoleSprite::walk() {
    RoleSprite::unscheduleAllCallbacks();
    startDo = false;
    this->stopAllActions();
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    /*Vec2 targetPos = this->targetObj->getPosition();
    float x = targetPos.x;
    float y = targetPos.y;
    Vec2 rolePos = this->getPosition();
    if(x < rolePos.x) {
        this->setFlippedX(false);
    } else {
        this->setFlippedX(true);
    }*/
    Vector<SpriteFrame*> frames;
    for(int i = 1; i < 9; i ++) {
        frames.pushBack(sfc->getSpriteFrameByName(StringUtils::format("%d.png", i)));
    }
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.10f);
    Animate* animate = Animate::create(animation);
    RepeatForever* action = RepeatForever::create(animate);
    action->setTag(2);
    this->runAction(action);
    //scheduleUpdate();
    RoleSprite::schedule(schedule_selector(RoleSprite::walkUpdate), 60.0, kRepeatForever, 0.5);
}

void RoleSprite::walkUp() {
    RoleSprite::unscheduleAllCallbacks();
    this->stopAllActions();
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> frames;
    for(int i = 1; i < 9; i ++) {
        frames.pushBack(sfc->getSpriteFrameByName(StringUtils::format("%d.png", i)));
    }
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.10f);
    Animate* animate = Animate::create(animation);
    RepeatForever* action = RepeatForever::create(animate);
    action->setTag(3);
    this->runAction(action);
    RoleSprite::schedule(schedule_selector(RoleSprite::walkUpdate), 60.0, kRepeatForever, 0.5);
}

void RoleSprite::walkDown() {
    RoleSprite::unscheduleAllCallbacks();
    this->stopAllActions();
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> frames;
    for(int i = 1; i < 9; i ++) {
        frames.pushBack(sfc->getSpriteFrameByName(StringUtils::format("%d.png", i)));
    }
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.10f);
    Animate* animate = Animate::create(animation);
    RepeatForever* action = RepeatForever::create(animate);
    action->setTag(4);
    this->runAction(action);
    RoleSprite::schedule(schedule_selector(RoleSprite::walkUpdate), 60.0, kRepeatForever, 0.5);
}

void RoleSprite::update(float t) {
    try {
        float step = 0.5;
        float x = this->getPosition().x + step;
        float y = this->getPosition().y + step;
        /*if(targetObj == nullptr || nullptr == targetBtn) {
            return;
        }*/
        if(startDo) {
            return ;
        }
        Vec2 targetPos = targetObj->getPosition();
        if(targetPos.x < this->getPosition().x) {
            x = this->getPosition().x - step;
        }
        if(targetPos.y < this->getPosition().y) {
            y = this->getPosition().y - step;
        }
        if(this->getBoundingBox().intersectsRect(targetObj->getBoundingBox())) {
            startDo = true;
            this->standSide();
            if(this->callback) {
                this->callback();
            }
            this->targetBtn->callback();
            targetObj = nullptr;
            targetBtn = nullptr;
            return;
        }
        //遍历所有的物体，判断角色是否和某个物体相交，如果相交，则不再沿某个方向走动
        Vector<Node*> nodes = this->getParent()->getChildren();
        for(Vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter ++) {
            //如果是目标物体，则不判断
            if((*iter) == targetObj) {
                continue;
            }
            //如果角色和不是目标物体的物体相交，则不再沿原来方向走，沿另外一个方向走
            if(this->getBoundingBox().intersectsRect((*iter)->getBoundingBox())) {
                turnY = !turnY;
                break;
            }
        }
        if(!turnY) {
            this->setPosition(x, this->getPosition().y);
        } else {
            this->setPosition(this->getPosition().x, y);
        }
    } catch(const char* msg) {
        log("异常:%s", msg);
    } catch(std::exception& ex) {
        log("获取参数异常：%s", ex.what());
    }
}

void RoleSprite::sleep() {
    RoleSprite::unscheduleAllCallbacks();
    RoleSprite::schedule(schedule_selector(RoleSprite::sleepUpdate), 60.0, kRepeatForever, 0.5);
}

void RoleSprite::sleepUpdate(float a) {
    this->role = this->roleService->loadRoleById(1);
    float mpIncrease = 5/100;   //睡觉状态每分钟恢复5%的mp
    float powerReduce = 0.1/100;   //睡觉状态每分钟消耗0.1%的能量
    //获取角色当前的mp和power
    float mp = this->role->getMp();
    float hp = this->role->getHp();
    float power = this->role->getPower();
    mp = mp + mp*mpIncrease;
    float maxMp = RoleLevelConfig::getIntByName(StringUtils::format("%d", role->getLevel()), "mp");
    if(mp > maxMp) {
        mp = maxMp;
    }
    this->role->setMp(mp);
    power = power - power*powerReduce;
    if(power < 0) {
        power = 0;
    }
    this->role->setPower(power);
    this->role->setMp(mp);
    this->roleService->updateRole(role);
}

void RoleSprite::walkUpdate(float a) {
    this->role = this->roleService->loadRoleById(1);
    float mpReduce = 1/100; //角色走路时每分钟消耗的精力
    float powerReduce = 1/100;    //角色走路时每分钟消耗的体力
    //获取角色当前的mp和power
    float mp = this->role->getMp();
    float power = this->role->getPower();
    mp = mp - mp*mpReduce;
    power = power - power*powerReduce;
    if(mp < 0) {
        mp = 0;
    }
    if(power < 0) {
        power = 0;
    }
    this->role->setPower(power);
    this->role->setMp(mp);
    this->roleService->updateRole(role);
}

void RoleSprite::standUpdate(float a) {
    this->role = this->roleService->loadRoleById(1);
    float mpReduce = 0.5/100;
    float powerReduce = 0.5/100;
    float mp = this->role->getMp();
    float power = this->role->getPower();
    mp = mp - mp*mpReduce;
    power = power - power*powerReduce;
    if(mp < 0) {
        mp = 0;
    }
    if(power < 0) {
        power = 0;
    }
    this->role->setPower(power);
    this->role->setMp(mp);
    this->roleService->updateRole(role);
}