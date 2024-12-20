
#ifndef READERMANAGER_H
#define READERMANAGER_H
#include <bits/stdc++.h>
using namespace std;
class ReaderManager
{
public:
    //各种管理用户的菜单
    void ReaderManagerMenu();
    void addReader();
    void deleteReader();
    void searchReader();
    void modifyReader();
    
    //操作用户
    void showID(string &id);
    void getID(string &name);
    void deleteID(string id);
    
    //修改用户信息
    void modifyUsername(string target);
    void modifyPassword(string target);
    void modifyType(string target);
    void modifyPassWordToDefault(string target);
   
    void getReaderRecords(string &id);
};

#endif
