#ifndef BOOKSYSTEM_H
#define BOOKSYSTEM_H
#include <bits/stdc++.h>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;
class Book // 单本图书的类
{

    // 数据结构
    int id;
    int BorrowTimes;
    int Current;
    int Total;
    double Price;
    string BookCode;
    string Name;
    string Author;
    string Publisher;
    fstream file;   // 文件流对象，以供整个类使用
    json Book_Json; // json对象，以供整个类使用

public:
    Book(const json &OpenedBook); // 构造函数

    void ReadData(const json &OpenedBook); // 初始化数据 被所有open方法调用
    // open方法 打开并读取json文件中的数据 然后获得一个theBook对象
    void open();
    void openId(int id);                        // 以id为参数读取json文件 最基础，其他的open方法都是在此基础上实现的
    void openCode(const string &InputBookCode); // 以图书编号为参数读取json文件
    void openName(string &Name);                // 以图书名称为参数读取json文件

    // 操作数据
    void show();   // 显示数据
    void save();   // 保存数据
    void close();  // 关闭文件
    void setAll(); // 设置数据

    // 借阅和归还
    void Borrow(); // 借书
    void Return(); // 还书

    // Getter接口和Setter接口
    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    int getBorrowTimes() const { return BorrowTimes; }
    void setBorrowTimes(int times) { BorrowTimes = times; }

    int getCurrent() const { return Current; }
    void setCurrent(int current) { Current = current; }

    int getTotal() const { return Total; }
    void setTotal(int total) { Total = total; }

    double getPrice() const { return Price; }
    void setPrice(double price) { Price = price; }

    string getBookCode() const { return BookCode; }
    void setBookCode(const string &code) { BookCode = code; }

    string getName() const { return Name; }
    void setName(const string &name) { Name = name; }

    string getAuthor() const { return Author; }
    void setAuthor(const string &author) { Author = author; }

    string getPublisher() const { return Publisher; }
    void setPublisher(const string &publisher) { Publisher = publisher; }
};

#endif