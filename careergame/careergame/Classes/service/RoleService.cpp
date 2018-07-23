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
    role->setExp(document["exp"].GetInt());
    role->setHp(document["hp"].GetInt());
    role->setMp(document["mp"].GetInt());
    role->setLevel(document["level"].GetInt());
    role->setType(document["type"].GetInt());
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
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    log("角色生成的json：%s", buffer.GetString());
    UserDefault::getInstance()->setStringForKey("role", buffer.GetString());
}