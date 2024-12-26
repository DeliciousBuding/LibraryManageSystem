#ifndef USER_H
#define USER_H

#include "BookSystem.h"
#include "Book.h"

using namespace std;
class Record
{
    string BookCode;
    int BookID;
    bool BookReturn;
    string BorrowTime;
    string ReturnTime;

public:
    Record(const json &j) // json格式构造函数
    {
        BookCode = j["BookCode"];
        BookID = j["BookID"];
        BookReturn = j["BookReturn"];
        BorrowTime = j["BorrowTime"];
        ReturnTime = j["ReturnTime"];
    }

    // getter和setter接口
    string getBookCode() { return BookCode; }
    void setBookCode(string BookCode) { this->BookCode = BookCode; }
    int getBookID() { return BookID; }
    void setBookID(int BookID) { this->BookID = BookID; }
    bool getBookReturn() { return BookReturn; }
    void setBookReturn(bool BookReturn) { this->BookReturn = BookReturn; }
    string getBorrowTime() { return BorrowTime; }
    void setBorrowTime(string BorrowTime) { this->BorrowTime = BorrowTime; }
    string getReturnTime() { return ReturnTime; }
    void setReturnTime(string ReturnTime) { this->ReturnTime = ReturnTime; }
};

class User
{
private:
    int ID;
    string name;
    string password;
    int type;
    vector<Record> Records;

public:
    // 构造函数 读取用户
    User(int newID, string newName, string newPassword, int newType, vector<Record> newRecords)
        : ID(newID), name(newName), password(newPassword), type(newType), Records(newRecords) {}

    // 构造函数 新用户
    User(int newID, string newName, string newPassword, int newType)
        : ID(newID), name(newName), password(newPassword), type(newType), Records() {}

    // getter和setter接口
    int getID() { return ID; }
    void setID(int ID) { this->ID = ID; }
    string getName() { return name; }
    void setName(string name) { this->name = name; }
    string getPassword() { return password; }
    void setPassword(string password) { this->password = password; }
    int getType() { return type; }
    void setType(int type) { this->type = type; }
    vector<Record> getRecords() { return Records; }
    void setRecords(vector<Record> Records) { this->Records = Records; }
    
    // 显示用户信息
    void ShowInfo();
    void ShowRecords();
    // 添加借阅记录
    void AddRecord(Record Record);
    
};

#endif
