#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle): cycle_(cycle) {

}

Queue::~Queue() {

    while (first_ != nullptr) {
        Vehicle* to_be_released = first_;
        first_= first_->next;

        delete to_be_released;
    }

}

// If the color of traffic light is red, inserts a vehicle, the register
// number of which is reg, to the queue.
void Queue::enqueue(const string &reg) {

    if (is_green_) {
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" << std::endl;
        return;
    }

    if (is_empty()) {
        first_ = new Vehicle{reg, nullptr};
        last_ = first_;
    } else {
        Vehicle* v = new Vehicle{reg, nullptr};
        last_->next = v;
        last_ = v;
    }

}

// Switches the color of traffic light from green to red or vice versa.
// If the new color is green, lets at least <cycle_> vehicles
// go on (i.e. calls dequeue at least <cycle_> times), and finally
// resets the color to red again.
void Queue::switch_light() {

    if (is_empty()) {
        if (!is_green_) {
            is_green_ = true;
            std::cout << "GREEN: ";
        } else {
            is_green_ = false;
            std::cout << "RED: ";
        }
        std::cout << "No vehicles waiting in traffic lights" << std::endl;
    } else {
        std::cout << "GREEN: Vehicle(s) ";
        for (unsigned int i = 0; i < cycle_; i++) {
            dequeue();
        }
        std::cout << "can go on" << std::endl;

    }

}

void Queue::reset_cycle(unsigned int cycle) {

    cycle_ = cycle;

}

void Queue::print() const {

    if (is_green_) {
        std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
        return;
    }

    std::cout << "RED: ";

    if (is_empty()) {
        std::cout << "No vehicles waiting in traffic lights" << std::endl;
    } else {
        std::cout << "Vehicle(s) ";
        Vehicle* v = first_;
        while(v != nullptr) {
            std::cout << v->reg_num << " ";
            v = v->next;
        }
        std::cout << "waiting in traffic lights" << std::endl;
    }

}

bool Queue::is_empty() const {

    return first_ == nullptr && last_ == nullptr;

}

void Queue::dequeue() {

    if (is_empty()) {
        return;
    }

    Vehicle* to_go = first_;
    first_ = to_go->next;
    if (first_ == nullptr) {
        last_ = nullptr;
    }

    std::cout << to_go->reg_num << " ";

    delete to_go;

}

