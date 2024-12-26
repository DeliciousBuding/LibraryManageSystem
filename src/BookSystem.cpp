#include "BookSystem.h"

// 修改: vector<Book> Books; // 初始化Booklist
unordered_map<string, Book> Books; // 初始化Booklist
void BookManagerMenu()
{
    CreateBooks();
    // SaveBooks(true);
    bool exitOfBookManagerMenu = false;
    while (!exitOfBookManagerMenu)
    {
        cout << endl;
        cout << "欢迎进入图书管理系统" << endl;
        cout << "1. 添加图书" << endl;
        cout << "2. 删除图书" << endl;
        cout << "3. 查找图书" << endl;
        cout << "4. 修改图书" << endl;
        cout << "5. 显示所有图书" << endl;
        cout << "6. 退出图书管理系统" << endl;
        cout << "请输入您的选择: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            AddBook();
            break;
        case 2:
            DeleteBook();
            break;
        case 3:
            FindBook();
            break;
        case 4:
            ModifyBook();
            break;
        case 5:
            ShowAllBooks();
            break;
        case 6:
            exitOfBookManagerMenu = true;
            break;
        }
    }
}

void AddBook()
{
}
void DeleteBook()
{
}
void FindBook()
{
}
void ModifyBook()
{
}
void ShowAllBooks()
{
}

void CreateBooks(bool Mode)
{
    ifstream infile("../data/Book.json");
    if (!infile.is_open())
    {
        cout << "文件打开失败" << endl;
        perror("Error opening file"); // 添加此行以输出系统错误信息
        return;
    }
    if (Mode)
        cout << "文件打开成功" << endl;
    json BookJson;
    infile >> BookJson;
    if (Mode)
        cout << BookJson << endl;
    infile.close();
    if (Mode)
        cout << "成功写入BookJson" << endl;
    // 判断Books是否为空
    if (!Books.empty())
    {
        Books.clear();
        if (Mode)
            cout << "成功清空Books" << endl;
    }

    for (auto &theBook : BookJson["Books"]) // 读取BookJson中的每个元素
    {
        Book NewBook;
        int id = theBook["ID"];
        string name = theBook["Name"];
        string bookCode = theBook["ISBN/ISSN"];
        string author = theBook["Author"];
        string publisher = theBook["Publisher"];
        string language = theBook["Language"];
        int edition = theBook["Edition"];
        int publicationYear = theBook["PublicationYear"];
        int publicationMonth = theBook["PublicationMonth"];
        string introduction = theBook["Introduction"];
        int borrowTimes = theBook["BorrowTimes"];
        int total = theBook["Total"];
        int current = theBook["Current"];
        double price = theBook["Price"];
        string originalName = "无";
        string originalAuthor = "无";
        if (theBook.contains("OriginalName"))
            originalName = theBook["OriginalName"];
        if (theBook.contains("OriginalAuthor"))
            originalAuthor = theBook["OriginalAuthor"];
        if (Mode)
            cout << "成功读取一个Book数据" << endl;
        NewBook.setId(id);
        NewBook.setName(name);
        NewBook.setBookCode(bookCode);
        NewBook.setAuthor(author);
        NewBook.setPublisher(publisher);
        NewBook.setLanguage(language);
        NewBook.setEdition(edition);
        NewBook.setPublicationYear(publicationYear);
        NewBook.setPublicationMonth(publicationMonth);
        NewBook.setIntroduction(introduction);
        NewBook.setBorrowTimes(borrowTimes);
        NewBook.setTotal(total);
        NewBook.setCurrent(current);
        NewBook.setPrice(price);
        NewBook.setOriginalName(originalName);
        NewBook.setOriginalAuthor(originalAuthor);
        if (Mode)
            cout << "成功设置Book对象属性" << endl;

        if (Mode)
            cout << "成功构造Book对象" << endl;
        Books.insert(make_pair(bookCode, NewBook)); // 使用bookCode作为键
        if (Mode)
            cout << "成功添加Book对象" << endl;
    }
}

void SaveBooks(bool Mode)
{
    ofstream outfile("../data/Book.json", ios::trunc);
    if (!outfile.is_open())
    {
        cout << "文件打开失败" << endl;
        perror("Error opening file"); // 添加此行以输出系统错误信息
        return;
    }
    // 进行排序
    vector<Book> bookVector;
    for (auto &book : Books)
    {
        bookVector.push_back(book.second);
    }
    sort(bookVector.begin(), bookVector.end(), [](Book &a, Book &b)
         { return a.getId() < b.getId(); });
    json BookJson;
    // 遍历bookVector数组，将每个Book对象转换为json格式并添加到BookJson中
    for (auto &bookPair : bookVector)
    {
        json tempBook;
        tempBook["Name"] = bookPair.getName();
        tempBook["ISBN/ISSN"] = bookPair.getBookCode();
        tempBook["Author"] = bookPair.getAuthor();
        tempBook["Publisher"] = bookPair.getPublisher();
        tempBook["Language"] = bookPair.getLanguage();
        tempBook["Edition"] = bookPair.getEdition();
        tempBook["PublicationYear"] = bookPair.getPublicationYear();
        tempBook["PublicationMonth"] = bookPair.getPublicationMonth();
        tempBook["Introduction"] = bookPair.getIntroduction();
        tempBook["BorrowTimes"] = bookPair.getBorrowTimes();
        tempBook["Total"] = bookPair.getTotal();
        tempBook["Current"] = bookPair.getCurrent();
        tempBook["Price"] = bookPair.getPrice();
        tempBook["OriginalName"] = bookPair.getOriginalName();
        tempBook["OriginalAuthor"] = bookPair.getOriginalAuthor();
        tempBook["ID"] = bookPair.getId();
        BookJson["Books"].push_back(tempBook); // 使用bookCode作为键
    }
    outfile << BookJson.dump(4);
    outfile.close();
}