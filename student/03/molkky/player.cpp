#include "player.hh"

#include <string>
#include <iostream>

Player::Player(std::string name):
name_(name)
{
    points_ = 0;
}

std::string Player::get_name()
{
    return name_;
}

int Player::get_points()
{
    return points_;
}

bool Player::has_won()
{
    if(points_ == 50) {
        return true;
    }
    return false;
}

void Player::add_points(int i)
{
    if (points_ + i > 50) {
        std::cout << get_name() << " gets penalty points!" << std::endl;
        points_ = 25;
    } else {
        points_ += i;
    }
}
