// UserManager.h
#ifndef USERMANAGER_H
#define USERMANAGER_H
#include <bits/stdc++.h>
#include "BookManager.h"
#include "ReaderManager.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;

class BookManager;   // 声明 BookManager 类
class ReaderManager; // 声明 ReaderManager 类

class Record
{
public:
    string BookCode;
    string BookID;
    bool BookReturn;
    string BorrowTime;
    string ReturnTime;

    // 构造函数
    Record(string bookCode, string bookID, bool bookReturn, string borrowTime, string returnTime)
        : BookCode(bookCode), BookID(bookID), BookReturn(bookReturn), BorrowTime(borrowTime), ReturnTime(returnTime) {}

    // 从 JSON 对象加载记录
    Record(const json &j)
        : BookCode(j["BookCode"]), BookID(j["BookID"]), BookReturn(j["BookReturn"]), BorrowTime(j["BorrowTime"]), ReturnTime(j["ReturnTime"]) {}

    // 将记录转换为 JSON 对象
    json to_json() const
    {
        return {{"BookCode", BookCode}, {"BookID", BookID}, {"BookReturn", BookReturn}, {"BorrowTime", BorrowTime}, {"ReturnTime", ReturnTime}};
    }
};

class User
{
public:
    int id;
    string name;
    string password;
    string type;            // 1-管理员、2-读者
    vector<Record> records; // 借阅记录

    // 构造函数
    User(int id, string name, string password, string type, vector<Record> records)
        : id(id), name(name), password(password), type(type), records(records) {}

    // 从 JSON 对象加载用户
    User(const json &j)
        : id(j["id"]), name(j["name"]), password(j["password"]), type(j["type"])
    {
        for (const auto &record : j["record"])
        {
            records.emplace_back(record);
        }
    }

    // 将用户转换为 JSON 对象
    json to_json() const // 返回 JSON 对象 j 而且const 修饰符表示该函数不会修改对象的状态
    {
        json j;
        j["id"] = id;
        j["name"] = name;
        j["password"] = password;
        j["type"] = type;
        for (const auto &record : records)
        {
            j["record"].push_back(record.to_json());
        }
        return j;
    }
};

class UserManager
{
public:
    void RegisterUser();
    bool UserFind(const string &username);
    int UserPass(const string &username, const string &password);
    void open();
    void save();
    void close();

    User Reader; // 用于查看的读者对象

    fstream file;
    json User_Json;
    BookManager bookManager;
    ReaderManager readerManager;

    friend class BookManager;
    friend class ReaderManager;
};

#endif // USERMANAGER_H