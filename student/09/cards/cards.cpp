#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards(): top_(nullptr) {
}

Card_data *Cards::get_topmost() {
    return top_;
}

void Cards::add(int id) {

    if (is_empty()) {
        top_ = new Card_data{id, nullptr};
    } else {
        Card_data* old_card = top_;
        top_ = new Card_data{id, old_card};
    }

}

void Cards::print_from_top_to_bottom(std::ostream &s) {

    if (is_empty()) {
        return;
    }

    Card_data* card_to_print = top_;
    int running_number = 1;

    while (card_to_print != nullptr) {
        s << running_number << ": " << card_to_print->data << std::endl;
        card_to_print = card_to_print->next;
        running_number++;
    }

}

bool Cards::remove(int &id) {

    if (is_empty()) {
        return false;
    }

    Card_data* card_to_remove = top_;
    id = card_to_remove->data;

    if (card_to_remove->next == nullptr) {
        delete card_to_remove;
        top_ = nullptr;
    } else {
        top_ = card_to_remove->next;
        delete card_to_remove;
    }

    return true;

}

bool Cards::bottom_to_top() {

    if (is_empty()) {
        return false;
    }

    if (top_->next == nullptr) {
        return true;
    }

    Card_data* bottom_card = top_;
    Card_data* new_bottom = nullptr;

    while(bottom_card->next != nullptr) {
        new_bottom = bottom_card;
        bottom_card = bottom_card->next;
    }

    bottom_card->next = top_;
    top_ = bottom_card;
    new_bottom->next = nullptr;

    return true;

}

bool Cards::top_to_bottom() {

    if (is_empty()) {
        return false;
    }

    if (top_->next == nullptr) {
        return true;
    }

    Card_data* bottom_card = top_;

    while(bottom_card->next != nullptr) {
        bottom_card = bottom_card->next;
    }

    Card_data* old_top = top_;
    top_ = top_->next;
    bottom_card->next = old_top;
    old_top->next = nullptr;

    return true;

}

void Cards::print_from_bottom_to_top(std::ostream &s)
{

}

Cards::~Cards() {
    while (top_ != nullptr ) {
       Card_data* item_to_be_released = top_;
       top_ = top_->next;

       delete item_to_be_released;
    }
}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{

}

bool Cards::is_empty() {
    return top_ == nullptr;
}
