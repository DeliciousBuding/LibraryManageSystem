#include "UserSystem.h"

unordered_map<string, User> Users;
void UserManagerMenu() // 管理员用户管理菜单
{
    bool exitOfUserManagerMenu = 0;
    while (!exitOfUserManagerMenu)
    {
        cout << endl;
        cout << "用户管理菜单" << endl;
        cout << "1.用户信息查询" << endl;
        cout << "2.用户信息修改" << endl;
        cout << "3.用户信息删除" << endl;
        cout << "4.用户信息添加" << endl;
        cout << "5.打印用户列表" << endl;
        cout << "6.返回上一级菜单" << endl;
        cout << "请输入你的选择:";
        int chooseOfUserManagerMenu;
        cin >> chooseOfUserManagerMenu;
        switch (chooseOfUserManagerMenu)
        {
        case 1:
            SearchUser();
            break;
        case 2:
            ModifyUser();
            break;
        case 3:
            DeleteUser();
            break;
        case 4:
            AddUser();
            break;
        case 5:
            PrintUsers();
            break;
        case 6:
            exitOfUserManagerMenu = 1;
            break;
        default:
            cout << "输入错误，请重新输入" << endl;
            break;
        }
    }
}
void PrintUsers()
{
    cout << endl;
    cout << "用户列表:" << endl;
    for (auto &i : Users)
    {
        cout << endl;
        i.second.ShowInfo();
        // cout << "用户ID:" << i.second.getID() << endl;
        // cout << "用户名:" << i.second.getName() << endl;
        // cout << "用户类型:" << i.second.getType() << endl;
    }
    cout << endl;
}
void SearchUser()
{
    bool exitOfSearchUser = 0;
    while (!exitOfSearchUser)
    {
        cout << endl;
        cout << "用户信息查询：" << endl;
        cout << "1.按用户ID查询" << endl;
        cout << "2.按用户名查询" << endl;
        cout << "3.返回上一级菜单" << endl;
        cout << "请输入你的选择：";
        int chooseOfSearchUser;
        cin >> chooseOfSearchUser;
        switch (chooseOfSearchUser)
        {
        case 1:
        {
            cout << "请输入用户ID：";
            int tempID;
            cin >> tempID;
            for (auto &it : Users)
            {
                if (it.second.getID() == tempID)
                {
                    it.second.ShowInfo();
                }
                else
                {
                    cout << "未找到该用户" << endl;
                    break;
                }
            }

            break;
        }
        case 2:
        {
            cout << "请输入用户名：";
            string tempName;
            cin >> tempName;
            for (auto &i : Users)
            {
                if (i.second.getName() == tempName)
                {
                    i.second.ShowInfo();
                }
                else
                {
                    cout << "未找到该用户" << endl;
                    break;
                }
            }
        }
        case 3:
            exitOfSearchUser = 1;
            break;
        default:
            cout << "输入错误，请重新输入" << endl;
            break;
        }
    }
}
int GetNewID()
{
    int maxID = 0;
    for (auto &i : Users)
    {
        if (i.second.getID() > maxID)
        {
            maxID = i.second.getID();
        }
    }
    return maxID + 1;
}
void RegisterUser(string &name, string &password)
{
    User NewUser(GetNewID(), name, password, 1);
    Users.insert(make_pair(name, NewUser));
    SaveUsers();
}
void AddUser()
{
    cout << endl;
    cout << "用户添加：" << endl;

    string tempName;
    bool exitOfAddUser = 0;
    while (!exitOfAddUser)
    {
        cout << "请输入用户名：";
        cin >> tempName;
        int flag = 1;
        for (auto &i : Users)
        {
            if (i.second.getName() == tempName)
            {
                cout << "用户名已存在，请重新输入" << endl;
                flag = 0;
            }
            else
            {
                flag = 1;
            }
        }
        if (flag)
        {
            exitOfAddUser = 1;
        }
    }
    cout << "请输入密码：";
    string tempPassword;
    cin >> tempPassword;
    cout << "请输入用户类型：(1.管理员 2.读者)";
    int tempType;
    cin >> tempType;
    User NewUser(GetNewID(), tempName, tempPassword, tempType);
    Users.insert(make_pair(tempName, NewUser));
    SaveUsers();
}

