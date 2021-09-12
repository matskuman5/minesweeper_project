#include "book.hh"
#include <string>
#include <iostream>

Book::Book(std::string author, std::string name):
author_(author), name_(name)
{
    available_ = true;
}

void Book::print()
{
    std::cout << author_ << " : " << name_ << std::endl;
    if(available_) {
        std::cout << "- available" << std::endl;
    } else {
        std::cout << "- loaned: ";
        loaned_.print();
        std::cout << "- to be returned: ";
        due_.print();
    }
}

void Book::loan(Date d)
{
    if(available_) {
        loaned_ = d;
        d.advance(28);
        due_ = d;
        available_ = false;
    } else {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    }
}

void Book::renew()
{
    if(!available_) {
        due_.advance(28);
    } else {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    }
}

void Book::give_back()
{
    available_ = true;
}
