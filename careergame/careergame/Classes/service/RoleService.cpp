//
// Created by LinusLan on 2018/6/25.
//

#include "RoleService.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace rapidjson;
Role* RoleService::loadRoleById(int id) {
    std::string roleStr = UserDefault::getInstance()->getStringForKey("role-11");
    Document document;
    document.Parse(roleStr.c_str());
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    log("获取到的角色json：%s", buffer.GetString());
    Role* role = new Role();
    role->setName(document["name"].GetString());
    role->setExp(document["exp"].GetFloat());
    role->setHp(document["hp"].GetFloat());
    role->setMp(document["mp"].GetFloat());
    role->setLevel(document["level"].GetInt());
    role->setType(document["type"].GetInt());
    role->setPower(document["power"].GetFloat());
    return role;
}

void RoleService::updateRole(Role* role) {
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember(rapidjson::Value("name", allocator), rapidjson::Value(role->getName().c_str(), allocator), allocator);
    document.AddMember(rapidjson::Value("exp", allocator), rapidjson::Value(role->getExp()), allocator);
    document.AddMember(rapidjson::Value("hp", allocator), rapidjson::Value(role->getHp()), allocator);
    document.AddMember(rapidjson::Value("mp", allocator), rapidjson::Value(role->getMp()), allocator);
    document.AddMember(rapidjson::Value("level", allocator), rapidjson::Value(role->getLevel()), allocator);
    document.AddMember(rapidjson::Value("type", allocator), rapidjson::Value(role->getType()), allocator);
    document.AddMember(rapidjson::Value("power", allocator), rapidjson::Value(role->getPower()), allocator);
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    log("角色生成的json：%s", buffer.GetString());
    UserDefault::getInstance()->setStringForKey("role-11", buffer.GetString());
}