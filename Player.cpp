#include "Player.hpp"

//Return name of player
std::string Player::getName() const{
    return name_;
}

//Return reference of Player's inventory
Inventory& Player::getInventoryRef(){
    return inventory_;
}

//Copy Constructor
Player::Player(const Player& rhs)
: inventory_(rhs.inventory_), name_(rhs.name_){}

//Move Constructor
Player::Player(Player&& rhs)
: inventory_(std::move(rhs.inventory_)), name_(std::move(rhs.name_)){}

//Copy Assignment operator
Player& Player::operator=(const Player& rhs){
    if(this != &rhs){
        name_ = rhs.name_;
        inventory_ = rhs.inventory_;
    }
    return *this;
}

//Move Assignment Operator
Player& Player::operator=(Player&& rhs){
    if(this != &rhs){
        name_ = std::move(rhs.name_);
        inventory_ = std::move(rhs.inventory_);
    }
    return *this;
}
