#include "User.h"
std::fstream UserFile;
nlohmann::json UserJson;
User::User(string &InputName)
{
    // 打开并加载 User.json 文件
    open();
    load();

    // 遍历 UserJson 中的每个用户对象 并且将目标对象转换为 User 对象
    for (auto &i : UserJson.items())
    {
        if (i.value()["name"] == InputName)
        {
            cout << "找到目标用户" << endl;
            ID = i.key(); // 设置用户ID
            name = i.value()["name"];
            password = i.value()["password"];
            type = i.value()["type"];
            if (i.value().contains("records"))
                for (auto &j : i.value()["records"].items())
                {
                    records.push_back(j.value()); // 将借阅记录添加到 records
                }
            break;
            close();
            return;
        }
    }
}
User::User(string tempID, string tempName, string tempPassword, int tempType) // 新建用户并保存到User.json中
{
    this->ID = tempID;
    this->name = tempName;
    this->password = tempPassword;
    this->type = tempType;
    open();
    load();
    json TempUserJson;
    TempUserJson["name"] = name;
    TempUserJson["password"] = password;
    TempUserJson["type"] = type;
    TempUserJson["records"] = json::array();
    // 插入 JSON 对象到 UserJson
    UserJson[ID] = TempUserJson;
    UserJson["NumberOfUsers"] = UserJson.size() - 1;
    save();
    close();
}
User::User(json &InputJson, string &InputID)
{
    // 从json对象中提取用户信息
    ID = InputID;
    // cout << "ID: " << InputID << endl;
    name = InputJson["name"];
    // cout << "name: " << name << endl;
    password = InputJson["password"];
    // cout << "password: " << password << endl;
    type = InputJson["type"];
    // cout << "type: " << type << endl;
    if (InputJson.contains("records"))
    {
        // cout<<"has records" << endl;
        for (auto &i : InputJson["records"].items())
        {

            records.push_back(i.value());
            // cout<<"record: "<<i.value() << endl;
        }
    }

    close();
}
void User::open()
{
    // 打开User.json
    if (!UserFile.is_open())
        UserFile.open("../data/User.json", ios::in | ios::out);
    if (!UserFile.is_open())
        cerr << "无法打开文件 User.json" << endl;
}
void User::close()
{
    // 关闭文件
    if (UserFile.is_open())
        UserFile.close();
}
void User::save()
{
    // 对 UserJson 中的用户对象按顺序排序
    json sortedUserJson;
    for (int i = 1; i <= UserJson["NumberOfUsers"]; ++i)
    {
        std::string key = std::to_string(i);
        if (UserJson.contains(key))
        {
            sortedUserJson[key] = UserJson[key];
        }
    }
    sortedUserJson["NumberOfUsers"] = UserJson["NumberOfUsers"];

    // 对每个用户的 records 按顺序排序
    for (auto &[key, value] : sortedUserJson.items())
    {
        if (key != "NumberOfUsers" && value.contains("records"))
        {
            json sortedRecords;
            for (int i = 1; i <= value["records"].size(); ++i)
            {
                std::string recordKey = std::to_string(i);
                if (value["records"].contains(recordKey))
                {
                    sortedRecords[recordKey] = value["records"][recordKey];
                }
            }
            sortedUserJson[key]["records"] = sortedRecords;
        }
    }

    // 保存数据到 User.json
    if (UserFile.is_open())
    {
        UserFile.seekp(0, ios::beg);
        UserFile.clear();
        UserFile << sortedUserJson.dump(4);
        UserFile.flush();
    }
    else
    {
        open();
        save();
    }
}
void User::load()
{
    // 读取数据到User_json
    if (UserFile.is_open())
        UserFile >> UserJson;
}
void User::ShowInfo()
{
    cout << endl
         << endl;
    cout << "用户ID: " << ID << endl;
    cout << "用户名: " << name << endl;
    cout << "密码: " << password << endl;
    cout << "类型: " << type << endl;
    cout << "借阅记录: " << endl;
    for (auto &i : records)
    {
        cout << endl;
        cout << "图书代码: " << i.BookCode << endl;
        cout << "图书ID: " << i.BookID << endl;
        cout << "是否归还: " << i.BookReturn << endl;
        cout << "借阅时间: " << i.BorrowTime << endl;
        cout << "归还时间: " << i.ReturnTime << endl;
    }
}

void User::ShowRecords()
{
    // 遍历 records 并显示每个借阅记录
    cout << endl;
    cout << "借阅记录: " << endl;
    for (auto &i : records)
    {
        Book tempBook(i.BookCode);
        cout << endl;
        cout << "图书名称: " << tempBook.getName() << endl;
        cout << "图书作者: " << tempBook.getAuthor() << endl;
        cout << "图书代码: " << i.BookCode << endl;
        cout << "图书ID:   " << i.BookID << endl;
        cout << "是否归还: " << i.BookReturn << endl;
        cout << "借阅时间: " << i.BorrowTime << endl;
        cout << "归还时间: " << i.ReturnTime << endl;
    }
}
void User::ModifyPassword()
{
    // 修改密码
    cout << endl;
    cout << "请输入新的密码：";
    string tempPassword;
    cin >> tempPassword;
    this->setPassword(tempPassword);
    this->ShowInfo();
    cout << "修改成功" << endl;
    // 将对象保存到数据流UserJson中
    string tempID = this->getID();
    UserJson[tempID]["password"] = tempPassword;
    this->open();
    this->save();
    this->close();
}