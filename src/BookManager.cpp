// #include "UserManager.h"
#include <bits/stdc++.h>
#include "BookManager.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;

void BookManager::bookManagerMenu()
{
    bool exitOfBookManagerMenu = false;
    while (!exitOfBookManagerMenu)
    {
        cout << endl;
        cout << "图书后台管理菜单" << endl;
        cout << "1.添加图书" << endl;
        cout << "2.删除图书" << endl;
        cout << "3.修改图书" << endl;
        cout << "4.查询图书" << endl;
        cout << "5.退出" << endl;
        cout << "请输入你的选择:";
        int chooseOfBookManagerMenu;
        cin >> chooseOfBookManagerMenu;
        switch (chooseOfBookManagerMenu)
        {
        case 1:
            addBook();
            break;
        case 2:
            deleteBook();
            break;
        case 3:
            modifyBook();
            break;
        case 4:
            searchBook();
            break;
        case 5:
            exitOfBookManagerMenu = true;
        default:
            break;
        }
    }
}
void BookManager::addBook()
{
}
void BookManager::deleteBook()
{
}
void BookManager::searchBook()
{
    // 打开Book.json文件
    ifstream file("../data/Book.json");
    if (!file.is_open())
    {
        cerr << "无法打开文件 Book.json" << endl;
        return;
    }

    // 读取文件内容到json对象
    json j;
    file >> j;
    file.close();

    int n;
    cout << "请输入要读取的书的序号: ";
    cin >> n;

    // 检查输入的书序号是否有效
    if (n < 1 || n > j.size())
    {
        cerr << "无效的书序号，请输入1到" << j.size() << "之间的数字" << endl;
        return;
    }

    // 将书序号转换为字符串，因为json对象的键是字符串类型
    string bookKey = to_string(n);

    // 获取并打印第n本书的信息
    if (j.contains(bookKey))
    {
        json book = j[bookKey];
        cout << "ID: " << book["id"] << endl;
        cout << "书名: " << book["name"] << endl;
        cout << "ISBN/ISSN: " << book["ISBN/ISSN"] << endl;
        cout << "作者: " << book["author"] << endl;
        cout << "出版社: " << book["publisher"] << endl;
        cout << "价格: " << book["price"] << endl;
        cout << "总量: " << book["Total"] << endl;
        cout << "当前数量: " << book["Current"] << endl;
        cout << "借阅次数: " << book["BorrowTimes"] << endl;
    }
    else
    {
        cerr << "未找到指定序号的书" << endl;
        return;
    }

    return;
}
void BookManager::modifyBook()
{
    // 打开Book.json文件
    ifstream file("../data/Book.json");
    if (!file.is_open())
    {
        cerr << "无法打开文件 Book.json" << endl;
        return;
    }

    // 读取文件内容到json对象
    json j;
    file >> j;
    file.close();

    int n;
    cout << endl;
    cout << "请输入要修改的书的序号（1-" << j.size() << "）: ";
    cin >> n;
    cout << endl;
    // 检查输入的书序号是否有效
    if (n < 1 || n > j.size())
    {
        cerr << "无效的书序号，请输入1到" << j.size() << "之间的数字" << endl;
        return;
    }
    
    // 将书序号转换为字符串，因为json对象的键是字符串类型
    string bookKey = to_string(n);

    // 获取第n本书的信息
    if (j.contains(bookKey))
    {
        json &book = j[bookKey];
        // 打印原图书信息
        cout << endl;
        cout << "当前图书信息如下:" << endl;
        cout << "ID: " << book["id"] << endl;
        cout << "书名: " << book["name"] << endl;
        cout << "ISBN/ISSN: " << book["ISBN/ISSN"] << endl;
        cout << "作者: " << book["author"] << endl;
        cout << "出版社: " << book["publisher"] << endl;
        cout << "价格: " << book["price"] << endl;
        cout << "总量: " << book["Total"] << endl;
        cout << "当前数量: " << book["Current"] << endl;
        cout << "借阅次数: " << book["BorrowTimes"] << endl;
        cout << endl;
        // 提示用户输入新的信息
        cout << "请输入新的图书信息:" << endl;
        // 获取用户输入的新信息
        string id, name, isbn_issn, author, publisher;
        double price;
        int total, current, borrow_times;

        cout << endl;
        cout << "请输入新的图书ID: ";
        cin >> id;
        cout << "请输入新的书名: ";
        cin.ignore(); // 忽略前一个cin留下的换行符
        getline(cin, name);
        cout << "请输入新的ISBN/ISSN: ";
        getline(cin, isbn_issn);
        cout << "请输入新的作者: ";
        getline(cin, author);
        cout << "请输入新的出版社: ";
        getline(cin, publisher);
        cout << "请输入新的价格: ";
        cin >> price;
        cout << "请输入新的总量: ";
        cin >> total;
        cout << "请输入新的当前数量: ";
        cin >> current;
        cout << "请输入新的借阅次数: ";
        cin >> borrow_times;
        cout << endl;
        //输出修改前后的图书信息
        cout << "修改前后图书信息如下:" << endl;
        cout << "ID: " << book["id"] <<" -> "<<id<<endl;
        cout << "书名: " << book["name"] <<" -> \""<<name<<'\"'<<endl;
        cout << "ISBN/ISSN: " << book["ISBN/ISSN"] <<" -> "<<isbn_issn<<endl;
        cout << "作者: " << book["author"] <<" -> \""<<author<<'\"'<<endl;
        cout << "出版社: " << book["publisher"] <<" -> \""<<publisher<<'\"'<<endl;
        cout << "价格: " << book["price"] <<" -> "<<price<<endl;
        cout << "总量: " << book["Total"] <<" -> "<<total<<endl;
        cout << "当前数量: " << book["Current"] <<" -> "<<current<<endl;
        cout << "借阅次数: " << book["BorrowTimes"] <<" -> "<<borrow_times<<endl;
        cout << endl;
        


        // 更新图书信息
        book["id"] = id;
        book["name"] = name;
        book["ISBN/ISSN"] = isbn_issn;
        book["author"] = author;
        book["publisher"] = publisher;
        book["price"] = price;
        book["Total"] = total;
        book["Current"] = current;
        book["BorrowTimes"] = borrow_times;

        
        cout << "你确定要修改吗？(Y/N)" << endl;
        char choice;
        cin >> choice;
        if (choice != 'y' || choice == 'Y')
        {
            cout << "取消修改" << endl;
            return;
        }

        // 将修改后的json对象写回文件
        ofstream outFile("../data/Book.json");
        if (!outFile.is_open())
        {
            cerr << "无法打开文件 Book.json 进行写入" << endl;
            return;
        }
        outFile << j.dump(4); // 使用缩进为4的格式化输出
        outFile.close();
        cout << "图书信息已成功修改" << endl;
    }
    else
    {
        cerr << "未找到指定序号的书" << endl;
        return;
    }
}