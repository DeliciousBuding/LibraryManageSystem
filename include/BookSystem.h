#ifndef BOOKSYSTEM_H
#define BOOKSYSTEM_H
#include "nlohmann/json.hpp"
#include "Book.h"
#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;
class Book;
extern json BookJson;
extern fstream BookFile;
extern vector<Book> Books;
//BookSystem可不可以完全通过Book类来进行json的操作？
void BookManagerMenu();

void addBook();
void deleteBook();
void searchBook();
void modifyBook();

void CreateBooks(bool Mode);//Mode=true时，输出调试信息
void SaveBooks(bool);
#endif
