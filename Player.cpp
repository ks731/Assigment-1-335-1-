#include "Player.hpp"

//Player Constructor
Player::Player(const std::string& name, const Inventory& inventory) : inventory_(inventory),  name_(name){}

//Get name of player
std::string Player::getName() const{
    return name_;
}

//Get inventory reference
Inventory& Player::getInventoryRef(){
    return inventory_;
}

//Copy constructor
Player::Player(const Player& rhs):  inventory_(rhs.inventory_), name_(rhs.name_){}

//Move Constructor
Player::Player(Player&& rhs) :  inventory_(std::move(rhs.inventory_)), name_(std::move(rhs.name_)){}

//Copy Assignment Operator
Player& Player::operator=(const Player& rhs){
    if(this != &rhs){
        inventory_ = rhs.inventory_;
        name_ = rhs.name_;
    }
    return *this;
}

//Move Assignment Operator
Player& Player::operator=(Player&& rhs){
    if(this != &rhs){
        inventory_ = std::move(rhs.inventory_);
        name_ = std::move(rhs.name_);
    }
    return *this;
}
