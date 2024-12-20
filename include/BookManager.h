
#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H
#include <bits/stdc++.h>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

class BookManager
{
public:
    void bookManagerMenu();
    void addBook();
    void deleteBook();
    void searchBook();
    void modifyBook();
};

#endif
