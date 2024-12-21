#include <bits/stdc++.h>
#include "BookSystem.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;
json Book::getBookById(int id)
{
    open();
    json data = json::parse(file);
    string idStr = to_string(id);
    if (data.find(idStr) != data.end())
    {
        return data[idStr];
    }
    return json();
}
// 构造函数, 初始化数据成员 当需要新建Book时使用
Book::Book(int id)
{
    json openedBook = getBookById(id);
    if (!openedBook.is_null())
    {
        this->id = openedBook.value("id", 0);
        name = openedBook.value("Name", "");
        bookCode = openedBook.value("ISBN/ISSN", "");
        author = openedBook.value("Author", "");
        originalAuthor = openedBook.value("OriginalAuthor", "");
        isbnIssn = openedBook.value("ISBN/ISSN", "");
        publisher = openedBook.value("Publisher", "");
        language = openedBook.value("Language", "");
        edition = openedBook.value("Edition", 0);
        publicationYear = openedBook.value("PublicationYear", 0);
        publicationMonth = openedBook.value("PublicationMonth", 0);
        price = openedBook.value("Price", 0.00);
        total = openedBook.value("Total", 0);
        current = openedBook.value("Current", 0);
        borrowTimes = openedBook.value("BorrowTimes", 0);
        introduction = openedBook.value("Introduction", "");
    }
    else
    {
        // 处理未找到书籍的情况
        this->id = 0;
        name = "";
        bookCode = "";
        author = "";
        originalAuthor = "";
        isbnIssn = "";
        publisher = "";
        language = "";
        edition = 0;
        publicationYear = 0;
        publicationMonth = 0;
        price = 0.00;
        total = 0;
        current = 0;
        borrowTimes = 0;
        introduction = "";
    }
}

// 初始化数据 被所有open方法调用
void Book::readData(const json &openedBook)
{
    id = openedBook.value("id", 0);
    name = openedBook.value("Name", "");
    bookCode = openedBook.value("ISBN/ISSN", "");
    author = openedBook.value("Author", "");
    originalAuthor = openedBook.value("OriginalAuthor", "");
    isbnIssn = openedBook.value("ISBN/ISSN", "");
    publisher = openedBook.value("Publisher", "");
    language = openedBook.value("Language", "");
    edition = openedBook.value("Edition", 0);
    publicationYear = openedBook.value("PublicationYear", 0);
    publicationMonth = openedBook.value("PublicationMonth", 0);
    price = openedBook.value("Price", 0.00);
    total = openedBook.value("Total", 0);
    current = openedBook.value("Current", 0);
    borrowTimes = openedBook.value("BorrowTimes", 0);
    introduction = openedBook.value("Introduction", "");
}

// 打开并读取json文件中的数据
void Book::open()
{
    // 如果已经打开，直接返回
    if (file.is_open())
    {
        return;
    }
    file.open("../data/Book.json", ios::in | ios::out);
    if (!file.is_open())
    {
        cerr << "无法打开文件 Book.json" << endl;
    }
}

// 关闭文件
void Book::close()
{
    if (file.is_open()) // 只有打开了才关闭
        file.close();
}

// 以id为参数读取json文件 最基础，其他的open方法都是在此基础上实现的
void Book::openId(int id)
{
    open();

    // 读取文件内容到json对象
    json bookJson;
    file.seekg(0); // 确保文件指针在文件开头
    file >> bookJson;

    // 检查输入的书序号是否有效
    if (id < 1 || id > bookJson.size())
    {
        cerr << "无效的书序号，请输入1到" << bookJson.size() << "之间的数字" << endl;
        return;
    }

    // 将书序号转换为字符串，因为json对象的键是字符串类型
    string bookKey = to_string(id);

    // 获取并读取第n本书的信息
    if (bookJson.contains(bookKey))
    {
        readData(bookJson[bookKey]); // 读取数据到成员变量
    }
    else
    {
        cerr << "未找到指定序号的书" << endl;
        return;
    }
}

// 以图书编号为参数读取json文件
void Book::openCode(const string &inputBookCode)
{
    open();
    json bookJson;
    file.seekg(0); // 确保文件指针在文件开头
    file >> bookJson;

    for (auto &item : bookJson.items())
    {
        if (item.value()["ISBN/ISSN"] == inputBookCode)
        {
            readData(item.value()); // 读取数据到成员变量
            return;
        }
    }
    cerr << "未找到指定书号的书" << endl;
}

// 以图书名称为参数读取json文件
void Book::openName(const string &name)
{
    open();
    json bookJson;
    file.seekg(0); // 确保文件指针在文件开头
    file >> bookJson;

    for (auto &item : bookJson.items())
    {
        if (item.value()["Name"] == name)
        {
            readData(item.value()); // 读取数据到成员变量
            return;
        }
    }
    cerr << "未找到指定书名的书" << endl;
}

