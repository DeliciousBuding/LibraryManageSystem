#ifndef BOOK_H
#define BOOK_H

#include <string>

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
class Book
{
private:
    string name;
    string bookCode;
    string author;
    string publisher;
    string language;
    int id;
    int edition;
    int publicationYear;
    int publicationMonth;
    string introduction;
    int borrowTimes;
    int total;
    int current;
    double price;
    string originalName;
    string originalAuthor;

public:
    Book(string code);
    Book();
    void show();

    // getter and setter
    string getName() { return name; }
    void setName(string name) { this->name = name; }
    string getBookCode() { return bookCode; }
    void setBookCode(string bookCode) { this->bookCode = bookCode; }
    string getAuthor() { return author; }
    void setAuthor(string author) { this->author = author; }
    string getPublisher() { return publisher; }
    void setPublisher(string publisher) { this->publisher = publisher; }
    string getLanguage() { return language; }
    void setLanguage(string language) { this->language = language; }
    int getEdition() { return edition; }
    void setEdition(int edition) { this->edition = edition; }
    int getPublicationYear() { return publicationYear; }
    void setPublicationYear(int publicationYear) { this->publicationYear = publicationYear; }
    int getPublicationMonth() { return publicationMonth; }
    void setPublicationMonth(int publicationMonth) { this->publicationMonth = publicationMonth; }
    string getIntroduction() { return introduction; }
    void setIntroduction(string introduction) { this->introduction = introduction; }
    int getBorrowTimes() { return borrowTimes; }
    void setBorrowTimes(int borrowTimes) { this->borrowTimes = borrowTimes; }
    int getTotal() { return total; }
    void setTotal(int total) { this->total = total; }
    int getCurrent() { return current; }
    void setCurrent(int current) { this->current = current; }
    double getPrice() { return price; }
    void setPrice(double price) { this->price = price; }
    string getOriginalName() { return originalName; }
    void setOriginalName(string originalName) { this->originalName = originalName; }
    string getOriginalAuthor() { return originalAuthor; }
    void setOriginalAuthor(string originalAuthor) { this->originalAuthor = originalAuthor; }
    int getId() { return id; }
    void setId(int id) { this->id = id; }
};

#endif