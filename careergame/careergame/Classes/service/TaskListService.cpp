//
// Created by LinusLan on 2018/7/25.
//

#include "TaskListService.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
#include "TaskListConfig.h"
#include <cocos2d/external/json/stringbuffer.h>
#include <cocos2d/external/json/writer.h>
USING_NS_CC;
using namespace rapidjson;
void TaskListService::addTask(Task *task) {
    Document doc;
    std::string taskList = TaskListConfig::getData();
    log("获取到的系统生成的任务列表为：%s", taskList.c_str());
    if(taskList.empty()) {
        log("获取到的系统生成的任务列表为空");
        doc.SetObject();
    } else {
        log("获取到的系统生成的任务列表不为空");
        doc.Parse(taskList.c_str());
    }
    log("开始生成任务的json数据");
    rapidjson::Value newTask(kObjectType);
    newTask.SetObject();
    log("开始设置json的id");
    newTask.AddMember(rapidjson::Value("id", doc.GetAllocator()), rapidjson::Value(task->getId()), doc.GetAllocator());
    log("开始设置json的name");
    newTask.AddMember(rapidjson::Value("name", doc.GetAllocator()), rapidjson::Value(task->getName(), doc.GetAllocator()), doc.GetAllocator());
    log("开始设置json的money");
    newTask.AddMember(rapidjson::Value("money", doc.GetAllocator()), rapidjson::Value(task->getMoney()), doc.GetAllocator());
    log("开始设置json的exp");
    newTask.AddMember(rapidjson::Value("exp", doc.GetAllocator()), rapidjson::Value(task->getExp()), doc.GetAllocator());
    log("开始设置json的time");
    newTask.AddMember(rapidjson::Value("time", doc.GetAllocator()), rapidjson::Value(task->getTime()), doc.GetAllocator());
    log("开始设置json的power");
    newTask.AddMember(rapidjson::Value("power", doc.GetAllocator()), rapidjson::Value(task->getPower()), doc.GetAllocator());
    log("开始设置json的mp");
    newTask.AddMember(rapidjson::Value("mp", doc.GetAllocator()), rapidjson::Value(task->getMp()), doc.GetAllocator());
    log("开始设置json的level");
    newTask.AddMember(rapidjson::Value("level", doc.GetAllocator()), rapidjson::Value(task->getLevel()), doc.GetAllocator());
    log("开始设置json的status");
    newTask.AddMember(rapidjson::Value("status", doc.GetAllocator()), rapidjson::Value(task->getStatus()), doc.GetAllocator());
    log("开始设置json的difficultyLevel");
    newTask.AddMember(rapidjson::Value("difficultyLevel", doc.GetAllocator()), rapidjson::Value(task->getDifficultyLevel()), doc.GetAllocator());
    std::string level = StringUtils::format("%d", task->getLevel());
    log("开始判断是否有level=%s对应的值", level.c_str());
    if(!doc.HasMember(level.c_str())) {
        log("不存在%s对应的值", level.c_str());
        rapidjson::Value levelList(kArrayType);
        doc.AddMember(rapidjson::Value(level.c_str(), doc.GetAllocator()), levelList, doc.GetAllocator());
    }
    doc[level.c_str()].PushBack(newTask, doc.GetAllocator());
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);
    log("系统任务列表更新后的json：%s", buffer.GetString());
    TaskListConfig::updateTaskList(buffer.GetString());
}

std::vector<Task*>* TaskListService::getTaskList() {
    std::vector<Task*>* vector = new std::vector<Task*> ();
    std::string taskList = TaskListConfig::getData();
    log("得到的系统任务列表为：%s", taskList.c_str());
    Document doc;
    doc.Parse(taskList.c_str());
    for(rapidjson::Value::MemberIterator iter = doc.MemberBegin(); iter != doc.MemberEnd(); iter ++) {
        log("进入json对象类型判断");
        rapidjson::Value list = (iter->value).GetArray();
        if(list.IsNull()) {
            continue;
        }
        for(rapidjson::Value::ValueIterator iter2 = list.Begin(); iter2 != list.End(); iter2 ++) {
            log("进入对应等级的系统任务列表循环");
            rapidjson::Value taskJson = (*iter2).GetObject();
            if(taskJson.IsNull()) {
                continue;
            }
            Task* task = new Task();
            task->setId(taskJson["id"].GetInt());
            task->setLevel(taskJson["level"].GetInt());
            task->setStatus(taskJson["status"].GetInt());
            task->setExp(taskJson["exp"].GetInt());
            task->setMoney(taskJson["money"].GetInt());
            task->setTime(taskJson["time"].GetInt());
            task->setDifficultyLevel(taskJson["difficultyLevel"].GetInt());
            log("开始复制名称");
            const char* nameCh = taskJson["name"].GetString();
            log("name=%s, 长度为：%d", nameCh, strlen(nameCh));
            char* name = new char[strlen(nameCh)+1]();
            strcpy(name, nameCh);
            log("名称复制成功, name = %s", name);
            task->setName(name);
            task->setPower(taskJson["power"].GetInt());
            task->setMp(taskJson["mp"].GetInt());
            vector->push_back(task);
        }
    }
    return vector;
}

bool TaskListService::updateTask(Task *task) {
    std::string taskList = TaskListConfig::getData();
    log("领取的任务id为：%d, 获取到的系统任务为：%s", task->getId(), taskList.c_str());
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
    newTask.AddMember(rapidjson::Value("difficultyLevel", doc.GetAllocator()), rapidjson::Value(task->getDifficultyLevel()), doc.GetAllocator());
    std::string level = StringUtils::format("%d", task->getLevel());
    if(!doc.HasMember(level.c_str())) {
        rapidjson::Value levelList(kArrayType);
        doc.AddMember(rapidjson::Value(level.c_str(), doc.GetAllocator()), levelList, doc.GetAllocator());
    }
    for(rapidjson::Value::ValueIterator iter = doc[level.c_str()].GetArray().Begin(); iter != doc[level.c_str()].GetArray().End(); iter ++) {
        rapidjson::Value& value = (*iter);
        log("循环到等级为%s的系统任务列表的id为：%d，名称为：%s", level.c_str(), value["id"].GetInt(), value["name"].GetString());
        if(value["id"].GetInt() == task->getId()) {
            log("系统任务id%d和玩家领取的任务id%d相同，删除该系统任务id对应的任务，重新新增", value["id"].GetInt(), task->getId());
            doc[level.c_str()].GetArray().Erase(iter);
            break;
        }
    }
    doc[level.c_str()].PushBack(newTask, doc.GetAllocator());
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);
    log("系统任务更新后的json：%s", buffer.GetString());
    TaskListConfig::updateTaskList(buffer.GetString());
}