// 显示数据
void Book::show()
{
    cout << endl;
    cout << "1. 书名：" << name << endl;
    cout << "2. 原书名：" << originalName << endl;
    cout << "3. 作者：" << author << endl;
    cout << "4. 原作者：" << originalAuthor << endl;
    cout << "5. ISBN/ISSN：" << isbnIssn << endl;
    cout << "6. 出版社：" << publisher << endl;
    cout << "7. 语言：" << language << endl;
    cout << "8. 版本：" << edition << endl;
    cout << "9. 出版年份：" << publicationYear << endl;
    cout << "10. 出版月份：" << publicationMonth << endl;
    cout << "11. 价格：" << price << endl;
    cout << "12. 总数：" << total << endl;
    cout << "13. 当前库存：" << current << endl;
    cout << "14. 借阅次数：" << borrowTimes << endl;
    cout << "15. 简介：" << introduction << endl;
}

// 保存数据
void Book::save()
{
    // 将Book类的数据存入bookJson
    json tempBook;
    tempBook["id"] = id;
    tempBook["Name"] = name;
    tempBook["OriginalName"] = originalName;
    tempBook["Author"] = author;
    tempBook["OriginalAuthor"] = originalAuthor;
    tempBook["ISBN/ISSN"] = isbnIssn;
    tempBook["Publisher"] = publisher;
    tempBook["Language"] = language;
    tempBook["Edition"] = edition;
    tempBook["PublicationYear"] = publicationYear;
    tempBook["PublicationMonth"] = publicationMonth;
    tempBook["Price"] = price;
    tempBook["Total"] = total;
    tempBook["Current"] = current;
    tempBook["BorrowTimes"] = borrowTimes;
    tempBook["Introduction"] = introduction;

    bookJson[to_string(id)] = tempBook; // 将数据存入json对象

    // 将json对象写入文件
    file.seekp(0); // 确保文件指针在文件开头
    file << bookJson.dump(4) << endl;
    file.flush(); // 刷新缓冲区

    cout << "数据已保存" << endl
         << endl;
}

// 设置数据
void Book::setAll()
{
    bool exitOfSetAll = false;
    while (!exitOfSetAll)
    {
        show();
        cout << endl;
        cout << "请输入要修改的字段序号(输入0退出)：";
        int chooseOfSetAll = 0;
        cin >> chooseOfSetAll;
        switch (chooseOfSetAll)
        {
        case 1:
            cout << "请输入新的图书名称：";
            cin >> name;
            setName(name);
            break;
        case 2:
            cout << "请输入新的原书名：";
            cin >> originalName;
            setOriginalName(originalName);
            break;
        case 3:
            cout << "请输入新的作者：";
            cin >> author;
            setAuthor(author);
            break;
        case 4:
            cout << "请输入新的原作者：";
            cin >> originalAuthor;
            setOriginalAuthor(originalAuthor);
            break;
        case 5:
            cout << "请输入新的ISBN/ISSN：";
            cin >> isbnIssn;
            setIsbnIssn(isbnIssn);
            break;
        case 6:
            cout << "请输入新的出版社：";
            cin >> publisher;
            setPublisher(publisher);
            break;
        case 7:
            cout << "请输入新的语言：";
            cin >> language;
            setLanguage(language);
            break;
        case 8:
            cout << "请输入新的版本：";
            cin >> edition;
            setEdition(edition);
            break;
        case 9:
            cout << "请输入新的出版年份：";
            cin >> publicationYear;
            setPublicationYear(publicationYear);
            break;
        case 10:
            cout << "请输入新的出版月份：";
            cin >> publicationMonth;
            setPublicationMonth(publicationMonth);
            break;
        case 11:
            cout << "请输入新的价格：";
            cin >> price;
            setPrice(price);
            break;
        case 12:
            cout << "请输入新的总数：";
            cin >> total;
            setTotal(total);
            break;
        case 13:
            cout << "请输入新的当前库存：";
            cin >> current;
            setCurrent(current);
            break;
        case 14:
            cout << "请输入新的借阅次数：";
            cin >> borrowTimes;
            setBorrowTimes(borrowTimes);
            break;
        case 15:
            cout << "请输入新的简介：";
            cin.ignore(); // 忽略前一个换行符
            getline(cin, introduction);
            setIntroduction(introduction);
            break;
        case 0:
            exitOfSetAll = true;
            break;
        default:
            cout << "无效的选择，请重新输入" << endl;
        }
    }
    save();
}

// 借书
void Book::borrow()
{
    if (current > 0)
    {
        current--;
        borrowTimes++;
        save();
    }
    else
    {
        cout << "当前库存不足，无法借书" << endl;
    }
}

// 还书
void Book::returnBook()
{
    if (current < total)
    {
        current++;
        save();
    }
    else
    {
        total++;
        current++;
        save();
        cout << "库存增加" << endl;
    }
}