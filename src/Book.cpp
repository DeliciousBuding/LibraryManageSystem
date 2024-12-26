#include <book.h>
 
 //默认构造函数
Book::Book()
{
    name="";
    bookCode="";
    author="";
    publisher = "";
    language = "";
    edition=0;
    publicationYear=0;
    publicationMonth=0;
    introduction = "";
    borrowTimes=0;
    total=0;
    current=0;
    price=0.00;
    string originalName = "";
    string originalAuthor = "";
}