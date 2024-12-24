#ifndef USER_H
#define USER_H

#include "BookSystem.h"
#include "UserSystem.h"
#include "Book.h"
#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;
class record
{
public:
    string BookCode;
    string BookID;
    bool BookReturn;
    string BorrowTime;
    string ReturnTime;
    record(const json &j) // json格式构造函数
    {
        BookCode = j["BookCode"];
        BookID = j["BookID"];
        BookReturn = j["BookReturn"];
        BorrowTime = j["BorrowTime"];
        ReturnTime = j["ReturnTime"];
    }
};

class User
{
private:
    string ID;
    string name;
    string password;
    int type;
    vector<record> records;

public:
    void open();
    void close();
    void save();
    void load();
    // 传入Name进行构造
    User(string &InputName);
    User(json &InputJson, string &InputI);
    // 新建用户
    User(string ID, string name, string password, int type);
    // getter和setter接口
    string getID() { return ID; }
    void setID(string ID) { this->ID = ID; }
    string getName() { return name; }
    void setName(string name) { this->name = name; }
    string getPassword() { return password; }
    void setPassword(string password) { this->password = password; }
    int getType() { return type; }
    void setType(int type) { this->type = type; }
    vector<record> getRecords() { return records; }
    void setRecords(vector<record> records) { this->records = records; }
    
    void ModifyPassword();
    // 显示用户信息
    void ShowInfo();
    void ShowRecords();
    // 添加借阅记录
    void AddRecord(record record);
    void DeleteRecord(string BookCode);
    void ModifyRecord(string BookCode);
};

#endif
