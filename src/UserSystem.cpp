#include "User.h"
#include "UserSystem.h"

vector<User> Users; // 在这里定义 Users

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
        LoadUsers();
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

void LoadUsers()
{
    if (Users.empty())
    {
        open();
        load();
        if (!UserJson.is_null() && UserJson.is_object())
        {
            // cout << "UserJson 内容：" << UserJson.dump(4) << endl; // 输出 JSON 内容
            cout << endl;
            for (auto &i : UserJson.items())
            {
                if (!i.value().is_null())
                {
                    string ID = i.key();
                    if (ID == "NumberOfUsers")
                        continue;
                    cout << "正在加载用户 ID: " << ID << endl; // 输出正在加载的用户 ID
                    try
                    {
                        Users.push_back(User(i.value(), ID));
                    }
                    catch (const std::exception &e)
                    {
                        cerr << "加载用户 ID " << ID << " 时发生错误: " << e.what() << endl;
                    }
                }
                else
                {
                    cerr << "警告: UserJson 中包含 null 值，跳过该项。" << endl;
                }
            }
        }
        else
        {
            cerr << "警告: UserJson 为空或不是对象类型。" << endl;
        }
        close();
    }
}

void PrintUsers()
{
    cout << endl;
    cout << "用户列表:" << endl;
    cout << endl;
    for (auto &i : Users)
        i.ShowInfo();
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
            string tempID;
            cin >> tempID;
            for (auto &i : Users)
            {
                if (i.getID() == tempID)
                {
                    i.ShowInfo();
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
                if (i.getName() == tempName)
                {
                    i.ShowInfo();
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

void AddUser()
{
    cout << endl;
    cout << "用户信息添加：" << endl;

    string tempName;
    bool exitOfAddUser = 0;
    while (!exitOfAddUser)
    {
        cout << "请输入用户名：";
        cin >> tempName;
        int flag = 1;
        for (auto &i : Users)
        {
            if (i.getName() == tempName)
            {
                cout << "用户名已存在" << endl;
                flag = 0;
                break;
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
    // 获得用户ID
    string tempID = to_string(Users.size() + 1);
    // 判断是否重复
    int flag = 1;
    while (flag)
    {
        int a = 0;
        for (auto &i : Users)
        {
            if (i.getID() == tempID)
            {
                a = 1;
                break;
            }
        }
        if (a == 0)
        {
            flag = 0;
        }
        else
        {
            tempID = to_string(stoi(tempID) + 1);
        }
    }
    User tempUser(tempID, tempName, tempPassword, tempType);
    Users.push_back(tempUser);
}

void ModifyUser()
{
    bool exitOfModifyUser = 0;
    while (!exitOfModifyUser)
    {
        cout << endl;
        cout << "用户信息修改：" << endl;
        cout << "1.按用户ID修改" << endl;
        cout << "2.按用户名修改" << endl;
        cout << "3.返回上一级菜单" << endl;
        cout << "请输入你的选择：";
        int chooseOfModifyUser;
        cin >> chooseOfModifyUser;
        switch (chooseOfModifyUser)
        {
        case 1:
        {
            cout << "请输入用户ID：";
            string tempID;
            cin >> tempID;
            for (auto &i : Users)
            {
                if (i.getID() == tempID)
                {
                    cout << "请输入新的用户名：";
                    string tempName;
                    cin >> tempName;
                    cout << "请输入新的密码：";
                    string tempPassword;
                    cin >> tempPassword;
                    i.setName(tempName);
                    i.setPassword(tempPassword);

                    cout << "请输入新的用户类型：(1.管理员 2.读者):";
                    int tempType;
                    cin >> tempType;
                    i.setType(tempType);
                    i.ShowInfo();
                    cout << "修改成功" << endl;
                    // 将对象保存到数据流UserJson中
                    UserJson[tempID]["name"] = tempName;
                    UserJson[tempID]["password"] = tempPassword;
                    UserJson[tempID]["type"] = tempType;
                    i.open();
                    i.save();
                    i.close();
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
                if (i.getName() == tempName)
                {
                    string tempID = i.getID();
                    cout << "请输入新的用户名：";
                    string tempName;
                    cin >> tempName;
                    cout << "请输入新的密码：";
                    string tempPassword;
                    cin >> tempPassword;
                    i.setName(tempName);
                    i.setPassword(tempPassword);

                    cout << "请输入新的用户类型：(1.管理员 2.读者):";
                    int tempType;
                    cin >> tempType;
                    i.setType(tempType);
                    i.ShowInfo();
                    cout << "修改成功" << endl;
                    // 将对象保存到数据流UserJson中
                    UserJson[tempID]["name"] = tempName;
                    UserJson[tempID]["password"] = tempPassword;
                    UserJson[tempID]["type"] = tempType;
                    i.open();
                    //cout << UserJson;
                    i.save();
                    i.close();
                }
            }
        }
        case 3:
            exitOfModifyUser = 1;
            break;
        default:
        {
            cout << "输入错误，请重新输入" << endl;
            break;
        }
        }
    }
}

void DeleteUser()
{
}

void open()
{
    // 打开User.json
    if (!UserFile.is_open())
        UserFile.open("../data/User.json", ios::in | ios::out);
    if (!UserFile.is_open())
        cerr << "无法打开文件 User.json" << endl;
}

void close()
{
    // 关闭文件
    if (UserFile.is_open())
        UserFile.close();
}

void save()
{
    // 保存数据到User.json
    if (UserFile.is_open())
        UserFile << UserJson.dump(4);
}

void load()
{
    // 读取数据到User_json
    if (UserFile.is_open())
    {
        UserFile.seekg(0);                                   // 移动到文件开头
        if (UserFile.peek() == ifstream::traits_type::eof()) // 检查文件是否为空
        {
            UserJson = json::object(); // 初始化为空对象
        }
        else
        {
            UserFile >> UserJson;
        }
    }
}