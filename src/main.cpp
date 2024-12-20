#include "LibrarySystem.h"
#include <bits/stdc++.h>
//#include <nlohmann/json.hpp>


//using json = nlohmann::json;
using namespace std;

int main()
{
    
    // library
    LibrarySystem library;
    bool exitOfMain = false;

    while (!exitOfMain)
    {
        int choiceOfMain = 0;
        cout << endl;
        cout << "欢迎进入图书馆管理系统" << endl;
        cout << "1.登录 " << endl;
        cout << "2.注册 " << endl;
        cout << "3.退出 " << endl;
        cout << "请选择：";
        cin >> choiceOfMain;

        if (choiceOfMain != 1 && choiceOfMain != 2 && choiceOfMain != 3)
        {
            cout << endl;
            cout << "输入有误，请重新输入：" << endl;
        }
        switch (choiceOfMain)
        {
        case 1:
            library.Login();
            break;
        case 2:
            library.userManager.RegisterUser();
            break;
        case 3:
            exitOfMain = true;
            break;
        default:
            break;
        }
    }

    return 0;
}
