#ifndef BOOKSYSTEM_H
#define BOOKSYSTEM_H

#include <bits/stdc++.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

class Book // 单本图书的类
{
private:
    // 数据结构
    int id;
    int borrowTimes;
    int current;
    int total;
    double price;
    string bookCode;
    string name;
    string originalName;
    string author;
    string originalAuthor;
    string isbnIssn;
    string publisher;
    string language;
    int edition;
    int publicationYear;
    int publicationMonth;
    string introduction;

    fstream file;  // 文件流对象，以供整个类使用
    json bookJson; // json对象，以供整个类使用

public:
    Book(const json &openedBook); // 构造函数

    void readData(const json &openedBook); // 初始化数据 被所有open方法调用
    // open方法 打开并读取json文件中的数据 然后获得一个theBook对象
    void open();
    void openId(int id);                        // 以id为参数读取json文件 最基础，其他的open方法都是在此基础上实现的
    void openCode(const string &inputBookCode); // 以图书编号为参数读取json文件
    void openName(const string &name);          // 以图书名称为参数读取json文件

    // 操作数据
    void show();   // 显示数据
    void save();   // 保存数据
    void close();  // 关闭文件
    void setAll(); // 设置数据

    // 借阅和归还
    void borrow();     // 借书
    void returnBook(); // 还书

    // Getter接口和Setter接口
    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    int getBorrowTimes() const { return borrowTimes; }
    void setBorrowTimes(int times) { borrowTimes = times; }

    int getCurrent() const { return current; }
    void setCurrent(int current) { this->current = current; }

    int getTotal() const { return total; }
    void setTotal(int total) { this->total = total; }

    double getPrice() const { return price; }
    void setPrice(double price) { this->price = price; }

    string getBookCode() const { return bookCode; }
    void setBookCode(const string &code) { bookCode = code; }

    string getName() const { return name; }
    void setName(const string &name) { this->name = name; }

    string getOriginalName() const { return originalName; }
    void setOriginalName(const string &originalName) { this->originalName = originalName; }

    string getAuthor() const { return author; }
    void setAuthor(const string &author) { this->author = author; }

    string getOriginalAuthor() const { return originalAuthor; }
    void setOriginalAuthor(const string &originalAuthor) { this->originalAuthor = originalAuthor; }

    string getIsbnIssn() const { return isbnIssn; }
    void setIsbnIssn(const string &isbnIssn) { this->isbnIssn = isbnIssn; }

    string getPublisher() const { return publisher; }
    void setPublisher(const string &publisher) { this->publisher = publisher; }

    string getLanguage() const { return language; }
    void setLanguage(const string &language) { this->language = language; }

    int getEdition() const { return edition; }
    void setEdition(int edition) { this->edition = edition; }

    int getPublicationYear() const { return publicationYear; }
    void setPublicationYear(int publicationYear) { this->publicationYear = publicationYear; }

    int getPublicationMonth() const { return publicationMonth; }
    void setPublicationMonth(int publicationMonth) { this->publicationMonth = publicationMonth; }

    string getIntroduction() const { return introduction; }
    void setIntroduction(const string &introduction) { this->introduction = introduction; }
};

#endif