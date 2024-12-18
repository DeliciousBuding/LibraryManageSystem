
#ifndef READERMANAGER_H
#define READERMANAGER_H
#include <bits/stdc++.h>
using namespace std;
class ReaderManager
{
public:
    void ReaderManagerMenu();
    void addReader();
    void deleteReader();
    void searchReader();
    void modifyReader();
    void showID(string &id);
    void getID(string &name);
    void deleteID(string id);

    void modifyUsername(string target);
    void modifyPassword(string target);
    void modifyType(string target);
    void modifyPassWordToDefault(string target);
};

#endif
