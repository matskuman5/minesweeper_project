#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id) {

//    if (is_empty()) {
//        return false;
//    }

//    Card_data* card_to_remove = top_;
//    id = card_to_remove->data;

//    if (card_to_remove->next == nullptr) {
//        delete card_to_remove;
//        top_ = nullptr;
//    } else {
//        top_ = card_to_remove->next;
//        delete card_to_remove;
//    }

//    return true;



    if (top_ == nullptr) {
        return false;
    }

    id = top_->data;

    top_ = top_->next;

    return true;

}

void Cards::reverse() {

    std::shared_ptr<Card_data> current_card = top_;
    std::shared_ptr<Card_data> next_card = top_;
    std::shared_ptr<Card_data> last_card = nullptr;

    while(current_card != nullptr) {
        next_card = current_card->next;
        current_card->next = last_card;
        last_card = current_card;
        current_card = next_card;
    }

    top_= last_card;



}

// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp
