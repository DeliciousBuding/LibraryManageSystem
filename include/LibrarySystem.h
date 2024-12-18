// LibrarySystem.h
#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#include "UserManager.h"
#include <bits/stdc++.h>
class UserManager; // 声明 UserManager 类

class LibrarySystem
{
public:
    void AdminMenu();
    void ReaderMenu();
    void Login();
    void Logout();

    // 添加 UserManager 类的成员声明
    UserManager userManager;
};

#endif // LIBRARYSYSTEM_H
