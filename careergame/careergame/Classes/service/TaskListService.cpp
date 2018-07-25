//
// Created by LinusLan on 2018/7/25.
//

#include "TaskListService.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
#include "TaskListConfig.h"
USING_NS_CC;
using namespace rapidjson;
void TaskListService::addTask(Task *task) {
    std::string taskList = TaskListConfig::getData();
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
    std::string level = StringUtils::format("%s", task->getLevel());
    if(doc[level.c_str()].IsNull()) {
        rapidjson::Value levelList(kArrayType);
        doc.AddMember(rapidjson::Value(level.c_str(), doc.GetAllocator()), levelList, doc.GetAllocator());
    }
    doc[level.c_str()].PushBack(newTask, doc.GetAllocator());
    TaskListConfig::updateTaskList(doc);
}

std::vector<Task*>* getTaskList() {
    std::vector<Task*>* vector = new std::vector<Task*> ();
    std::string taskList = TaskListConfig::getData();
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
            Task* task = new Task();
            task->setLevel(taskJson["level"].GetInt());
            task->setStatus(taskJson["status"].GetInt());
            task->setExp(taskJson["exp"].GetInt());
            task->setMoney(taskJson["money"].GetInt());
            task->setTime(taskJson["time"].GetInt());
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