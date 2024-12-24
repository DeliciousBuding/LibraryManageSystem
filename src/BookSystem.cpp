#include "BookSystem.h"
vector<Book> Books;
// 初始化Booklist
void CreateBooks(bool Mode = 0)
{
    //  打开Book.json
    if (!BookFile.is_open())
        BookFile.open("../data/Book.json", ios::in | ios::out);
    if (!BookFile.is_open())
        cerr << "无法打开文件 Book.json" << endl;
    if (Mode)
        cout << "Book.json 打开完成" << endl;
    // 读取数据到BookJson
    if (BookFile.is_open())
        BookFile >> BookJson;
    BookFile.close();
    if (Mode)
        cout << "BookJson 初始化完成" << endl;
    // cout << BookJson<<endl;
    //  现在实现BookJson->Books
    // 检查Books是否为空
    if (Books.size() != 0)
    {
        if (Mode)
            cout << "Books不为空,正在重置" << endl;
        // 清空Books
        Books.clear();
    }
    for (size_t i = 0; i < BookJson.size(); ++i)
    {
        auto it = BookJson.begin();
        std::advance(it, i);
        // cout << "正在构造Books" << endl;
        // cout << it.key() << endl;
        string tempcode = it.value()["ISBN/ISSN"];
        // cout << tempcode << endl;
        Book tempbook(tempcode);
        // tempbook.show();
        // cout << "tempbook初始化完成" << endl;
        //  构造一个Book对象
        Books.push_back(tempbook);
        // Books[stoi(it.key())] = tempbook; // 存入Books里 key是id
        // cout << "成功存入Books里" << endl;
    }
    if (Mode)
        cout << "Books 初始化完成" << endl;
}

void BookManagerMenu() // 管理员图书管理菜单
{
    cout << endl;
    CreateBooks(1); // 初始化Books
    SaveBooks(1);   // 保存Books
    // Books[1].show(); // 测试能否输出[1]的图书
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
void addBook()
{
}
void deleteBook()
{
}
void searchBook()
{
}
void modifyBook()
{
}

void SaveBooks(bool Mode = 0)
{
    //  打开Book.json
    if (!BookFile.is_open())
        BookFile.open("../data/Book.json", ios::out | ios::trunc); // 修改: 使用ios::trunc模式确保文件被清空
    if (!BookFile.is_open())
        cerr << "无法打开文件 Book.json" << endl;
    if (Mode)
    {
        cout << "Book.json 打开完成" << endl;
        cout << "正在写入BookJson" << endl;
    }
    // 清空BookJson
    BookJson.clear();
    if (Mode)
        cout << "BookJson 清空完成" << endl;
    // Books->BookJson
    for (auto it : Books)
    {
        json tempbook;
        tempbook["id"] = it.getId();
        tempbook["Name"] = it.getName();
        tempbook["ISBN/ISSN"] = it.getBookCode();
        tempbook["Author"] = it.getAuthor();
        tempbook["Publisher"] = it.getPublisher();
        tempbook["Language"] = it.getLanguage();
        tempbook["Edition"] = it.getEdition();
        tempbook["PublicationYear"] = it.getPublicationYear();
        tempbook["PublicationMonth"] = it.getPublicationMonth();
        tempbook["Introduction"] = it.getIntroduction();
        tempbook["BorrowTimes"] = it.getBorrowTimes();
        tempbook["Total"] = it.getTotal();
        tempbook["Current"] = it.getCurrent();
        tempbook["Price"] = it.getPrice();
        if (it.getOriginalName() != "无")
            tempbook["OriginalName"] = it.getOriginalName();
        if (it.getOriginalAuthor() != "无")
            tempbook["OriginalAuthor"] = it.getOriginalAuthor();
        BookJson[to_string(it.getId())] = tempbook; // 修改: 使用字符串形式的ID作为键
    }
    if (Mode)
        cout << "BookJson 写入完成" << endl;
    // cout<<BookJson<<endl;
    //  保存数据到 Book.json
    if (BookFile.is_open())
    {
        //
        BookFile.seekp(0, ios::beg);
        BookFile.clear();
        BookFile << BookJson.dump(4);
        BookFile.flush();
        if (Mode)
            cout << "Book.json 保存完成" << endl;
    }
}
