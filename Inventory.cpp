
#include "Inventory.hpp"
#include<vector>

//Copy Constructor
Inventory::Inventory(const Inventory& rhs)
: inventory_grid_(rhs.inventory_grid_), weight_(rhs.weight_), item_count_(rhs.item_count_){
    if(rhs.equipped_ != nullptr){
        equipped_ = new Item(*rhs.equipped_); //create new item and copy same data
    }else
    equipped_ = nullptr;   //set to nullptr if original item was nullptr
} 

//Copy Assignment Operator
Inventory& Inventory::operator=(const Inventory& rhs){
    if(this != &rhs){
        //deallocate equipped_ (item pointer)
        if(equipped_ != nullptr){
            delete equipped_;
        }
        inventory_grid_ = rhs.inventory_grid_;
        if(rhs.equipped_ != nullptr){
            equipped_ = new Item(*rhs.equipped_);
        }else{
            equipped_ = nullptr;
        }
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
    }
    return *this;
}

//Move Constructor
Inventory::Inventory(Inventory&& rhs) 
: inventory_grid_(std::move(rhs.inventory_grid_)), equipped_(rhs.equipped_) ,weight_(rhs.weight_), item_count_(rhs.item_count_){
    //set rhs to a valid but empty state
    rhs.inventory_grid_.clear(); //clear grid to 0
    rhs.equipped_ = nullptr;
    rhs.weight_ = 0;
    rhs.item_count_ = 0;
}

//Move Assignment Operator 
Inventory& Inventory::operator=(Inventory&& rhs){
    if(this != &rhs){
        delete equipped_;

        equipped_ = rhs.equipped_;
        inventory_grid_ = std::move(rhs.inventory_grid_);
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;

        rhs.equipped_ = nullptr;
        rhs.inventory_grid_.clear();
        rhs.weight_ = 0;
        rhs.item_count_ = 0;
    }
    return *this;
}

//Destructor
Inventory::~Inventory(){
    delete equipped_;
}

//Retrieves equipped
Item*  Inventory::getEquipped() const{
    return equipped_;
}

//Equips a new item
void Inventory::equip(Item* itemToEquip){
    equipped_ = itemToEquip;
}

//Discards currently equipped item
void Inventory::discardEquipped(){
    if(equipped_ != nullptr){
        delete equipped_;
        equipped_ = nullptr;
    }
}

//Retrieves inventory grid
std::vector<std::vector<Item>> Inventory::getItems() const{
    return inventory_grid_;
}

//Retrieves weight
float Inventory::getWeight() const{
    return weight_;
}

//Retrieves item count
size_t Inventory::getCount() const{
    return item_count_;
}

//Retrieves Item located at specific row and column in inventory grid
Item Inventory::at(const size_t& row, const size_t& col) const{
    if(row>= inventory_grid_.size() || col >= inventory_grid_[row].size()){
        throw std::out_of_range("Out of range");
    }
    return inventory_grid_[row][col];
}

//Stores an item at the specified row and column in the inventory grid.
bool Inventory::store(const size_t& row, const size_t& col, const Item& pickup){
    if(row >= inventory_grid_.size() || col >= inventory_grid_[row].size()){
        throw std::out_of_range("Out of range");
    }

    if(inventory_grid_[row][col] == Item()){
        inventory_grid_[row][col] = pickup;

        item_count_++;
        weight_ += pickup.weight_;
        return true;
    }

    return false;

}

int main(){
        //Default Constructor
    Inventory in1;
    std::cout << "Testing default constructor" << std::endl;

    //Parameterized Constructor
    Item sword("sword", 5.0, WEAPON);
    std::vector<std::vector<Item>> items(5,std::vector<Item>(5,sword));
    Inventory in2(items, new Item("chestplate", 8.0, ARMOR));
    std::cout << "Testing Parameterized Constructor" << std::endl;

    //Test copy constructor
    Inventory in3(in2);
    std::cout << "Testing copy constructor" << std::endl;

    //Testing Move Constructor
    Inventory in4(std::move(in2));
    std::cout << "Testing move constructor" << std::endl;

    //Test copy assignment operator
    in1 = in3;
    std::cout << "Testing copy assignment operator" << std::endl;

    //Test move assignment operator
    in1 = std::move(in4);
    std::cout << "Testing Move assignment operator" << std::endl;

    //Test getEquipped
    std::cout << (in3.getEquipped() ? in3.getEquipped()->name_ : "No Item equipped") << std::endl;

    //Test equip
    Item* gun = new Item("gun", 5.0, WEAPON);
    in3.equip(gun);
    std::cout << "inventory 3 now has a: " << in3.getEquipped()->name_ << std::endl;

    //Test discardEquipped
    in3.discardEquipped();
    std::cout << "Testing discard Equipped" << std::endl;

    //Test getWeight
    std::cout << "inventory 3 weight: " << in3.getWeight() << std::endl;
    
    //Test getCount
    std::cout << "inventory 3 item count: " << in3.getCount() << std::endl;

    //Test at
    Item firstItem = in3.at(0,0);
    std::cout << "First item in inventory 3: " << firstItem.name_ << std::endl;

    //Test store
    std::cout << "Testing store() " << std::endl;
    Item bomb("bomb",10.0, WEAPON );
    bool bombStored = in3.store(0,0,bomb);
    if(!bombStored){
        std::cout << "This should print if false (it is)" << std::endl;
    }
    bombStored = in3.store(1,1,bomb);
    if(bombStored){
        std::cout << "This should print if truw now (it is)" << std::endl;

    }

    std::cout << "If this only prints out something is wrong" << std::endl;


}