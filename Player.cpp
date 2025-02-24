#include "Player.hpp"

//Player Constructor
Player::Player(const std::string& name, const Inventory& inventory) : name_(name), inventory_(inventory){}

//Get name of player
std::string Player::getName() const{
    return name_;
}

//Get inventory reference
Inventory& Player::getInventoryRef(){
    return inventory_;
}

//Copy constructor
Player::Player(const Player& rhs): name_(rhs.name_), inventory_(rhs.inventory_){}

//Move Constructor
Player::Player(Player&& rhs) : name_(std::move(rhs.name_)), inventory_(std::move(rhs.inventory_)){}

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

int main(){
    //Items
    Item sword("Sword", 7.5, WEAPON);
    Item chestplate("Chestplate", 8.5, ARMOR);
    Item water("Water", 1.5, ACCESSORY);
    Item canon("Canon", 200.7, WEAPON);
    Item shoes("Shoes", 4.2, ACCESSORY);
    Item helmet("Helmet", 6.9, ARMOR);

    //Inventories
    // test Constructor
    Inventory one;
    Inventory two;
    Inventory three;

    //test store()
    two.store(0,0,sword);
    two.store(0,1,chestplate);
    two.store(1,0,water);

    //test equip
    two.equip(&sword);
    //test accessors
    std::cout << "Inventory two has equipped: " << two.getEquipped()->name_ << "\n";
    std::cout << "Inventory two's weight: " << two.getWeight() << "\n";
    std::cout << "Inventory two's item count: " << two.getCount() << "\n";
    std::cout << "All of inventory two's items: " << "\n";
    std::vector<std::vector<Item>> retrieved_items = two.getItems();
    for (size_t i = 0; i < retrieved_items.size(); ++i) {
        for (size_t j = 0; j < retrieved_items[i].size(); ++j) {
            std::cout << retrieved_items[i][j].name_ << " ";
        }
        std::cout << std::endl;
    }



    return 0;
}