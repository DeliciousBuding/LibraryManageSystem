#include <book.h>

// 默认构造函数
Book::Book()
{
    name = "";
    bookCode = "";
    author = "";
    publisher = "";
    language = "";
    edition = 0;
    publicationYear = 0;
    publicationMonth = 0;
    introduction = "";
    borrowTimes = 0;
    total = 0;
    current = 0;
    price = 0.00;
    originalName = "";
    originalAuthor = "";
}
void Book::show()
{
    cout << "书名：" << name << endl;
    if (originalName != "")
        cout << "原书名：" << originalName << endl;
    cout << "作者：" << author << endl;
    if (originalAuthor != "")
        cout << "原作者名：" << originalAuthor << endl;
    cout << "ISBN/ISSN：" << bookCode << endl;
    cout << "出版社：" << publisher << endl;
    cout << "语言：" << language << endl;
    cout << "版本：" << edition << endl;
    cout << "出版年份：" << publicationYear << endl;
    cout << "出版月份：" << publicationMonth << endl;
    cout << "简介：" << introduction << endl;
    cout << "借阅次数：" << borrowTimes << endl;
    cout << "总数量：" << total << endl;
    cout << "当前数量：" << current << endl;
    cout << "价格：" << fixed<<setprecision(2)<<price << endl;
}
