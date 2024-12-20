#include <bits/stdc++.h>
#include "BookSystem.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;
Book::Book(json OpenedBook)
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
    fstream file("../data/Book.json");
}
void Book::close()
{
    file.close();
}
void Book::openId(int id)
{
    ifstream file("../data/Book.json");
    if (!file.is_open())
    {
        cerr << "无法打开文件 Book.json" << endl;
        return;
    }
    // 读取文件内容到json对象
    json j;
    file >> j;

    // 检查输入的书序号是否有效
    if (id < 1 || id > j.size())
    {
        cerr << "无效的书序号，请输入1到" << j.size() << "之间的数字" << endl;
        return;
    }

    // 将书序号转换为字符串，因为json对象的键是字符串类型
    string bookKey = to_string(id);

    // 获取并打印第n本书的信息
    if (j.contains(bookKey))
    {
        Book theBook(j[bookKey]);// 创建指定图书对象
    }
    else
    {
        cerr << "未找到指定序号的书" << endl;
        return;
    }

    return;
}
