// LibrarySystem.h
#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#include "LibrarySystem.h"
#include "UserManager.h"
#include "ReaderManager.h"
#include "BookManager.h"
#include "BookSystem.h"

#include <bits/stdc++.h>
using namespace std;
class UserManager; // 声明 UserManager 类

class LibrarySystem
{
public:
    
    void AdminMenu();
    void ReaderMenu();
    void Login();
    
    
    // 添加 UserManager 类的成员声明
    UserManager userManager;
};

#endif // LIBRARYSYSTEM_H
