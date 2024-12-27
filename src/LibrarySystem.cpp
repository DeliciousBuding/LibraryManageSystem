#include "LibrarySystem.h"
using namespace std;
void Login()
{
    cout << endl;
    CreateUsers();
    // SaveUsers(1);
    string username, password;
    cout << "登录" << endl
         << "请输入您的账号和密码：" << endl;
    cin >> username >> password;
    User *tempUser = GetUserByName(username);
    if (tempUser == nullptr)
    {
        cout << "账号不存在，请重新输入" << endl;
        Login();
    }
    if (tempUser->getPassword() == password)
    {
        if (tempUser->getType() == 1)
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
    CreateUsers();
    cout << endl;
    string username, password;
    cout << "注册" << endl
         << "请输入您的账号和密码：" << endl;
    cin >> username >> password;
    User *tempUser = GetUserByName(username);
    if (tempUser != NULL)
    {
        cout << endl;
        cout << "账号已存在，请重新输入" << endl;
    }
    else
    {
        RegisterUser(username, password);
        cout << "注册成功，请登录" << endl;
    }
}
void AdminMenu(User *NowUser)
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
        int choiceOfAdminMenu = 0;
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
void ReaderMenu(User *NowUser)
{
    CreateBooks();
    bool exitOfReaderMenu = false;
    while (!exitOfReaderMenu)
    {
        cout << endl;
        cout << "读者菜单" << endl;
        cout << "1.查看借阅记录" << endl;
        cout << "2.搜索图书" << endl;
        cout << "3.查看热门图书" << endl;
        cout << "4.查看最新图书" << endl;
        cout << "5.借、还图书" << endl;
        cout << "6.查看所有图书" << endl;
        cout << "7.修改密码" << endl;
        cout << "8.退出" << endl;
        cout << "请输入你的选择:";
        int choiceOfReaderMenu = 0;
        cin >> choiceOfReaderMenu;
        switch (choiceOfReaderMenu)
        {
        case 1:
            // 查看借阅记录
            NowUser->ShowRecords();
            break;
        case 2:
            // 搜索图书
            SearchBook();
            break;
        case 3:
            // 查看热门图书
            ShowHotBooks();
            break;
        case 4:
            // 查看最新图书
            ShowNewBooks();
            break;
        case 5:
        {
            bool exitOfBorrowReturn = false;
            while (!exitOfBorrowReturn)
            {
                // 借、还图书
                cout << endl;
                cout << "当前借阅记录:" << endl;
                NowUser->ShowRecords();
                cout << endl;
                cout << "图书借阅菜单" << endl;
                cout << "1.借阅书籍" << endl;
                cout << "2.归还书籍" << endl;
                cout << "3.返回上一级菜单" << endl;
                cout << "请输入你的选择:";
                int choiceOfBorrowReturn = 0;
                cin >> choiceOfBorrowReturn;
                switch (choiceOfBorrowReturn)
                {
                case 1:
                    BorrowBook(NowUser);
                    break;
                case 2:
                    ReturnBook(NowUser);
                    break;
                case 3:
                    exitOfBorrowReturn = true;
                    break;
                default:
                    cout << "输入错误，请重新输入" << endl;
                    break;
                }
            }
            break;
        }
        case 6:
        {
            ShowBooks();
            break;
        }

        case 7:
            // 修改密码
            if (ChangePassword(NowUser))
            {
                cout << "密码修改成功,请重新登录" << endl;
                exitOfReaderMenu = true;
                Login();
            }

            break;
        case 8:
            exitOfReaderMenu = true;
            break;
        default:
            cout << "输入错误，请重新输入" << endl;
            break;
        }
    }
}
void ShowHotBooks()
{
    vector<Book> tempBooks;
    for (auto &i : Books)
    {
        tempBooks.push_back(i.second);
    }
    sort(tempBooks.begin(), tempBooks.end(), [](Book a, Book b)
         { return a.getBorrowTimes() > b.getBorrowTimes(); }); // 按借阅次数排序
    int sum = 0;
    for (auto &i : tempBooks) // 显示前10本热门图书
    {
        cout << endl;
        i.show();
        sum++;
        if (sum > 10)
            break;
    }
}

void BorrowBook(User *NowUser)
{

    cout << endl;
    cout << "图书借阅菜单" << endl;
    Book *tempBook = FindBook(1);
    if (tempBook == nullptr)
    {
        cout << "未找到目标图书，请重新查找" << endl;
    }
    else
    {
        // 新建借阅记录
        Record tempRecord(tempBook->getBookCode(), tempBook->getId(), false, GetTimeNow(), "");
        NowUser->AddRecord(tempRecord);
        tempBook->setCurrent(tempBook->getCurrent() - 1);
        tempBook->setBorrowTimes(tempBook->getBorrowTimes() + 1);
        cout << "借阅成功" << endl;
        cout << "您的本次借阅记录如下：" << endl;
        tempRecord.ShowRecord();
    }

    SaveBooks();
}
void ReturnBook(User *NowUser)
{

    cout << endl;
    cout << "图书归还菜单" << endl;
    Book *tempBook = FindBook(1);
    if (tempBook == nullptr)
    {
        cout << "未找到目标图书，请重新查找" << endl;
    }
    else
    {
        for (auto &i : NowUser->getRecords())
        {
            if (i.getBookCode() == tempBook->getBookCode())
            {
                i.setBookReturn(true);
                i.setReturnTime(GetTimeNow());
                tempBook->setCurrent(tempBook->getCurrent() + 1);
                cout << "归还成功" << endl;
                cout << "您的本次借阅记录如下：" << endl;
                i.ShowRecord();
            }
            break;
        }
    }

    SaveBooks();
}

void SearchBook()
{
    FindBook();
}

string GetTimeNow()
{
    // 获取当前时间
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // 格式化时间
    ostringstream oss;
    oss << put_time(ltm, "%Y-%m-%d %H:%M");

    return oss.str();
}

bool ChangePassword(User *NowUser)
{
    string oldPassword;
    cout << "请输入旧密码:";
    cin >> oldPassword;
    if (oldPassword != NowUser->getPassword())
    {
        cout << "旧密码错误" << endl;
        return false;
    }
    string newPassword;
    cout << "请输入新密码:";
    cin >> newPassword;
    cout << "请再次输入新密码:";
    string newPassword2;
    cin >> newPassword2;
    if (newPassword != newPassword2)
    {
        cout << "两次输入密码不一致" << endl;
        return false;
    }
    if (newPassword == oldPassword)
    {
        cout << "新密码不能与旧密码相同" << endl;
        return false;
    }
    NowUser->setPassword(newPassword);
    SaveUsers();
    return true;
}
void ShowNewBooks()
{
    vector<Book> tempBooks;
    for (auto &i : Books)
    {
        tempBooks.push_back(i.second);
    }
    sort(tempBooks.begin(), tempBooks.end(), [](Book a, Book b)
         { if(a.getPublicationYear() == b.getPublicationYear())
            return a.getPublicationMonth() > b.getPublicationMonth();
            return a.getPublicationYear() > b.getPublicationYear(); }); // 按id排序
    int sum = 0;
    for (auto &i : tempBooks) // 显示前10本最新图书
    {
        cout << endl;
        i.show();
        sum++;
        if (sum > 10)
            break;
    }
}
