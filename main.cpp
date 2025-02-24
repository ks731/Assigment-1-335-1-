#include "Inventory.hpp"
#include "Player.hpp"
#include <vector>

int main(){
    //Items
    Item* sword = new Item("Sword", 7.5, WEAPON);   //Item pointer 
    Item chestplate("Chestplate", 8.5, ARMOR);
    Item water("Water", 1.5, ACCESSORY);
    Item canon("Canon", 200.7, WEAPON);
    Item shoes("Shoes", 4.2, ACCESSORY);
    Item helmet("Helmet", 6.9, ARMOR);

    //Inventories
    // test Constructor
    Inventory one;
    Inventory two; 
    Inventory *three = nullptr;

    //test destructor
    delete three;

    //test store()
    two.store(0,0,shoes);
    two.store(1,0,chestplate);
    two.store(2,0,water);

    //test equip
    two.equip(sword);
    //test accessors
    std::cout << "Inventory two has equipped: " << two.getEquipped()->name_ << "\n";
    two.discardEquipped();
    std::cout << "Inventory two's weight: " << two.getWeight() << "\n";
    std::cout << "Inventory two's item count: " << two.getCount() << "\n";
    std::cout << "All of inventory two's items: " << "\n";
    std::vector<std::vector<Item>> retrieved_items = two.getItems();
    for (size_t i = 0; i < retrieved_items.size(); ++i) {
        for (size_t j = 0; j < retrieved_items[i].size(); ++j) {
            std::cout << retrieved_items[i][j].name_;
        }
        std::cout << std::endl;
    }

    //test move constructor
    Inventory four(std::move(two));





    return 0;
}