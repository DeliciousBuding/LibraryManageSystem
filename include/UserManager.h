// UserManager.h
#ifndef USERMANAGER_H
#define USERMANAGER_H
#include <bits/stdc++.h>
#include "BookManager.h"
#include "ReaderManager.h"
// #include "LibrarySystem.h" !!!循环依赖
// 循环依赖：如果LibraryManageSystem和UserManager互相依赖，且头文件的包含顺序导致编译器在处理一个类定义时无法找到另一个类的完整定义。
using namespace std;
class BookManager;   // 声明 Book 类
class ReaderManager; // 声明 Book 类

struct User
{
    int id;
    string name;
    string password;
    string type; // 1-管理员、2-读者
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

    fstream file;
    json User_Json;
    BookManager bookManager;
    ReaderManager readerManager;
};

#endif // USERMANAGER_H
