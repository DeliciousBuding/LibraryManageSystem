// UserManager.cpp
#include "UserManager.h"
#include "BookManager.h"
#include "BookSystem.h"
#include <bits/stdc++.h>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;

void UserManager::RegisterUser()
{
    cout << endl
         << "请输入新用户名：" << endl;
    string temp_name;
    cin >> temp_name;
    if (UserFind(temp_name))
    {
        cout << "用户已存在！请直接登录" << endl;
    }
    else // 实现注册
    {
        string pass1, pass2;
        cout << "请输入密码:" << endl;
        cin >> pass1;
        cout << "请再次输入密码:" << endl;
        cin >> pass2;
        if (pass1 != pass2)
        {
            cout << "两次输入的密码不一样！请重新再试" << endl;
        }
        else
        {
            open(); // 读到file

            // 读取文件内容到json对象
            bool flag = true;

            // 遍历查找，判断是否存在用户,过于低效
            for (int i = 1; i <= User_Json["NumberOfUsers"]; i++)
            {
                json temp_user = User_Json[to_string(i)];
                if (temp_user["name"] == temp_name) // 匹配是否存在用户
                {
                    flag = false;
                    break;
                }
            }

            if (flag)
            {
                int current_key = User_Json["NumberOfUsers"]; // 实现用户数量增加
                int key = current_key + 1;                    // 获取key
                // 有问题，因为可能有用户被删除，导致key不连续

                // 判断是否存在用户也为key 获取可用的key(id号)
                while (User_Json.contains(to_string(key)))
                {
                    key++;
                }
                User_Json["NumberOfUsers"] = current_key + 1; // 记录用户数量

                // 写入文件
                User_Json[to_string(key)] = {{"id", key}, {"name", temp_name}, {"password", pass1}, {"type", "2"}, {"record", json::array()}};
                file.seekp(0, ios::beg); // 定位文件开头
                save();
            }
            else
            {
                cout << "用户已存在！请直接登录" << endl;
            }
            close();
        }
    }
}

bool UserManager::UserFind(const string &username) // 返回登录结果 判断用户名是否存在
{
    open();
    close();
    // 遍历 JSON 对象的所有键值对 并检查用户名
    for (auto it = User_Json.begin(); it != User_Json.end(); ++it)
    {
        const string &key = it.key();   // 获取键
        const json &value = it.value(); // 获取值

        if (key == "NumberOfUsers")
            continue; // 跳过 NumberOfUsers 键

        // 检查当前用户的用户名是否与传入的用户名匹配
        if (value["name"] == username)
        {
            return true; // 找到用户，返回 true
        }
    }

    return false; // 未找到用户，返回 false
}

int UserManager::UserPass(const string &username, const string &password) // 返回登录结果 判断密码是否正确
{
    open();
    close();
    // 遍历 JSON 对象的所有键值对
    for (auto it = User_Json.begin(); it != User_Json.end(); ++it)
    {
        const string &key = it.key();   // 获取对象的键
        const json &value = it.value(); // 获取对象的值

        if (key == "NumberOfUsers")
            continue; // 跳过 NumberOfUsers 键

        // 检查当前用户的用户名是否与传入的用户名匹配
        if (value["name"] == username) // 对象中名为"name"的值与传入的用户名匹配
        {
            // 检查当前用户的密码是否与传入的密码匹配
            if (value["password"] == password) // 对象中名为"password"的值与传入的密码匹配
            {
                
                return stoi(value["type"].get<string>()); // 密码正确，返回用户类型
            }
            else
            {
                return -1; // 密码错误，返回 -1
            }
        }
    }
    return -1; // 用户不存在，返回 -1
}

void UserManager::open()
{
    if (!file.is_open())
    {
        file.open("../data/User.json", ios::in | ios::out);
        file >> User_Json;
    }
    if (!file.is_open())
    {
        cerr << "无法打开文件 User.json" << endl;
        return;
    }
}

void UserManager::close()
{
    if (file.is_open())
        file.close();
    return;
}

void UserManager::save()
{
    if (file.is_open())
    {
        file << User_Json.dump(4) << endl;
    }
    else
    {
        cerr << "文件未打开" << endl;
    }
}

void User::showInfo()
{
    cout << "用户名：" << name << endl;
    cout << "密码：" << password << endl;
    cout << "用户类型：" << type << endl;
    cout << "借阅记录：" << endl;
    for (auto &record : records)
    {
        Book tempbook(stoi(record.BookID));
        cout << "图书名称：" << tempbook.getName()<< endl;
        cout << "图书编号：" << record.BookCode << endl;
        cout << "图书ID：" << record.BookID << endl;
    }
}