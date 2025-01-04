#include "BookSystem.h"

// 修改: vector<Book> Books; // 初始化Booklist
unordered_map<string, Book> Books; // 初始化Booklist
void BookManagerMenu()
{

    // SaveBooks(true);
    bool exitOfBookManagerMenu = false;
    while (!exitOfBookManagerMenu)
    {
        CreateBooks();
        cout << endl;
        cout << "欢迎进入图书管理系统" << endl;
        cout << "1. 添加图书" << endl;
        cout << "2. 删除图书" << endl;
        cout << "3. 查找图书" << endl;
        cout << "4. 修改图书" << endl;
        cout << "5. 显示所有图书" << endl;
        cout << "6. 退出图书管理系统" << endl;
        cout << "请输入您的选择: ";
        int choice = 0;
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
            ShowBooks();
            break;
        case 6:
            exitOfBookManagerMenu = true;
            break;
        }
    }
}
void ShowBooks()
{
    bool exitOfShowAllBooks = false;
    while (!exitOfShowAllBooks)

    { // 查看所有图书
        cout << endl;
        cout << "全部图书列表" << endl;
        cout << "1.按书名顺序排序" << endl;
        cout << "2.按作者顺序排序" << endl;
        cout << "3.按借阅次数排序" << endl;
        cout << "4.按出版社顺序排序" << endl;
        cout << "5.按出版时间排序" << endl;
        cout << "6.按价格排序" << endl;
        cout << "7.返回上一级菜单" << endl;
        cout << "请输入你的选择:";
        int choiceOfShowAllBooks = 0;
        cin >> choiceOfShowAllBooks;
        switch (choiceOfShowAllBooks)
        {
        case 1:
            ShowAllBooks(1);
            break;
        case 2:
            ShowAllBooks(2);
            break;
        case 3:
            ShowAllBooks(3);
            break;
        case 4:
            ShowAllBooks(4);
            break;
        case 5:
            ShowAllBooks(5);
            break;
        case 6:
            ShowAllBooks(6);
            break;
        case 7:
            exitOfShowAllBooks = true;
            break;
        default:
            cout << "输入错误，请重新输入" << endl;
            break;
        }

        break;
    }
}

void AddBook()
{
    string name, bookCode, author, publisher, language, introduction, originalName, originalAuthor;
    int Year, Month, BorrowTimes, Current, Edition, Total;
    double Price;
    cout << "请输入图书名称: ";
    cin >> name;
    cout << "请输入图书原名(如果没有请回车): ";
    cin >> originalName;
    cout << "请输入图书编号: ";
    cin >> bookCode;
    cout << "请输入图书作者: ";
    cin >> author;
    cout << "请输入图书原作者(如果没有请回车): ";
    cin >> originalAuthor;
    cout << "请输入图书出版社: ";
    cin >> publisher;
    cout << "请输入图书语言: ";
    cin >> language;
    cout << "请输入图书简介: ";
    cin >> introduction;
    cout << "请输入图书出版年份: ";
    cin >> Year;
    cout << "请输入图书出版月份: ";
    cin >> Month;
    cout << "请输入图书版次: ";
    cin >> Edition;
    cout << "请输入图书总册数: ";
    cin >> Total;
    cout << "请输入图书当前册数: ";
    cin >> Current;
    cout << "请输入图书价格: ";
    cin >> Price;
    cout << "请输入图书借阅次数: ";
    cin >> BorrowTimes;
    Book NewBook;
    NewBook.setId(Books.size() + 1);
    NewBook.setName(name);
    NewBook.setBookCode(bookCode);
    NewBook.setAuthor(author);
    NewBook.setPublisher(publisher);
    NewBook.setLanguage(language);
    NewBook.setEdition(Edition);
    NewBook.setPublicationYear(Year);
    NewBook.setPublicationMonth(Month);
    NewBook.setIntroduction(introduction);
    NewBook.setBorrowTimes(BorrowTimes);
    NewBook.setTotal(Total);
    NewBook.setCurrent(Current);
    NewBook.setPrice(Price);
    if (!originalName.empty())
        NewBook.setOriginalName(originalName);
    else
        NewBook.setOriginalName("");
    if (!originalAuthor.empty())
        NewBook.setOriginalAuthor(originalAuthor);
    else
        NewBook.setOriginalAuthor("");
    Books.insert(make_pair(bookCode, NewBook)); // 使用bookCode作为键，将Book对象插入map中
    SaveBooks();
}
void DeleteBook()
{
    cout << "请输入图书编号: ";
    string BookCode;
    cin >> BookCode;
    if (Books.find(BookCode) != Books.end())
    {
        Books.erase(BookCode);
        SaveBooks();
        cout << "删除成功" << endl;
    }
}

