//
// Created by LinusLan on 2018/6/25.
//

#ifndef PROJ_ANDROID_STUDIO_ROLESERVICE_H
#define PROJ_ANDROID_STUDIO_ROLESERVICE_H

#include "BaseService.h"
#include "Role.h"
#include "cocos2d.h"
USING_NS_CC;
class RoleService: public BaseService {
public:
    Role* loadRoleById(int id);
    void updateRole(Role* role);
};
#endif //PROJ_ANDROID_STUDIO_ROLESERVICE_H