void ModifyUser()
{
    bool exitOfModifyUser = false;
    while (!exitOfModifyUser)
    {
        cout << endl;
        cout << "用户信息修改：" << endl;
        cout << "1.按用户ID修改" << endl;
        cout << "2.按用户名修改" << endl;
        cout << "3.返回上一级菜单" << endl;
        cout << "请输入你的选择：";
        int chooseOfModifyUser;
        User *tempUser = nullptr;
        cin >> chooseOfModifyUser;
        switch (chooseOfModifyUser)
        {
        case 1:
        {
            cout << "请输入用户ID：";
            int tempID;
            cin >> tempID;
            tempUser = FindUserByID(tempID);

            if (tempUser != nullptr)
            {
                cout << "找到用户：" << tempUser->getName() << endl;
                ModifyUserInfo(tempUser); // 修改: 使用解引用指针
            }
            else
            {
                cout << "未找到该用户" << endl;
            }
            break;
        }
        case 2:
        {
            cout << "请输入用户名：";
            string tempName;
            cin >> tempName;
            tempUser = FindUserByName(tempName);

            if (tempUser != nullptr)
            {
                cout << "找到用户：" << tempUser->getName() << endl;
                ModifyUserInfo(tempUser); // 修改: 使用解引用指针
            }
            else
            {
                cout << "未找到该用户" << endl;
            }
            break;
        }
        case 3:
            exitOfModifyUser = true;
            break;
        default:
            cout << "输入错误，请重新输入" << endl;
            break;
        }
    }
}
void ModifyUserInfo(User *tempUser)
{
    bool exitOfModifyUserInfo = false;
    while (!exitOfModifyUserInfo)
    {
        cout << endl;
        cout << "用户信息修改";
        tempUser->ShowInfo();
        cout << endl;
        cout << "1.修改用户名" << endl;
        cout << "2.修改密码" << endl;
        cout << "3.修改用户类型" << endl;
        cout << "4.返回上一级菜单" << endl;
        cout << "请输入你的选择：";
        int chooseOfModifyUserInfo;
        cin >> chooseOfModifyUserInfo;
        switch (chooseOfModifyUserInfo)
        {
        case 1:
        {
            cout << "请输入新用户名：";
            string tempName;
            cin >> tempName;
            tempUser->setName(tempName);
            break;
        }
        case 2:
        {
            cout << "请输入新密码：";
            string tempPassword;
            cin >> tempPassword;
            tempUser->setPassword(tempPassword);
        }
        case 3:
        {
            cout << "请输入新用户类型：";
            int tempType;
            cin >> tempType;
            tempUser->setType(tempType);
        }
        case 4:
            exitOfModifyUserInfo = true;
            break;
        default:
            cout << "输入错误，请重新输入" << endl;
            break;
        }
        SaveUsers();
    }
}

void DeleteUser()
{
    bool exitOfDeleteUser = false;
    while (!exitOfDeleteUser)
    {
        cout << endl;
        cout << "用户删除：" << endl;
        cout << "1.按用户ID删除" << endl;
        cout << "2.按用户名删除" << endl;
        cout << "3.返回上一级菜单" << endl;
        cout << "请输入你的选择：";
        int chooseOfDeleteUser;
        cin >> chooseOfDeleteUser;
        switch (chooseOfDeleteUser)
        {
        case 1:
        {
            cout << "请输入用户ID：";
            int tempID;
            cin >> tempID;
            User *tempUser = FindUserByID(tempID);
            if (tempUser != nullptr)
            {
                cout << "找到用户：" << tempUser->getName() << endl;
                Users.erase(tempUser->getName());
                SaveUsers();
            }
        }
        case 2:
        {
            cout << "请输入用户名：";
            string tempName;
            cin >> tempName;
            User *tempUser = FindUserByName(tempName);
            if (tempUser != nullptr)
            {
                cout << "找到用户：" << tempUser->getName() << endl;
                Users.erase(tempUser->getName());
                SaveUsers();
            }
        }
        case 3:
            exitOfDeleteUser = true;
            break;
        default:
            cout << "输入错误，请重新输入" << endl;
            break;
        }
    }
}

