
#ifndef READERMANAGER_H
#define READERMANAGER_H
#include <bits/stdc++.h>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;
class ReaderManager
{
public:
    //各种管理用户的菜单
    void ReaderManagerMenu();
    
    void addReader();

    void deleteReader();
    void deleteID(string id);
    
    void searchReader();
    void modifyReader();
    
    //操作用户
    void showID(string &id);
    void getID(string &name);
    
    string getReaderID(string &name);
    //初始化用户
    void getReader(string &id);//获取用户信息 并初始化到Reader对象中
    void showReader(string &id);//显示用户信息

    //修改用户信息
    void modifyUsername(string target);
    void modifyPassword(string target);
    void modifyType(string target);
    void modifyPassWordToDefault(string target);
    

    void open();//打开并读取文件
    void close();//关闭文件
    void save();//保存文件
    
    json User_json;
    fstream file;

    friend class UserManager;
};

#endif
