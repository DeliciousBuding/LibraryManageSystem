#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#include "LibrarySystem.h"
#include "BookSystem.h"
#include "UserSystem.h"
#include "User.h"
using namespace std;



void AdminMenu(User *NowUser);
void ReaderMenu(User *NowUser);

void Login();
void Register();

#endif // LIBRARYSYSTEM_H