void CreateUsers(bool Mode) // Mode为1时，输出调试信息
{
    ifstream infile("../data/User.json");
    if (!infile.is_open())
    {
        cout << "文件打开失败" << endl;
        perror("Error opening file"); // 添加此行以输出系统错误信息
        return;
    }
    if (Mode)
        cout << "文件打开成功" << endl;
    json UserJson;
    infile >> UserJson;
    if (Mode)
        cout << UserJson << endl;
    infile.close();
    if (Mode)
        cout << "成功写入UserJson" << endl;
    // 判断Users是否为空
    if (Users.size() != 0)
    {
        Users.clear();
        if (Mode)
            cout << "成功清空Users" << endl;
    }

    for (auto &theUser : UserJson["Users"]) // 读取Users数组中的每个元素
    {
        if (Mode)
            cout << theUser["id"] << endl;
        int id = theUser["id"];
        string name = theUser["name"];
        string password = theUser["password"];
        int type = theUser["type"];
        vector<Record> tempRecords;
        if (theUser.contains("records"))
        {
            for (auto &theRecord : theUser["records"]) // 读取records
            {
                tempRecords.push_back(Record(theRecord));
                if (Mode)
                    cout << theRecord << endl;
            }
        }
        // 构造User对象并添加到Users中

        User NewUser(id, name, password, type, tempRecords);
        if (Mode)
            cout << "成功构造User对象" << endl;
        Users.insert(make_pair(name, NewUser));
        if (Mode)
            cout << "成功添加User对象" << endl;
    }
}

// src/UserSystem.cpp
bool cmpID(User &a, User &b)
{
    return a.getID() < b.getID();
}
void SaveUsers(bool Mode)
{
    ofstream outfile("../data/User.json", ios::trunc);
    if (!outfile.is_open())
    {
        cout << "文件打开失败" << endl;
        perror("Error opening file"); // 添加此行以输出系统错误信息
        return;
    }
    json UserJson;

    // 提取用户到 vector 中 便于排序
    vector<User> userVector;
    for (auto &user : Users)
    {
        userVector.push_back(user.second);
    }

    // 对 vector 中的用户按 id 进行排序
    sort(userVector.begin(), userVector.end(), cmpID);

    // 遍历排序后的用户数组，将每个 User 对象转换为 json 格式并添加到 UserJson 中
    for (auto &user : userVector)
    {
        json tempUser;
        tempUser["id"] = user.getID();
        tempUser["name"] = user.getName();
        tempUser["password"] = user.getPassword();
        tempUser["type"] = user.getType();

        if (user.getRecords().size() != 0)
        {
            json tempRecords;
            for (auto &record : user.getRecords()) // 遍历 records 并添加到 tempRecords 中
            {
                json tempRecord;
                tempRecord["BookCode"] = record.getBookCode();
                tempRecord["BookID"] = record.getBookID();
                tempRecord["BookReturn"] = record.getBookReturn();
                tempRecord["BorrowTime"] = record.getBorrowTime();
                tempRecord["ReturnTime"] = record.getReturnTime();
                tempRecords.push_back(tempRecord);
                if (Mode)
                    cout << tempRecord << endl;
            }
            tempUser["records"] = tempRecords;
        }

        UserJson["Users"].push_back(tempUser);
    }

    outfile << UserJson.dump(4);
    outfile.close();
}

User *GetUserByName(string name) // 通过用户名获取用户信息
{
    for (auto &i : Users)
    {
        if (i.second.getName() == name)
        {
            return &i.second;
        }
    }
    return nullptr;
}

User *FindUserByID(int id)
{
    for (auto &i : Users)
    {
        if (i.second.getID() == id)
        {
            return &i.second;
        }
    }
    return nullptr;
}

User *FindUserByName(const string &name)
{
    auto it = Users.find(name);
    if (it != Users.end())
    {
        return &it->second;
    }
    return nullptr;
}