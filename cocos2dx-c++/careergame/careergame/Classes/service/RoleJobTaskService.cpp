//
// Created by LinusLan on 2018/7/3.
//

#include <cocos2d/external/json/stringbuffer.h>
#include <cocos2d/external/json/writer.h>
#include "RoleJobTaskService.h"
#include "json/filewritestream.h"
std::vector<RoleJobTask*>* RoleJobTaskService::getTasks() {
    std::vector<RoleJobTask*>* taskList = new std::vector<RoleJobTask*>();
    std::string data = UserDefault::getInstance()->getStringForKey("RoleJobTaskConfig");
    if(data.empty()) {
        data = RoleJobTaskConfig::init();
    }
    log("获取到的data为:%s", data.c_str());
    Document doc;
    doc.Parse(data.c_str());
    log("准备开始组装task对象");
    for(SizeType i = 0; i < doc.Size(); i ++) {
        rapidjson::Value value = doc[i].GetObject();
        RoleJobTask* task = new RoleJobTask();
        std::string name = value["name"].GetString();
        task->setName(name);
        task->setExp(value["exp"].GetInt());
        task->setLevel(value["level"].GetInt());
        task->setId(value["id"].GetInt());
        task->setMoney(value["money"].GetInt());
        task->setStatus(value["status"].GetInt());
        task->setTaskId(value["taskId"].GetInt());
        task->setTime(value["time"].GetInt());
        task->setTimeSpend(value["timeSpend"].GetInt());
        taskList->push_back(task);
    }
    return taskList;
}

void RoleJobTaskService::updateTask(RoleJobTask *task) {
    if(nullptr != task) {
        std::string data = UserDefault::getInstance()->getStringForKey("RoleJobTaskConfig");
        if(data.empty()) {
            data = RoleJobTaskConfig::init();
        }
        log("获取到的data为:%s", data.c_str());
        Document doc;
        doc.Parse(data.c_str());
        for(rapidjson::Value::ValueIterator iter = doc.Begin(); iter != doc.End(); iter ++) {
            rapidjson::Value value = (*iter).GetObject();
            log("开始判断对象");
            if(value["id"].GetInt() == task->getId()) {
                log("id为%d的对象和task为同一个对象，移除对象", value["id"].GetInt());
                doc.Erase(iter);
                log("移除成功，退出循环");
                break;
            }
        }
        log("移除task成功");
        rapidjson::Value taskVal(kObjectType);
        log("创建value成功");
        taskVal.SetObject();
        log("设置value为object成功");
        taskVal.AddMember(rapidjson::Value("name", doc.GetAllocator()), rapidjson::Value(task->getName().c_str(), doc.GetAllocator()), doc.GetAllocator());
        taskVal.AddMember(rapidjson::Value("exp", doc.GetAllocator()), rapidjson::Value(task->getExp()), doc.GetAllocator());
        taskVal.AddMember(rapidjson::Value("id", doc.GetAllocator()), rapidjson::Value(task->getId()), doc.GetAllocator());
        taskVal.AddMember(rapidjson::Value("level", doc.GetAllocator()), rapidjson::Value(task->getLevel()), doc.GetAllocator());
        taskVal.AddMember(rapidjson::Value("money", doc.GetAllocator()), rapidjson::Value(task->getMoney()), doc.GetAllocator());
        taskVal.AddMember(rapidjson::Value("status", doc.GetAllocator()), rapidjson::Value(task->getStatus()), doc.GetAllocator());
        taskVal.AddMember(rapidjson::Value("taskId", doc.GetAllocator()), rapidjson::Value(task->getTaskId()), doc.GetAllocator());
        taskVal.AddMember(rapidjson::Value("time", doc.GetAllocator()), rapidjson::Value(task->getTime()), doc.GetAllocator());
        taskVal.AddMember(rapidjson::Value("timeSpend", doc.GetAllocator()), rapidjson::Value(task->getTimeSpend()), doc.GetAllocator());
        doc.PushBack(taskVal, doc.GetAllocator());
        StringBuffer buffer;
        rapidjson::Writer<StringBuffer> writer(buffer);
        doc.Accept(writer);
        log("角色任务更新后的json：%s", buffer.GetString());
        std::string filePath = RoleJobTaskConfig::getFilePath();
        log("配置路径为：%s", filePath.c_str());
        bool isWrited = FileUtils::getInstance()->writeStringToFile(buffer.GetString(), filePath);
        log("写入到文件成功, %d", isWrited);
        //RoleJobTaskConfig::init();
    }
}