#ifndef USERSYSTEM_H
#define USERSYSTEM_H

#include <fstream>
#include "nlohmann/json.hpp"
#include <vector>

using namespace std;

class User; // 前向声明 User 类

extern fstream UserFile;
extern json UserJson;
// extern vector<User> Users; // 移除这行

void UserManagerMenu();

void SearchUser();
void AddUser();
void ModifyUser();
void DeleteUser();
void LoadUsers();

void PrintUsers();

void open();
void close();
void save();
void load();
#endif