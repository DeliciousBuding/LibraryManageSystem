// #include "UserManager.h"
#include <bits/stdc++.h>
#include "ReaderManager.h"
using namespace std;

void ReaderManager::ReaderManagerMenu()
{
    bool exitOfReaderManagerMenu = false;
    while (!exitOfReaderManagerMenu)
    {
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
            ReaderManager::addReader();
            break;
        case 2:
            ReaderManager::deleteReader();
            break;
        case 3:
            ReaderManager::modifyReader();
            break;
        case 4:
            ReaderManager::searchReader();
            break;
        case 5:
            exitOfReaderManagerMenu = true;
        default:
            break;
        }
    }
}
void ReaderManager::addReader()
{

    cout << endl;
    cout << "添加用户" << endl;
    cout << "请选择用户类型:" << endl
         << "1.管理员" << endl
         << " 2.读者" << endl;
    int typeOfAddReader;
    cout << "请输入您的选择：";
    cin >> typeOfAddReader;
    cout << "请输入用户名:";
    string readerName;
    cin >> readerName;
    ifstream data("data/User.txt");
    string line;
    string temp_username;

    bool flag = 1;
    while (getline(data, line) && flag)
    {
        // cout<<'!'<<line<<endl;
        if (line.find("name=") != string::npos)
        {
            temp_username = line.substr(line.find("=") + 1);
            if (temp_username == readerName)
            {
                flag = 0;
            }
        }
    }
    data.close();
    if (flag)
    {
        cout << "请输入读者密码:";
        string readerPassword;
        cin >> readerPassword;
        fstream data("data/User.txt", ios::out | ios::in);
        string line;
        getline(data, line);
        int Number = stoi(line);
        Number++;
        data.seekp(0, ios::beg);
        data << Number;
        data.close();

        // 写入新用户信息
        fstream data_write("data/User.txt", ios::out | ios::app);

        cout << "id=" << Number << endl;
        data_write << endl
                   << '{' << endl;
        data_write << "id=" << Number << endl;
        data_write << "name=" << readerName << endl;
        data_write << "password=" << readerPassword << endl;
        data_write << "type=" << typeOfAddReader << endl;
        data_write << '}' << endl;
        data_write.close();
        cout << endl;
        cout << "您已创建成功!" << endl;
    }
    else
    {
        cout << endl;
        cout << "用户名已存在" << endl;
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
        cout << endl;
        cout << "请输入删除内容：";
        cin >> enterOfDeleteReader;
        switch (chooseOfDeleteReader) // 实现删除功能
        {
        case 1:
            getID(enterOfDeleteReader);
            break;
        case 2:
            break;
        case 3:
            exitOfDeleteReader = true;
        default:
            break;
        }

        showID(enterOfDeleteReader);
        cout<<endl;
        if (enterOfDeleteReader == "1")
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
void ReaderManager::deleteID(string id)
{

    // 删除用户信息

    ifstream data_read("data/User.txt");
    vector<string> lines;
    string line;
    bool foundOfdata_read = false;
    while (getline(data_read, line))
    {
        lines.push_back(line);
    }
    data_read.close();
    vector<string> newlines;
    for (size_t i = 0; i < lines.size(); i++)
    {
        if (lines[i].find("id=") != string::npos)
        {
            string temp_id = lines[i].substr(lines[i].find("=") + 1);
            if (temp_id == id)
            {
                newlines.pop_back();
                newlines.pop_back();
                foundOfdata_read = true;
                i += 4;
            }
            else
                newlines.push_back(lines[i]);
        }
        else
        {
            newlines.push_back(lines[i]);
        }
    }
    // 首先读取整个文件内容
    if (foundOfdata_read)
    {
        ofstream data_write("data/User.txt");
        for (size_t i = 0; i < newlines.size(); i++)
        {
            data_write << newlines[i] << endl;
        }
        data_write.close();
        // NUMBER--
        fstream data("data/User.txt", ios::out | ios::in);
        string line;
        getline(data, line);
        int Number = stoi(line);
        Number--;
        data.seekp(0, ios::beg);
        data << Number;
        data.close();
        cout << "删除成功" << endl;
    }
    else
    {
        cout << "未找到该用户" << endl;
    }
    // 将不需要的部分过滤掉
    // 将剩余的部分重新写回文件
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
            enter;
            cout << endl;
            cout << "请输入查询内容：";
            cin >> enter;
            getID(enter);
            break;
        }
        case 2:
        {
            enter;
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
    }
}

void ReaderManager::modifyUsername(string target)
{
    ifstream data_read("data/User.txt");
    vector<string> lines;
    string line;
    bool found = false;
    string newUsername;
    cout << "请输入新的用户名: ";
    cin >> newUsername;

    // 检查新用户名是否已存在
    ifstream check_data("data/User.txt");
    string check_line;
    bool username_exists = false;
    while (getline(check_data, check_line))
    {
        if (check_line.find("name=") != string::npos)
        {
            string existing_username = check_line.substr(check_line.find("=") + 1);
            if (existing_username == newUsername)
            {
                username_exists = true;
                break;
            }
        }
    }
    check_data.close();

    if (username_exists)
    {
        cout << "用户名已存在，请选择其他用户名。" << endl;
        return;
    }

    while (getline(data_read, line))
    {
        if (line.find("id=") != string::npos)
        {
            string temp_id = line.substr(line.find("=") + 1);
            if (temp_id == target)
            {
                found = true;
                lines.push_back("id=" + temp_id);
                getline(data_read, line); // Skip the current name line
                lines.push_back("name=" + newUsername);
                getline(data_read, line); // Skip the password line
                lines.push_back(line);
                getline(data_read, line); // Skip the type line
                lines.push_back(line);
            }
            else
            {
                lines.push_back(line);
            }
        }
        else
        {
            lines.push_back(line);
        }
    }
    data_read.close();

    if (found)
    {
        ofstream data_write("data/User.txt");
        for (const auto &l : lines)
        {
            data_write << l << endl;
        }
        data_write.close();
        cout << "用户名已成功修改。" << endl;
    }
    else
    {
        cout << "未找到该用户。" << endl;
    }
}

void ReaderManager::modifyPassword(string target)
{
    ifstream data_read("data/User.txt");
    vector<string> lines;
    string line;
    bool found = false;
    string newPassword;
    cout << "请输入新的密码: ";
    cin >> newPassword;

    while (getline(data_read, line))
    {
        if (line.find("id=") != string::npos)
        {
            string temp_id = line.substr(line.find("=") + 1);
            if (temp_id == target)
            {
                found = true;
                lines.push_back(line);
                getline(data_read, line); // Skip the name line
                lines.push_back(line);
                getline(data_read, line); // Skip the current password line
                lines.push_back("password=" + newPassword);
                getline(data_read, line); // Skip the type line
                lines.push_back(line);
            }
            else
            {
                lines.push_back(line);
            }
        }
        else
        {
            lines.push_back(line);
        }
    }
    data_read.close();

    if (found)
    {
        ofstream data_write("data/User.txt");
        for (const auto &l : lines)
        {
            data_write << l << endl;
        }
        data_write.close();
        cout << "密码已成功修改。" << endl;
    }
    else
    {
        cout << "未找到该用户。" << endl;
    }
}

void ReaderManager::modifyType(string target)
{
    ifstream data_read("data/User.txt");
    vector<string> lines;
    string line;
    bool found = false;
    string newType;
    cout << "请输入新的用户类型(1为管理员 2为读者): ";
    cin >> newType;

    while (getline(data_read, line))
    {
        if (line.find("id=") != string::npos)
        {
            string temp_id = line.substr(line.find("=") + 1);
            if (temp_id == target)
            {
                found = true;
                lines.push_back(line);
                getline(data_read, line); // Skip the name line
                lines.push_back(line);
                getline(data_read, line); // Skip the password line
                lines.push_back(line);
                getline(data_read, line); // Skip the current type line
                lines.push_back("type=" + newType);
            }
            else
            {
                lines.push_back(line);
            }
        }
        else
        {
            lines.push_back(line);
        }
    }
    data_read.close();

    if (found)
    {
        ofstream data_write("data/User.txt");
        for (const auto &l : lines)
        {
            data_write << l << endl;
        }
        data_write.close();
        cout << "用户类型已成功修改。" << endl;
    }
    else
    {
        cout << "未找到该用户。" << endl;
    }
}

void ReaderManager::modifyPassWordToDefault(string target)
{
    ifstream data_read("data/User.txt");
    vector<string> lines;
    string line;
    bool found = false;
    string defaultPassword = "123456";

    while (getline(data_read, line))
    {
        if (line.find("id=") != string::npos)
        {
            string temp_id = line.substr(line.find("=") + 1);
            if (temp_id == target)
            {
                found = true;
                lines.push_back(line);
                getline(data_read, line); // Skip the name line
                lines.push_back(line);
                getline(data_read, line); // Skip the current password line
                lines.push_back("password=" + defaultPassword);
                getline(data_read, line); // Skip the type line
                lines.push_back(line);
            }
            else
            {
                lines.push_back(line);
            }
        }
        else
        {
            lines.push_back(line);
        }
    }
    data_read.close();

    if (found)
    {
        ofstream data_write("data/User.txt");
        for (const auto &l : lines)
        {
            data_write << l << endl;
        }
        data_write.close();
        cout << "密码已重置为默认值。" << endl;
    }
    else
    {
        cout << "未找到该用户。" << endl;
    }
}
void ReaderManager::showID(string &id)
{
    ifstream data("data/User.txt");
    string line;
    string temp_id, TempUsername, TempPassword, TempType;

    bool flag = 1;
    while (getline(data, line) && flag)
    {
        // cout<<'!'<<line<<endl;
        if (line.find("id=") != string::npos)
        {
            temp_id = line.substr(line.find("=") + 1);
            if (temp_id == id)
            {
                flag = 0;
                getline(data, line);
                // cout << line;
                TempUsername = line.substr(line.find("=") + 1);
                getline(data, line);
                // cout << line;
                TempPassword = line.substr(line.find("=") + 1);
                getline(data, line);
                // cout << line;
                TempType = line.substr(line.find("=") + 1);
            }
        }
    }
    data.close();
    if (!flag)
    {
        cout << endl;
        cout << "用户信息显示面板：" << endl;
        cout << "用户id:" << id << endl;
        cout << "用户名:" << TempUsername << endl;
        cout << "用户密码:" << TempPassword << endl;
        cout << "用户类型:" << TempType << " (1为管理员 2为读者)" << endl;
    }
    else
    {
        cout << "未找到该用户" << endl;
        id = "";
    }
}
void ReaderManager::getID(string &name)
{
    ifstream data("data/User.txt");
    string line;
    string temp_id, temp_username, temp_password, temp_type;

    bool flag = 1;
    while (getline(data, line) && flag)
    {
        // cout<<'!'<<line<<endl;
        if (line.find("id=") != string::npos)
        {
            temp_id = line.substr(line.find("=") + 1);
        }
        if (line.find("name=") != string::npos)
        {
            temp_username = line.substr(line.find("=") + 1);
            if (temp_username == name)
            {
                flag = 0;
            }
        }
    }
    data.close();
    if (!flag)
    {
        name = temp_id;
    }
    else
    {
        cout << endl;
        cout << "未找到该用户" << endl;
    }
}