// UserManager.cpp
#include "UserManager.h"
#include "BookManager.h"
#include <bits/stdc++.h>

#include "nlohmann/json.hpp"
using json = nlohmann::json;
// 重构 不再使用txt 改用json
using namespace std;

void UserManager::RegisterUser()
{
    cout << endl
         << "请输入新用户名：" << endl;
    string temp_name;
    cin >> temp_name;
    if (!UserFind(temp_name))
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
            fstream file("../data/User.json", ios::in | ios::out);
            if (!file.is_open())
            {
                cerr << "无法打开文件 User.json" << endl;
                return;
            }

            // 读取文件内容到json对象
            json j;
            file >> j;
            bool flag = 1;
            for (int i = 1; i < j.size(); i++)
            {
                json temp_user = j[to_string(i)];
                if (temp_user["name"] == temp_name)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                int current_key = (j["NumberOfUsers"]); // 实现用户数量增加
                int key = current_key + 1;              // 获取key
                // 有问题，因为可能有用户被删除，导致key不连续

                // 判断是否存在用户也为key
                while (j.contains(to_string(key)))
                {
                    key++;
                }
                j["NumberOfUsers"] = key;
                cout << "key:" << key << endl;
                cout << "temp_name:" << temp_name << endl;
                cout << "pass1:" << pass1 << endl;
                // 写入文件

                j[to_string(key)] = {{"name", temp_name}, {"password", pass1}, {"type", "2"}};
                file.seekp(0, ios::beg);
                file << j.dump(4) << endl;
            }
            else
            {
                cout << "用户已存在！请直接登录" << endl;
            }
            file.close();
        }
    }
}

bool UserManager::UserFind(const string &username) // 返回登录结果
{
    ifstream file("../data/User.json");
    if (!file.is_open())
    {
        cerr << "无法打开文件 User.json" << endl;
        return false;
    }

    json j;
    file >> j;
    
    // 遍历 JSON 对象的所有键值对
    for (auto it = j.begin(); it != j.end(); ++it)
    {
        const string &key = it.key();       // 获取键
        const json &value = it.value();     // 获取值
        
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

int UserManager::UserPass(const string &username, const string &password) // 返回登录结果
{
    ifstream file("../data/User.json");
    if (!file.is_open())
    {
        cerr << "无法打开文件 User.json" << endl;
        return -1;
    }

    json j;
    file >> j;
    
    // 遍历 JSON 对象的所有键值对
    for (auto it = j.begin(); it != j.end(); ++it)
    {
        const string &key = it.key();       // 获取键
        const json &value = it.value();     // 获取值
        
        if (key == "NumberOfUsers")
            continue; // 跳过 NumberOfUsers 键
        
        // 检查当前用户的用户名是否与传入的用户名匹配
        if (value["name"] == username)
        {
            // 检查当前用户的密码是否与传入的密码匹配
            if (value["password"] == password)
            {
                return value["type"]; // 密码正确，返回用户类型
            }
            else
            {
                return -1; // 密码错误，返回 -1
            }
        }
    }
    return -1; // 用户不存在，返回 -1
}