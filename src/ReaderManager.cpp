
#include <bits/stdc++.h>
#include "ReaderManager.h"
#include "nlohmann/json.hpp"
#include "UserManager.h"
using json = nlohmann::json;
using namespace std;

void ReaderManager::open()
{
    if (!file.is_open())
    {
        file.open("../data/User.json", ios::in | ios::out);
        file >> User_json;
    }
    if (!file.is_open())
    {
        cerr << "无法打开文件 User.json" << endl;
        return;
    }
}
void ReaderManager::close()
{
    if (file.is_open())
        file.close();
    return;
}
void ReaderManager::save()
{
    if (file.is_open())
    {
        file.seekp(0, ios::beg);           // 定位到文件开头
        file << User_json.dump(4) << endl; // 写入更新后的json数据
        // file.flush();                      // 确保所有缓冲区内容都写入文件
        // file.seekp(0, ios::end);           // 移动到文件末尾
        // file.clear();                      // 清除文件状态标志
    }
    else
    {
        cerr << "文件未打开" << endl;
    }
}
string ReaderManager::getReaderID(string &name)
{
    for (auto it = User_json.begin(); it != User_json.end(); ++it)
    {
        if (it.value()["name"] == name)
            return it.key();
    }
}
void ReaderManager::ReaderManagerMenu()
{

    bool exitOfReaderManagerMenu = false;
    while (!exitOfReaderManagerMenu)
    {
        open();
        cout << endl;
        cout << "用户后台管理菜单" << endl;
        cout << "1.添加用户" << endl;
        cout << "2.删除用户" << endl;
        cout << "3.修改用户" << endl;
        cout << "4.查询用户" << endl;
        cout << "5.退出" << endl;
        cout << "请输入你的选择:";
        int chooseOfReaderManagerMenu;
        cin >> chooseOfReaderManagerMenu;
        switch (chooseOfReaderManagerMenu)
        {
        case 1:
            addReader();
            break;
        case 2:
            deleteReader();
            break;
        case 3:
            modifyReader();
            break;
        case 4:
            searchReader();
            break;
        case 5:
            exitOfReaderManagerMenu = true;
        default:
            break;
        }
        close();
    }
}

void ReaderManager::addReader()
{
    bool exitOfAddReader = false;
    while (!exitOfAddReader) // 添加用户
    {
        cout << endl;
        cout << "添加用户" << endl;
        cout << "请选择用户类型:" << endl
             << "1.管理员" << endl
             << "2.读者" << endl
             << "3.退出" << endl;
        int typeOfAddReader;
        cout << "请输入您的选择：";
        cin >> typeOfAddReader;
        if (typeOfAddReader == 3)
        {
            exitOfAddReader = true;
            break;
        }
        if (typeOfAddReader != 1 && typeOfAddReader != 2)
            break;
        cout << "请输入用户名:";
        string readerName;
        cin >> readerName;

        bool flag = 1;
        for (auto it = User_json.begin(); it != User_json.end(); ++it)
        {
            const string &key = it.key();
            const json &value = it.value();

            if (key == "NumberOfUsers") // 跳过 NumberOfUsers 键
                continue;

            if (value["name"] == readerName) // 检查用户名是否已存在
            {
                flag = 0;
                break;
            }
        }

        if (flag)
        {
            cout << "请输入读者密码:";
            string readerPassword;
            cin >> readerPassword;

            int current_key = User_json["NumberOfUsers"]; // 获取当前用户数量
            int key = current_key + 1;                    // 计算新用户的key

            // 判断是否存在用户也为key
            while (User_json.contains(to_string(key)))
            {
                key++;
            }

            User_json["NumberOfUsers"] = key;                                                                                       // 更新用户数量
            User_json[to_string(key)] = {{"name", readerName}, {"password", readerPassword}, {"type", to_string(typeOfAddReader)}}; // 添加新用户信息
            save();                                                                                                                 // 写入更新后的json数据
            cout << endl;
            cout << "您已创建成功!" << endl;
        }
        else
        {
            cout << endl;
            cout << "用户名已存在" << endl;
        }
    }
}

void ReaderManager::deleteReader()
{
    bool exitOfDeleteReader = false;
    while (!exitOfDeleteReader)
    {

        cout << endl;
        cout << "删除读者用户" << endl;
        cout << "1.输入用户名删除" << endl;
        cout << "2.输入用户id删除" << endl;
        cout << "3.退出" << endl;
        int chooseOfDeleteReader;
        cout << "请输入您的选择：";
        cin >> chooseOfDeleteReader;
        string enterOfDeleteReader;
        if (chooseOfDeleteReader == 3)
        {
            exitOfDeleteReader = true;
            break;
        }
        cin >> enterOfDeleteReader;
        switch (chooseOfDeleteReader) // 实现删除功能
        {
        case 1:
            getID(enterOfDeleteReader);
            break;
        case 2:
            break;

        default:

            cout << "输入错误" << endl;
        }
        if (chooseOfDeleteReader == 1 || chooseOfDeleteReader == 2)
        {
            cout << endl;
            cout << "请输入删除内容：";
            showID(enterOfDeleteReader);
            cout << endl;
            if (enterOfDeleteReader == "1") // 主管理员序号为1
            {
                cout << "主管理员不能删除!" << endl;
                exitOfDeleteReader = true;
                break;
            }
            cout << "是否删除？(y/n):";
            char chooseOfDeleteReader2;
            cin >> chooseOfDeleteReader2;
            if (chooseOfDeleteReader2 == 'y')
                deleteID(enterOfDeleteReader);
        }
    }
}

