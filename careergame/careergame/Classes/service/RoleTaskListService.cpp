//
// Created by LinusLan on 2018/7/26.
//

#include "RoleTaskListService.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
#include "RoleTaskListConfig.h"
#include "IdConfig.h"
#include <cocos2d/external/json/stringbuffer.h>
#include <cocos2d/external/json/writer.h>
USING_NS_CC;
using namespace rapidjson;
RoleTask* RoleTaskListService::createRoleTask(Task *task) {
    RoleTask* roleTask = new RoleTask();
    int id = IdConfig::getIdByKey("roleTaskId");
    roleTask->setId(id);
    roleTask->setMp(task->getMp());
    roleTask->setPower(task->getPower());
    roleTask->setName(task->getName());
    roleTask->setTime(task->getTime());
    roleTask->setMoney(task->getMoney());
    roleTask->setExp(task->getExp());
    roleTask->setStatus(0);
    roleTask->setLevel(task->getLevel());
    roleTask->setTaskId(task->getId());
    roleTask->setDifficultyLevel(task->getDifficultyLevel());
    return roleTask;
}
void RoleTaskListService::addTask(RoleTask *task) {
    std::string taskList = RoleTaskListConfig::getData();
    Document doc;
    doc.Parse(taskList.c_str());
    rapidjson::Value newTask(kObjectType);
    newTask.SetObject();
    newTask.AddMember(rapidjson::Value("id", doc.GetAllocator()), rapidjson::Value(task->getId()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("name", doc.GetAllocator()), rapidjson::Value(task->getName(), doc.GetAllocator()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("money", doc.GetAllocator()), rapidjson::Value(task->getMoney()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("exp", doc.GetAllocator()), rapidjson::Value(task->getExp()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("time", doc.GetAllocator()), rapidjson::Value(task->getTime()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("power", doc.GetAllocator()), rapidjson::Value(task->getPower()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("mp", doc.GetAllocator()), rapidjson::Value(task->getMp()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("level", doc.GetAllocator()), rapidjson::Value(task->getLevel()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("status", doc.GetAllocator()), rapidjson::Value(task->getStatus()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("taskId", doc.GetAllocator()), rapidjson::Value(task->getId()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("difficultyLevel", doc.GetAllocator()), rapidjson::Value(task->getDifficultyLevel()), doc.GetAllocator());
    std::string level = StringUtils::format("%d", task->getLevel());
    if(doc[level.c_str()].IsNull()) {
        rapidjson::Value levelList(kArrayType);
        doc.AddMember(rapidjson::Value(level.c_str(), doc.GetAllocator()), levelList, doc.GetAllocator());
    }
    doc[level.c_str()].PushBack(newTask, doc.GetAllocator());
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);
    log("角色任务更新后的json：%s", buffer.GetString());
    RoleTaskListConfig::updateTaskList(buffer.GetString());
}

std::vector<RoleTask*>* RoleTaskListService::getTaskList() {
    std::vector<RoleTask*>* vector = new std::vector<RoleTask*> ();
    std::string taskList = RoleTaskListConfig::getData();
    Document doc;
    doc.Parse(taskList.c_str());
    for(rapidjson::Value::ValueIterator iter = doc.Begin(); iter != doc.End(); iter ++) {
        rapidjson::Value list = (*iter).GetArray();
        if(list.IsNull()) {
            continue;
        }
        for(rapidjson::Value::ValueIterator iter2 = list.Begin(); iter != list.End(); iter ++) {
            rapidjson::Value taskJson = (*iter2).GetObject();
            if(taskJson.IsNull()) {
                continue;
            }
            RoleTask* task = new RoleTask();
            task->setLevel(taskJson["level"].GetInt());
            task->setStatus(taskJson["status"].GetInt());
            task->setExp(taskJson["exp"].GetInt());
            task->setMoney(taskJson["money"].GetInt());
            task->setTime(taskJson["time"].GetInt());
            task->setId(taskJson["id"].GetInt());
            task->setTaskId(taskJson["taskId"].GetInt());
            task->setDifficultyLevel(taskJson["difficultyLevel"].GetInt());
            const char* nameCh = taskJson["name"].GetString();
            char name[sizeof(nameCh)+1];
            strcpy(name, nameCh);
            task->setName(name);
            task->setPower(taskJson["power"].GetInt());
            task->setMp(taskJson["mp"].GetInt());
            vector->push_back(task);
        }
    }
    return vector;
}

bool RoleTaskListService::updateTask(RoleTask *task) {
    std::string taskList = RoleTaskListConfig::getData();
    Document doc;
    doc.Parse(taskList.c_str());
    rapidjson::Value newTask(kObjectType);
    newTask.SetObject();
    newTask.AddMember(rapidjson::Value("id", doc.GetAllocator()), rapidjson::Value(task->getId()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("name", doc.GetAllocator()), rapidjson::Value(task->getName(), doc.GetAllocator()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("money", doc.GetAllocator()), rapidjson::Value(task->getMoney()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("exp", doc.GetAllocator()), rapidjson::Value(task->getExp()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("time", doc.GetAllocator()), rapidjson::Value(task->getTime()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("power", doc.GetAllocator()), rapidjson::Value(task->getPower()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("mp", doc.GetAllocator()), rapidjson::Value(task->getMp()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("level", doc.GetAllocator()), rapidjson::Value(task->getLevel()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("status", doc.GetAllocator()), rapidjson::Value(task->getStatus()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("taskId", doc.GetAllocator()), rapidjson::Value(task->getId()), doc.GetAllocator());
    newTask.AddMember(rapidjson::Value("difficultyLevel", doc.GetAllocator()), rapidjson::Value(task->getDifficultyLevel()), doc.GetAllocator());
    std::string level = StringUtils::format("%d", task->getLevel());
    if(doc[level.c_str()].IsNull()) {
        rapidjson::Value levelList(kArrayType);
        doc.AddMember(rapidjson::Value(level.c_str(), doc.GetAllocator()), levelList, doc.GetAllocator());
    }
    for(rapidjson::Value::ValueIterator iter = doc[level.c_str()].GetArray().Begin(); iter != doc[level.c_str()].GetArray().End(); iter ++) {
        rapidjson::Value value = (*iter).GetObject();
        if(value["id"].GetInt() == task->getId()) {
            doc[level.c_str()].GetArray().Erase(iter);
            break;
        }
    }
    doc[level.c_str()].PushBack(newTask, doc.GetAllocator());
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);
    log("角色任务更新后的json：%s", buffer.GetString());
    RoleTaskListConfig::updateTaskList(buffer.GetString());
    return true;
}