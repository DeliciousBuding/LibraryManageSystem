#include <bits/stdc++.h>
#include "BookSystem.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;
Book::Book(const json &OpenedBook) // 构造函数,初始化数据成员 当需要新建Book时使用
{
    id = OpenedBook.value("id", 0);
    Name = OpenedBook.value("name", "");
    BookCode = OpenedBook.value("ISBN/ISSN", "");
    Author = OpenedBook.value("author", "");
    Publisher = OpenedBook.value("publisher", "");
    Price = OpenedBook.value("price", 0.00);
    Total = OpenedBook.value("Total", 0);
    Current = OpenedBook.value("Current", 0);
    BorrowTimes = OpenedBook.value("BorrowTimes", 0);
}
void Book::ReadData(const json &OpenedBook)
{
    id = OpenedBook.value("id", 0);
    Name = OpenedBook.value("name", "");
    BookCode = OpenedBook.value("ISBN/ISSN", "");
    Author = OpenedBook.value("author", "");
    Publisher = OpenedBook.value("publisher", "");
    Price = OpenedBook.value("price", 0.00);
    Total = OpenedBook.value("Total", 0);
    Current = OpenedBook.value("Current", 0);
    BorrowTimes = OpenedBook.value("BorrowTimes", 0);
}
void Book::open()
{
    // 如果已经打开，直接返回
    if (file.is_open())
    {
        return;
    }
    fstream file("../data/Book.json", ios::in|ios::out);
    if (!file.is_open())
    {
        cerr << "无法打开文件 Book.json" << endl;
        return;
    }
}
void Book::close()
{
    if (file.is_open()) // 只有打开了才关闭
        file.close();
}
void Book::openId(int id)
{
    open();

    // 读取文件内容到json对象
    json Book_Json;
    file >> Book_Json;

    // 检查输入的书序号是否有效
    if (id < 1 || id > Book_Json.size())
    {
        cerr << "无效的书序号，请输入1到" << Book_Json.size() << "之间的数字" << endl;
        return;
    }

    // 将书序号转换为字符串，因为json对象的键是字符串类型
    string bookKey = to_string(id);

    // 获取并打印第n本书的信息
    if (Book_Json.contains(bookKey))
    {
        ReadData(Book_Json[bookKey]); // 读取数据到成员变量
    }
    else
    {
        cerr << "未找到指定序号的书" << endl;
        return;
    }

    return;
}
void Book::openCode(const string &InputBookCode)
{
    open();
    json j = json::parse(file);
    for (auto &i : j)
    {
        if (i["ISBN/ISSN"] == InputBookCode)
        {
            ReadData(i); // 读取数据到成员变量 i即为id
            return;
        }
    }
    cerr << "未找到指定书号的书" << endl;
}
void Book::openName(string &Name)
{
    open();
    json j = json::parse(file);
    for (auto &i : j)
    {
        if (i["书名"] == Name)
        {
            ReadData(i); // 读取数据到成员变量 i即为id
            return;
        }
    }
    cerr << "未找到指定书名的书" << endl;
}
void Book::show()
{
    cout << endl;
    cout << "1.书名：" << Name << endl;
    cout << "2.书号ISBN/ISSN：" << BookCode << endl;
    cout << "3.作者：" << Author << endl;
    cout << "4.出版社：" << Publisher << endl;
    cout << "5.价格：" << Price << endl;
    cout << "6.总数：" << Total << endl;
    cout << "7.当前库存：" << Current << endl;
    cout << "8.借阅次数：" << BorrowTimes << endl;
}
void Book::save()
{
    // 将Book类的数据存入j
    json tempBook;
    tempBook["BorrowTimes"] = BorrowTimes;
    tempBook["Current"] = Current;
    tempBook["ISBN/ISSN"] = BookCode;
    tempBook["Total"] = Total;
    tempBook["author"] = Author;
    tempBook["name"] = Name;
    tempBook["price"] = Price;
    tempBook["publisher"] = Publisher;
    tempBook["id"] = id;

    Book_Json[to_string(id)] = tempBook; // j[id] = tempBook; 相当于j["id"] = tempBook;
    // 对对象j进行存储
    file << Book_Json.dump(4) << endl;

    cout << "数据已保存" << endl
         << endl;
}
void Book::close()
{
    file.close();
}
void Book::setAll()
{
    bool exitOfsetAll = false;
    while (!exitOfsetAll)
    {
        show();
        cout << endl;
        cout << "请输入要修改的字段序号(输入0退出)：";
        int chooseOfsetAll = 0;
        cin >> chooseOfsetAll;
        switch (chooseOfsetAll)
        {
        case 1:
            cout << "请输入新的图书名称：";
            cin >> BookCode;
            setBookCode(BookCode);
            break;
        case 2:
            cout << "请输入新的图书ISBN/ISSN：";
            cin >> Name;
            setName(Name);
            break;
        case 3:
            cout << "请输入新的作者：";
            cin >> Author;
            setAuthor(Author);
            break;
        case 4:
            cout << "请输入新的出版社：";
            cin >> Publisher;
            setPublisher(Publisher);
            break;
        case 5:
            cout << "请输入新的价格：";
            cin >> Price;
            setPrice(Price);
            break;
        case 6:
            cout << "请输入新的总数：";
            cin >> Total;
            setTotal(Total);
            break;
        case 7:
            cout << "请输入新的当前库存：";
            cin >> Current;
            setCurrent(Current);
            break;
        case 8:
            cout << "请输入新的借阅次数：";
            cin >> BorrowTimes;
            setBorrowTimes(BorrowTimes);
            break;
        case 0:
            exitOfsetAll = true;
            break;
        default:
            cout << "无效的选择，请重新输入" << endl;
        }
    }
    save();
}
void Book::Borrow()
{
    if (Current > 0)
    {
        Current--;
        BorrowTimes++;
        save();
    }
}
void Book::Return()
{
    if (Current < Total)
    {
        Current++;
        save();
    }
}