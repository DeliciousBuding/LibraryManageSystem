#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#include "LibrarySystem.h"
#include "BookSystem.h"
#include "UserSystem.h"
#include "User.h"
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;

// 主菜单区
void AdminMenu(User *NowUser);
void ReaderMenu(User *NowUser);

// 读者面板区
void SearchBook();
void ShowHotBooks();
void ShowNewBooks();
void BorrowBook(User *NowUser);
void ReturnBook(User *NowUser);

// 用户区
void Login();
void Register();
bool ChangePassword(User *NowUser);

string GetTimeNow();
#endif // LIBRARYSYSTEM_H