void ReaderManager::deleteID(string id)
{
    bool found = false;
    for (auto it = User_json.begin(); it != User_json.end(); ++it)
    {
        const string &key = it.key();
        const json &value = it.value();

        if (key == "NumberOfUsers") // 跳过 NumberOfUsers 键
            continue;

        if (key == id) // 找到目标用户并删除
        {
            User_json.erase(it);
            // cout<<User_json.dump(4) << endl;//测试输出
            found = true;
            break;
        }
    }

    if (found)
    {
        // User_json["NumberOfUsers"]=User_json["NumberOfUsers"]-1; // 减少用户数量
        int Num = User_json["NumberOfUsers"];
        User_json["NumberOfUsers"] = Num - 1;
        // file << User_json.dump(4) << endl; // 写入更新后的json数据
        // 惨痛教训：原本的file操作没删干净，应该都使用save()
        cout << "删除成功" << endl;
        // cout<<User_json.dump(4) << endl;
        ofstream temp_file("../data/User.json");
        temp_file << User_json.dump(4) << endl;
        temp_file.close();
        // save();
        // close();
    }
    else
    {
        cout << "未找到该用户" << endl;
    }
}

void ReaderManager::searchReader()
{
    bool exitOfSearchReader = false;
    while (!exitOfSearchReader)
    {
        cout << endl;
        cout << "查询用户信息" << endl;
        cout << "1.输入用户名查询" << endl;
        cout << "2.输入用户id查询" << endl;
        cout << "3.退出" << endl;
        cout << "请输入您的选择：";
        int chooseOfSearchReader;
        cin >> chooseOfSearchReader;
        switch (chooseOfSearchReader) // 实现查询功能
        {
        case 1:
        {
            string enter;
            cout << endl;
            cout << "请输入查询内容：";
            cin >> enter;
            getID(enter);
            showID(enter);
            break;
        }
        case 2:
        {
            string enter;
            cout << endl;
            cout << "请输入查询内容：";
            cin >> enter;
            showID(enter);
            break;
        }
        case 3:
            exitOfSearchReader = true;
        default:
            break;
        }
    }
}

void ReaderManager::modifyReader()
{
    cout << endl;
    bool exitOfmodifyReader = false;
    while (!exitOfmodifyReader)
    {
        open();
        cout << endl;
        cout << "修改用户信息" << endl;
        cout << "1.输入用户名" << endl;
        cout << "2.输入用户ID" << endl;
        cout << "3.退出" << endl;
        cout << "请输入您的选择：";
        int chooseOfmodifyReader;
        cin >> chooseOfmodifyReader;
        string enter;
        switch (chooseOfmodifyReader) // 实现查询功能
        {
        case 1:
        {
            cout << endl;
            cout << "请输入查询内容：";
            cin >> enter;
            getID(enter);
            break;
        }
        case 2:
        {
            cout << endl;
            cout << "请输入查询内容：";
            cin >> enter;
            showID(enter);
            break;
        }
        case 3:
            exitOfmodifyReader = true;
        default:
            break;
        }
        if (!exitOfmodifyReader)
        {
            showID(enter);
            if (enter == "")
                break;
            cout << endl;
            cout << "用户修改界面" << endl;
            cout << "请选择要修改的字段：" << endl;
            cout << "1.用户名" << endl;
            cout << "2.用户密码" << endl;
            cout << "3.用户类型" << endl;
            cout << "4.重置用户密码为用户密码(123456)" << endl;
            cout << "5.退出" << endl;
            int chooseOfmodifyReader2;
            cout << "请输入您的选择：";
            cin >> chooseOfmodifyReader2;
            switch (chooseOfmodifyReader2)
            {
            case 1:
                modifyUsername(enter);
                break;
            case 2:
                modifyPassword(enter);
                break;
            case 3:
                modifyType(enter);
                break;
            case 4:
                modifyPassWordToDefault(enter);
                break;
            case 5:
                exitOfmodifyReader = true;
                break;
            default:
                break;
            }
        }
        close();
    }
}

