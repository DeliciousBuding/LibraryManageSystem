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
            fstream file("../data/User.json", ios::in | ios::out | ios::trunc);
            if (!file.is_open())
            {
                cerr << "无法打开文件 User.json" << endl;
                return;
            }

            // 读取文件内容到json对象
            json j;
            file >> j;
            file.close();
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
                cout << "key:" << key << endl;
                // 写入文件
                j[to_string(key)] = {"name", temp_name, "password", pass1, "type", "2"};
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
    ifstream data("../data/User.txt");
    string line;
    string temp_id, temp_username, temp_password, temp_type;

    bool flag = 1;
    while (getline(data, line) && flag)
    {
        // cout<<'!'<<line<<endl;
        if (line.find("name=") != string::npos)
        {
            temp_username = line.substr(line.find("=") + 1);
            if (temp_username == username)
            {
                return 0;
                flag = 0;
            }
        }
    }
    return 1;
}

int UserManager::UserPass(const string &username, const string &password) // 返回登录结果
{
    ifstream data("../data/User.txt");
    string line;
    string temp_id, temp_username, temp_password, temp_type;
    if (!data.is_open())
    {
        std::cerr << "无法打开文件 ../data/User.txt" << std::endl;
        return 0;
    }
    bool flag = 1;
    while (getline(data, line) && flag)
    {
        // cout<<'!'<<line<<endl;
        if (line.find("name=") != string::npos)
        {
            temp_username = line.substr(line.find("=") + 1);
            if (temp_username == username)
            {
                // cout<<"username found"<<endl;
                getline(data, line);
                temp_password = line.substr(line.find("=") + 1);
                if (temp_password == password)
                {
                    getline(data, line);
                    temp_type = line.substr(line.find("=") + 1);
                    flag = 0;
                }
            }
        }
    }

    if (flag == 0)
    {
        User user;                      // 创建User结构体
        return int(temp_type[0] - '0'); // 返回用户类型
    }
    return -1;
    // 返回1 管理员
    // 返回2 读者
    // 返回-1 用户不存在
    // 其他成员变量和函数
}
