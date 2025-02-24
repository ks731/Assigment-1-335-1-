#include "Inventory.hpp"

//Constructor
Inventory::Inventory(
    const std::vector<std::vector<Item>>& items, Item* equipped
): inventory_grid_(items), equipped_(equipped), weight_(0.0), item_count_(0){
    for(const auto &it : inventory_grid_){
        for(const auto &item : it){
            if(item.type_ != NONE){
                weight_ += item.weight_;
                item_count_++;
            }
        }
    }
}


//Retrieve equipped_
Item* Inventory::getEquipped() const{
    return equipped_;
}


//Updates `equipped` to the specified item 
void Inventory::equip(Item* itemToEquip){
    equipped_ = itemToEquip;
}


//Discard Equipped Item
void Inventory::discardEquipped(){
    delete equipped_;
    if(equipped_ != nullptr){
        equipped_ = nullptr;
    }
}

//Retrieve inventory grid
std::vector<std::vector<Item>> Inventory::getItems() const{
    return inventory_grid_;
}

//Return weight
float Inventory::getWeight() const{
    return weight_;
}

//Retrieve Item count
size_t Inventory::getCount() const{
    return item_count_;
}

// Retrieves the item located at the specified row and column in the inventory grid.
Item Inventory::at(const size_t& row, const size_t& col) const{
    if(row >= inventory_grid_.size()){
        throw std::out_of_range("row is out of bounds");
    }

    if(col >= inventory_grid_[row].size()){
        throw std::out_of_range("column is out of bounds");
    }

    return inventory_grid_[row][col];
}


        /**
         * @brief Stores an item at the specified row and column in the inventory grid.
         *
         * @param row A size_t parameter for the row index in the inventory grid.
         * @param col  A size_t parameter for the column index in the inventory grid.
         * @param pickup A const ref. to the item to store at the specified location.
         * @return True if the item was successfully stored, false if the cell is already occupied.
         * 
         * @post Updates `item_count_` and `weight_` if the Item is sucessfully added
         * @throws std::out_of_range If the row or column is out of bounds.
         */
bool Inventory::store(const size_t& row, const size_t& col, const Item& pickup){
    if(row >= inventory_grid_.size()){
        throw std::out_of_range("row out of bounds");
    }

    if(col >= inventory_grid_[row].size()){
        throw std::out_of_range("column out of bounds");
    }

    //check if cell is occupied
    if(inventory_grid_[row][col].type_ != NONE){
        return false;
    }

    inventory_grid_[row][col] = pickup;

    item_count_++;
    weight_ += pickup.weight_;
    return true;
}

//Big Five

//Copy Constructor
Inventory::Inventory(const Inventory& rhs)
: inventory_grid_(rhs.inventory_grid_), weight_(rhs.weight_), item_count_(rhs.item_count_){
    if(rhs.equipped_ != nullptr){
        equipped_ = new Item(*rhs.equipped_);
    }else{
        equipped_ = nullptr;
    }
}

//Move constructor
Inventory::Inventory(Inventory&& rhs) : inventory_grid_(std::move(rhs.inventory_grid_)), equipped_(rhs.equipped_), weight_(rhs.weight_), item_count_(rhs.item_count_){
    rhs.equipped_ = nullptr;
    rhs.weight_ = 0;
    rhs.item_count_ = 0;
    rhs.inventory_grid_.clear();

}

//Copy Assignment Operator
Inventory& Inventory::operator=(const Inventory& rhs){
    if(this != &rhs){
        inventory_grid_ = rhs.inventory_grid_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
        delete equipped_;
        if(rhs.equipped_){
            equipped_ = new Item(*rhs.equipped_);
        }else{
            equipped_ = nullptr;
        }
    }
    return *this;
}

//Move Assignment Operator
Inventory& Inventory::operator=(Inventory&& rhs){
    if(this != &rhs){
        inventory_grid_ = std::move(rhs.inventory_grid_);
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
        equipped_ = rhs.equipped_;

        rhs.inventory_grid_.clear();
        rhs.weight_ = 0;
        rhs.item_count_ = 0;
        rhs.equipped_ = nullptr;
        }
        return *this;
}

//Destructor
Inventory::~Inventory(){
    delete equipped_;
}


