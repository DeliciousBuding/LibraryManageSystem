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
void FindBook();
void ModifyBook();
void ShowAllBooks();

#endif