#ifndef USERSYSTEM_H
#define USERSYSTEM_H

#include <fstream>
#include "nlohmann/json.hpp"
#include "User.h" // 包含User.h头文件
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;
using json = nlohmann::json;

// 变量区
extern unordered_map<string, User> Users; // 使用name作为键，User对象为值
// 由于unordered_map的键是唯一的，所以可以使用name作为键来查找User对象

// 创建用户数据库
void CreateUsers(bool Mode = 0);
void SaveUsers(bool Mode = 0);

// 用户管理菜单函数
void UserManagerMenu();

// 用户管理功能函数
void RegisterUser(string &name, string &password);
void SearchUser();
void AddUser();
void ModifyUser();
void ModifyUserInfo(User *user);
void DeleteUser();
void PrintUsers();

// 辅助函数
User *GetUserByName(string name);
int GetNewID();
User *FindUserByID(int id);
User *FindUserByName(const string &name);

#endif