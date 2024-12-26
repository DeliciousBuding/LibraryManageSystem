#include "User.h"

void User::ShowInfo()
{
    cout << endl
         << endl;
    cout << "用户ID: " << ID << endl;
    cout << "用户名: " << name << endl;
    cout << "密码: " << password << endl;
    cout << "类型: " << type << endl;
    cout << "借阅记录: " << endl;
    for (auto &i : Records)
    {
        cout << endl;
        cout << "图书代码: " << i.getBookCode() << endl;
        cout << "图书ID: " << i.getBookID() << endl;
        cout << "是否归还: " << i.getBookReturn() << endl;
        cout << "借阅时间: " << i.getBorrowTime() << endl;
        cout << "归还时间: " << i.getReturnTime() << endl;
    }
}

void User::ShowRecords()
{
    // 遍历 records 并显示每个借阅记录
    cout << endl;
    cout << "借阅记录: " << endl;
    for (auto &i : Records)
    {
        // Book tempBook(i.getBookCode());
        cout << endl;
        //cout << "图书名称: " << tempBook.getName() << endl;
        //cout << "图书作者: " << tempBook.getAuthor() << endl;
        cout << "图书代码: " << i.getBookCode() << endl;
        cout << "图书ID:   " << i.getBookID() << endl;
        cout << "是否归还: " << i.getBookReturn() << endl;
        cout << "借阅时间: " << i.getBorrowTime() << endl;
        cout << "归还时间: " << i.getReturnTime() << endl;
    }
}