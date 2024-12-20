// UserManager.h
#ifndef USERMANAGER_H
#define USERMANAGER_H
#include <bits/stdc++.h>
#include "BookManager.h"
#include "ReaderManager.h"
// #include "LibrarySystem.h" 卧槽卧槽
// 循环依赖：如果LibraryManageSystem和UserManager互相依赖，且头文件的包含顺序导致编译器在处理一个类定义时无法找到另一个类的完整定义。

class BookManager;   // 声明 Book 类
class ReaderManager; // 声明 Book 类

struct BorrowRecord
{
    int bookID;
    int userID;
    std::string borrowDate;
    std::string returnDate;
};

struct User
{
    int id;
    std::string name;
    std::string password;
    std::string type; // 1-管理员、2-读者
    std::vector<BorrowRecord> borrowRecords;
};

class UserManager
{
public:
    void RegisterUser();
    bool UserFind(const std::string &username);
    int UserPass(const std::string &username, const std::string &password);
    void ReaderManage();
    BookManager bookManager;
    ReaderManager readerManager;
};

#endif // USERMANAGER_H
