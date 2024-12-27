#ifndef BOOKSYSTEM_H
#define BOOKSYSTEM_H

#include "nlohmann/json.hpp"
#include "Book.h"
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;
using json = nlohmann::json;

// 变量区
extern unordered_map<string, Book> Books; // 用BookCode为键，Book对象为值

// 创建书籍数据库
void CreateBooks(bool Mode = 0);
void SaveBooks(bool Mode = 0);

// 书籍管理菜单函数
void BookManagerMenu();

// 书籍管理功能函数
void AddBook();
void DeleteBook();
Book *FindBook(bool Mode = 0); // 如果Mode为0，为正常搜索菜单，为1则会返回指定书的指针
void ModifyBook();
void ShowAllBooks(int Mode);
void ShowBooks();
// 书籍管理辅助函数
Book *GetBookByCode(string BookCode);

#endif