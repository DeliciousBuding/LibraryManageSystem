// UserManager.cpp
#include "UserManager.h"
#include "BookManager.h"
#include <bits/stdc++.h>
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
    else // 实现登录
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
            // 实现账户数量+1
            fstream data("../data/User.txt", ios::out | ios::in);
            string line;
            getline(data, line);
            int Number = stoi(line);
            Number++;
            data.seekp(0, ios::beg);
            data << Number;
            data.close();

            // 写入新用户信息
            fstream data_write("../data/User.txt", ios::out | ios::app);

            cout << "id=" << Number << endl;
            data_write << endl
                       << '{' << endl;
            data_write << "id=" << Number << endl;
            data_write << "name=" << temp_name << endl;
            data_write << "password=" << pass1 << endl;
            data_write << "type=2" << endl;
            data_write << '}' << endl;
            data_write.close();

            cout << "您已创建成功!" << endl
                 << "请再次登录" << endl;
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
