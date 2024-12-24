#include "LibrarySystem.h"
using namespace std;
void Login()
{
    cout << endl;
    string username, password;
    cout << "登录" << endl
         << "请输入您的账号和密码：" << endl;
    cin >> username >> password;
    
    User tempUser(username);
    if(tempUser.getPassword() == password)
    {
        if(tempUser.getType() == 1)
        {
            // 管理员
            AdminMenu(tempUser);
        }
        else
        {
            // 读者
            ReaderMenu(tempUser);
        }
    }
    else
    {
        cout << endl;
        cout << "账号或密码错误，请重新输入" << endl;
    }
}
void Register()
{
    cout << endl;
    string username, password;
    cout << "注册" << endl
         << "请输入您的账号和密码：" << endl;
    cin >> username >> password;
    User temp(username);
    temp.setPassword(password);
    temp.setType(2);
    temp.save();
}
void AdminMenu(User &NowUser)
{
    // 读者用户管理：支持对读者的账号进行增、删、改、查；重置读者默认密码为123456；
    // 书籍信息管理：支持对馆藏图书进行增、删、改、查；
    bool exitOfAdminMenu = false;
    while (!exitOfAdminMenu)
    {
        cout << endl;
        cout << "管理员菜单" << endl;
        cout << "1.用户管理" << endl;
        cout << "2.书籍信息管理" << endl;
        cout << "3.退出" << endl;
        cout << "请输入你的选择:";
        int choiceOfAdminMenu;
        cin >> choiceOfAdminMenu;
        switch (choiceOfAdminMenu)
        {
        case 1:
            UserManagerMenu();
            break;
        case 2:
            // 书籍信息管理
            BookManagerMenu();
            break;
        case 3:
            // 退出
            exitOfAdminMenu = true;
            break;
        }
    }
}
void ReaderMenu(User &NowUser)
{
    // 读者可以查看自己的借阅记录
    // 读者可以搜索图书
    // 读者可以借、还图书
    // 读者可以修改自己的密码
    bool exitOfReaderMenu = false;
    while (!exitOfReaderMenu)
    {
        cout << endl;
        cout << "读者菜单" << endl;
        cout << "1.查看借阅记录" << endl;
        cout << "2.搜索图书" << endl;
        cout << "3.查看热门图书" << endl;
        cout << "4.借、还图书" << endl;
        cout << "5.修改密码" << endl;
        cout << "6.退出" << endl;
        cout << "请输入你的选择:";
        int choiceOfReaderMenu;
        cin >> choiceOfReaderMenu;
        switch (choiceOfReaderMenu)
        {
        case 1:
            // 查看借阅记录
            NowUser.ShowRecords();
            break;
        case 2:
            // 搜索图书
            break;
        case 3:
            // 查看热门图书
            break;
        case 4:
            // 借、还图书
            break;
        case 5:
            // 修改密码
            NowUser.ModifyPassword();
            break;
        case 6:
            exitOfReaderMenu = true;
            break;
        }
    }
}