Book *FindBook(bool Mode)
{
    bool exitOfFindBook = false;
    Book *foundBook = nullptr;

    while (!exitOfFindBook)
    {
        cout << endl;
        int choiceOfFindbook = 0;
        cout << "查找图书菜单" << endl;
        cout << "1.按书名查找" << endl;
        cout << "2.按作者查找" << endl;
        cout << "3.按图书代码查找" << endl;
        cout << "4.所有关键字查找" << endl;
        cout << "5.返回上一级菜单" << endl;
        cout << "请输入您的选择: ";
        cin.clear();

        cin >> choiceOfFindbook;
        cin.ignore(); // 忽略换行符，防止影响后续的 getline

        switch (choiceOfFindbook)
        {
        case 1:
        {
            cout << "请输入书名（模糊查找，支持原名）: ";
            string AbookName;
            getline(cin, AbookName);
            vector<Book> FoundBooks;
            for (auto &i : Books)
            {
                if (i.second.getName().find(AbookName) != string::npos || i.second.getOriginalName().find(AbookName) != string::npos)
                {
                    FoundBooks.push_back(i.second);
                }
            }
            if (!FoundBooks.empty())
            {
                int sum = 1;
                for (auto &i : FoundBooks)
                {
                    cout << endl;
                    cout << "第 " << sum << " 本: " << endl;
                    i.show();
                    sum++;
                }
                if (Mode)
                {
                    cout << "请输入要指定的图书序号: ";
                    int choice;
                    cin >> choice;
                    cin.ignore(); // 忽略换行符
                    if (choice > 0 && choice <= FoundBooks.size())
                    {
                        foundBook = &FoundBooks[choice - 1];
                        exitOfFindBook = true;
                    }
                    else
                    {
                        cout << "无效的序号，请重新输入" << endl;
                    }
                }
            }
            else
            {
                cout << "书名不存在" << endl;
            }
            break;
        }
        case 2:
        {
            cout << "请输入作者（支持模糊查找）: ";
            string Author;
            getline(cin, Author);
            vector<Book> FoundBooks;
            for (auto &i : Books)
            {
                if (i.second.getAuthor().find(Author) != string::npos || i.second.getOriginalAuthor().find(Author) != string::npos)
                {
                    FoundBooks.push_back(i.second);
                }
            }
            if (!FoundBooks.empty())
            {
                int sum = 1;
                for (auto &i : FoundBooks)
                {
                    cout << "第 " << sum << " 本: " << endl;
                    i.show();
                    cout << endl;
                    sum++;
                }
                if (Mode)
                {
                    cout << "请输入要指定的图书序号: ";
                    int choice;
                    cin >> choice;
                    cin.ignore(); // 忽略换行符
                    if (choice > 0 && choice <= FoundBooks.size())
                    {
                        foundBook = &FoundBooks[choice - 1];
                        exitOfFindBook = true;
                    }
                    else
                    {
                        cout << "无效的序号，请重新输入" << endl;
                    }
                }
            }
            else
            {
                cout << "作者不存在" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "请输入图书代码: ";
            string BookCode;
            getline(cin, BookCode);
            if (Books.find(BookCode) != Books.end())
            {
                Books[BookCode].show();
                if (Mode)
                {
                    foundBook = &Books[BookCode];
                    exitOfFindBook = true;
                }
                else
                {
                    exitOfFindBook = true;
                }
            }
            else
            {
                cout << "图书代码不存在" << endl;
            }
            break;
        }
        case 5:
            exitOfFindBook = true;
            break;
        case 4:
        {
            cout << "请输入特定关键字: ";
            string AbookName;
            getline(cin, AbookName);
            vector<Book> FoundBooks;
            for (auto &i : Books)
            {
                if (i.second.getName().find(AbookName) != string::npos || i.second.getOriginalName().find(AbookName) != string::npos || i.second.getAuthor().find(AbookName) != string::npos || i.second.getOriginalAuthor().find(AbookName) != string::npos || i.second.getBookCode().find(AbookName) != string::npos || i.second.getPublisher().find(AbookName) != string::npos || i.second.getLanguage().find(AbookName) != string::npos || i.second.getIntroduction().find(AbookName) != string::npos || i.second.getPublisher().find(AbookName) != string::npos || i.second.getBookCode().find(AbookName) != string::npos)
                {
                    FoundBooks.push_back(i.second);
                }
            }
            if (!FoundBooks.empty())
            {
                int sum = 1;
                for (auto &i : FoundBooks)
                {
                    cout << endl;
                    cout << "第 " << sum << " 本: " << endl;
                    i.show();
                    sum++;
                }
                if (Mode)
                {
                    cout << "请输入要指定的图书序号: ";
                    int choice;
                    cin >> choice;
                    cin.ignore(); // 忽略换行符
                    if (choice > 0 && choice <= FoundBooks.size())
                    {
                        foundBook = &FoundBooks[choice - 1];
                        exitOfFindBook = true;
                    }
                    else
                    {
                        cout << "无效的序号，请重新输入" << endl;
                    }
                }
            }
            else
            {
                cout << "搜索失败" << endl;
            }
            break;
        }
        default:
            cout << "无效的选择，请重新输入" << endl;
            break;
        }
    }

    return foundBook;
}
void ModifyBook()
{
    Book *tempBook = FindBook(1);
    if (tempBook != nullptr)
    {
        tempBook->show();
        bool exitModify = false;
        while (!exitModify)
        {
            cout << "请输入你想修改的属性 (或输入 '退出' 结束修改): " << endl;
            string choice;
            cin.ignore(); // 忽略之前的换行符
            getline(cin, choice);

            if (choice == "退出")
            {
                exitModify = true;
            }
            else if (choice == "书名")
            {
                cout << "请输入新的书名: ";
                string Name;
                getline(cin, Name);
                tempBook->setName(Name);
            }
            else if (choice == "作者")
            {
                cout << "请输入新的作者: ";
                string Author;
                getline(cin, Author);
                tempBook->setAuthor(Author);
            }
            else if (choice == "出版社")
            {
                cout << "请输入新的出版社: ";
                string Publisher;
                getline(cin, Publisher);
                tempBook->setPublisher(Publisher);
            }
            else if (choice == "语言")
            {
                cout << "请输入新的语言: ";
                string Language;
                getline(cin, Language);
                tempBook->setLanguage(Language);
            }
            else if (choice == "版次")
            {
                cout << "请输入新的版次: ";
                int Edition;
                cin >> Edition;
                tempBook->setEdition(Edition);
            }
            else if (choice == "出版年份")
            {
                cout << "请输入新的出版年份: ";
                int PublicationYear;
                cin >> PublicationYear;
                tempBook->setPublicationYear(PublicationYear);
            }
            else if (choice == "出版月份")
            {
                cout << "请输入新的出版月份: ";
                int PublicationMonth;
                cin >> PublicationMonth;
                tempBook->setPublicationMonth(PublicationMonth);
            }
            else if (choice == "简介")
            {
                cout << "请输入新的简介: ";
                string Introduction;
                getline(cin, Introduction);
                tempBook->setIntroduction(Introduction);
            }
            else if (choice == "ISBN/ISSN")
            {
                cout << "请输入新的ISBN/ISSN: ";
                string IsbnIssn;
                getline(cin, IsbnIssn);
                tempBook->setBookCode(IsbnIssn);
            }
            else if (choice == "价格")
            {
                cout << "请输入新的价格: ";
                double Price;
                cin >> Price;
                tempBook->setPrice(Price);
            }
            else if (choice == "总藏书量")
            {
                cout << "请输入新的总藏书量: ";
                int Total;
                cin >> Total;
                tempBook->setTotal(Total);
            }
            else if (choice == "当前数量")
            {
                cout << "请输入新的当前数量: ";
                int Current;
                cin >> Current;
                tempBook->setCurrent(Current);
            }
            else if (choice == "借阅次数")
            {
                cout << "请输入新的借阅次数: ";
                int BorrowTimes;
                cin >> BorrowTimes;
                tempBook->setBorrowTimes(BorrowTimes);
            }
            else if (choice == "原书名")
            {
                cout << "请输入新的原名: ";
                string OriginalName;
                getline(cin, OriginalName);
                tempBook->setOriginalName(OriginalName);
            }
            else if (choice == "原作者名")
            {
                cout << "请输入新的原作者名: ";
                string OriginalAuthor;
                getline(cin, OriginalAuthor);
                tempBook->setOriginalAuthor(OriginalAuthor);
            }
            else
            {
                cout << "输入错误，请重新输入" << endl;
            }

            // 保存修改后的图书信息
            SaveBooks();
        }
    }
}
void ShowAllBooks(int Mode)
{
    cout << "所有图书信息如下: " << endl;
    cout << endl;
    vector<Book> BookList;
    for (auto &book : Books)
    {
        BookList.push_back(book.second);
    }

    switch (Mode)
    {
    case 1: // 按书名顺序排序
        sort(BookList.begin(), BookList.end(), [](Book &a, Book &b)
             { return a.getName() < b.getName(); });
        break;
    case 2: // 按作者顺序排序
        sort(BookList.begin(), BookList.end(), [](Book &a, Book &b)
             { return a.getAuthor() < b.getAuthor(); });
        break;
    case 3: // 按借阅次数排序
        sort(BookList.begin(), BookList.end(), [](Book &a, Book &b)
             { return a.getBorrowTimes() > b.getBorrowTimes(); });
        break;
    case 4: // 按出版社顺序排序
        sort(BookList.begin(), BookList.end(), [](Book &a, Book &b)
             { return a.getPublisher() < b.getPublisher(); });
        break;
    case 5: // 按出版时间排序
        sort(BookList.begin(), BookList.end(), [](Book &a, Book &b)
             {
                 if (a.getPublicationYear() == b.getPublicationYear())
                 {
                     return a.getPublicationMonth() < b.getPublicationMonth();
                 }
                 return a.getPublicationYear() < b.getPublicationYear(); });
        break;
    case 6: // 按价格排序
        sort(BookList.begin(), BookList.end(), [](Book &a, Book &b)
             { return a.getPrice() < b.getPrice(); });
        break;
    default:
        cout << "无效的排序模式" << endl;
        return;
    }
    // 现在想要实现分页显示，即每次只显示一部分图书信息
    int pageSize = 10;                                //
    int pageCount = ceil(BookList.size() / pageSize); // 每页显示10条数据，总共需要多少页

    for (int i = 0; i < pageCount; ++i)
    {
        cout << "第" << i + 1 << "页" << endl;
        int start = i * pageSize;
        int end = min((i + 1) * pageSize, static_cast<int>(BookList.size()));
        for (int j = start; j < end; ++j)
        {
            BookList[j].show();
            cout << endl;
        }
        cout << "------------------------" << endl;
        cout << "按任意键继续，或输入'q'退出" << endl;
        string c;
        getline(cin, c);
        if (c == "q")
        {
            break;
        }
        //cin.ignore();
    }

    /*
    for (auto &book : BookList)
    {
        book.show();
        cout << endl;
    }
    */
}

Book *GetBookByCode(string BookCode)
{
    if (Books.find(BookCode) != Books.end())
        return &Books[BookCode];
    else
        return nullptr;
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