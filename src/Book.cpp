#include <book.h>

nlohmann::json BookJson;
std::fstream BookFile;

void Book::open()
{
    // 打开Book.json
    if (!BookFile.is_open())
        BookFile.open("../data/Book.json", ios::in | ios::out);
    if (!BookFile.is_open())
        cerr << "无法打开文件 Book.json" << endl;
}
void Book::close()
{
    // 关闭文件
    if (BookFile.is_open())
        BookFile.close();
}
void Book::save()
{
    // 保存数据到 Book.json
    if (BookFile.is_open())
    {
        BookFile.seekp(0, ios::beg);
        BookFile.clear();
        BookFile << BookJson.dump(4);
        BookFile.flush();
    }
    else
    {
        open();
        save();
    }
}
void Book::load()
{
    // 读取数据到BookJson
    if (BookFile.is_open())
        BookFile >> BookJson;
}
Book::Book(string code)
{
    open();
    load();
    // cout << "正在查找书籍" << endl;
    this->bookCode = code;
    // 在json中查找id对应的书籍
    for (auto it = BookJson.begin(); it != BookJson.end(); it++)
    {
        if (it.value()["ISBN/ISSN"] == code)
        {
            // cout << "找到书籍" << endl;
            //  提取书籍信息并填充到Book对象的成员变量中
            this->id = std::stoi(std::string(it.value()["id"]));
            // cout<<"id: "<<this->id<<endl;
            this->borrowTimes = it.value()["BorrowTimes"];
            // cout<<"borrowTimes: "<<this->borrowTimes<<endl;
            this->current = it.value()["Current"];
            // cout<<"current: "<<this->current<<endl;
            this->total = it.value()["Total"];
            // cout<<"total: "<<this->total<<endl;
            this->price = it.value()["Price"];
            // cout<<"price: "<<this->price<<endl;
            this->name = it.value()["Name"];
            // cout<<"name: "<<this->name<<endl;
            if (it.value().contains("OriginalName"))
                this->originalName = it.value()["OriginalName"];
            else
                this->originalName = "无";
            // cout<<"originalName: "<<this->originalName<<endl;
            this->author = it.value()["Author"];
            // cout<<"author: "<<this->author<<endl;
            if (it.value().contains("OriginalAuthor"))
                this->originalAuthor = it.value()["OriginalAuthor"];
            else
                this->originalAuthor = "无";
            // cout<<"originalAuthor: "<<this->originalAuthor<<endl;
            this->bookCode = it.value()["ISBN/ISSN"];
            // cout<<"isbnIssn: "<<this->isbnIssn<<endl;
            this->publisher = it.value()["Publisher"];
            // cout<<"publisher: "<<this->publisher<<endl;
            this->language = it.value()["Language"];
            // cout<<"language: "<<this->language<<endl;
            this->edition = it.value()["Edition"];
            // cout << "edition: " << this->edition;
            this->publicationYear = it.value()["PublicationYear"];
            // cout << "publicationYear: " << this->publicationYear;
            this->publicationMonth = it.value()["PublicationMonth"];
            // cout << "publicationMonth: " << this->publicationMonth;
            this->introduction = it.value()["Introduction"];
            // cout << "introduction: " << this->introduction;
            break; // 找到后退出循环
        }
    }
    close();
}
void Book::show()
{
    cout << "id: " << this->id << endl;
    cout << "borrowTimes: " << this->borrowTimes << endl;
    cout << "current: " << this->current << endl;
    cout << "total: " << this->total << endl;
    cout << "price: " << this->price << endl;
    cout << "name: " << this->name << endl;
    cout << "originalName: " << this->originalName << endl;
    cout << "author: " << this->author << endl;
    cout << "originalAuthor: " << this->originalAuthor << endl;
    cout << "bookCode: " << this->bookCode << endl;
    cout << "publisher: " << this->publisher << endl;
    cout << "language: " << this->language << endl;
    cout << "edition: " << this->edition << endl;
    cout << "publicationYear: " << this->publicationYear << endl;
    cout << "publicationMonth: " << this->publicationMonth << endl;
    cout << "introduction: " << this->introduction << endl;
    cout << endl;
}