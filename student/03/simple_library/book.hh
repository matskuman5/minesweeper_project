#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include <date.hh>

class Book
{
public:
    Book(std::string const author, std::string const name);

    void print();

    void loan(Date);
    void renew();
    void give_back();

private:

    std::string author_;
    std::string name_;
    Date loaned_;
    Date due_;
    bool available_;

};

#endif // BOOK_HH