void ReaderManager::modifyUsername(string target)
{
    bool found = false;
    string newUsername;
    cout << "请输入新的用户名: ";
    cin >> newUsername;

    // 检查新用户名是否已存在
    bool username_exists = false;
    for (auto it = User_json.begin(); it != User_json.end(); ++it)
    {
        const string &key = it.key();
        const json &value = it.value();

        if (key == "NumberOfUsers") // 跳过 NumberOfUsers 键
            continue;

        if (value["name"] == newUsername)
        {
            username_exists = true;
            break;
        }
    }

    if (username_exists)
    {
        cout << "用户名已存在，请选择其他用户名。" << endl;
        return;
    }

    for (auto it = User_json.begin(); it != User_json.end(); ++it)
    {
        const string &key = it.key();
        const json &value = it.value();

        if (key == "NumberOfUsers") // 跳过 NumberOfUsers 键
            continue;

        if (key == target) // 找到目标用户并修改用户名
        {
            User_json[key]["name"] = newUsername;
            found = true;
            break;
        }
    }

    if (found)
    {
        save();
        cout << "用户名已成功修改。" << endl;
    }
    else
    {
        cout << "未找到该用户。" << endl;
    }
}

void ReaderManager::modifyPassword(string target)
{
    bool found = false;
    string newPassword;
    cout << "请输入新的密码: ";
    cin >> newPassword;

    for (auto it = User_json.begin(); it != User_json.end(); ++it)
    {
        const string &key = it.key();
        const json &value = it.value();

        if (key == "NumberOfUsers") // 跳过 NumberOfUsers 键
            continue;

        if (key == target) // 找到目标用户并修改密码
        {
            User_json[key]["password"] = newPassword;
            found = true;
            break;
        }
    }

    if (found)
    {
        save();
        cout << "密码已成功修改。" << endl;
    }
    else
    {
        cout << "未找到该用户。" << endl;
    }
}

void ReaderManager::modifyType(string target)
{
    bool found = false;
    string newType;
    cout << "请输入新的用户类型(1为管理员 2为读者): ";
    cin >> newType;

    for (auto it = User_json.begin(); it != User_json.end(); ++it)
    {
        const string &key = it.key();
        const json &value = it.value();

        if (key == "NumberOfUsers") // 跳过 NumberOfUsers 键
            continue;

        if (key == target) // 找到目标用户并修改用户类型
        {
            User_json[key]["type"] = newType;
            found = true;
            break;
        }
    }

    if (found)
    {
        save();
        cout << "用户类型已成功修改。" << endl;
    }
    else
    {
        cout << "未找到该用户。" << endl;
    }
}

void ReaderManager::modifyPassWordToDefault(string target)
{
    bool found = false;
    string defaultPassword = "123456";

    for (auto it = User_json.begin(); it != User_json.end(); ++it)
    {
        const string &key = it.key();
        const json &value = it.value();

        if (key == "NumberOfUsers") // 跳过 NumberOfUsers 键
            continue;

        if (key == target) // 找到目标用户并重置密码
        {
            User_json[key]["password"] = defaultPassword;
            found = true;
            break;
        }
    }

    if (found)
    {
        save();

        cout << "密码已重置为默认值。" << endl;
    }
    else
    {
        cout << "未找到该用户。" << endl;
    }
}

void ReaderManager::showID(string &id)
{
    bool flag = 1;
    for (auto it = User_json.begin(); it != User_json.end(); ++it)
    {
        const string &key = it.key();
        const json &value = it.value();

        if (key == "NumberOfUsers") // 跳过 NumberOfUsers 键
            continue;

        if (key == id) // 找到目标用户并显示信息
        {

            flag = 0;
            cout << endl;
            cout << "用户信息显示面板：" << endl;
            cout << "用户id:" << id << endl;
            cout << "用户名:" << value["name"] << endl;
            cout << "用户密码:" << value["password"] << endl;
            cout << "用户类型:" << value["type"] << " (1为管理员 2为读者)" << endl;
            break;
        }
    }

    if (flag)
    {
        cout << "未找到该用户" << endl;
        id = "";
    }
}

void ReaderManager::getID(string &name)
{
    bool flag = 1;
    for (auto it = User_json.begin(); it != User_json.end(); ++it)
    {
        const string &key = it.key();
        const json &value = it.value();

        if (key == "NumberOfUsers") // 跳过 NumberOfUsers 键
            continue;

        if (value["name"] == name) // 找到目标用户名并获取其id
        {
            flag = 0;
            name = key;
            break;
        }
    }

    if (flag)
    {
        cout << endl;
        cout << "未找到该用户" << endl;
    }
}

User ReaderManager::getReader(string &id)
{
    if (User_json.contains(id))
    {
        json TempUserID = User_json[id];
        User readerObj(TempUserID);
        return readerObj;
        // 将 readerObj 存储到 userManager 的成员变量中
    }
    else
    {
        // 处理找不到用户的情况
        std::cerr << "User with ID " << id << " not found." << std::endl;
    }
}
void ReaderManager::showReader(string &id)
{
    User user = getReader(id);
    user.showInfo();
}