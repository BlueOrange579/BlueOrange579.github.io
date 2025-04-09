// InvInq.cpp
// Luis Lopez, CIP 400
// 2/27/19
#include <iostream>
#include <string>

using namespace std;

// Specification B1 - OOP
class Item{
  private:
    string* name = nullptr;
    int* quantity = nullptr;
    double* cost = nullptr;
  public:
    void set_values();
    void add_inv();
    int menu();
    void menu_choice(int);
    void display_inv();
    //void creat_array();
};
// Global variable
int size = 0;
// Prototype Functions
void add_inv();
int menu();
void menu_choice(int);
void display_inv();

int main(){
  bool again = true;
  Item item;
  //item.creat_array();
  item.set_values();
  cout << "Welcome to the Inventory Inquisiter!" << endl;
  cout << "Choose an option to get started." << endl;
  while(again){
    int choice = item.menu();
    item.menu_choice(choice);
    if (choice == 3){
      cout << "Quitting..." << endl;
      again = false;
    }
  }
}
// Set values to manipulate for arrays
// Specification C1 - Dynamic Array
void Item::set_values(){
  name = new string[size];
  quantity= new int[size];
  cost = new double[size];
}
// Specification C4 - Main Menu
int Item::menu(){
  int choice;
  cout << endl << endl;
  cout << "******************************************" << endl;
  cout << "1. Add Inventory\n2. Display Inventory\n3. Quit Program" << endl;
  cout << "******************************************" <<  endl;
  cout << "What would you like to do? ";
  cin >> choice;
  // Secification C5 - Validate Menu
  while(choice < 1 && choice > 3){
    cout << "Invalid choice. Please enter the number of the action you want to do." << endl;
    cout << " Enter choice: ";
    cin >> choice;
  }
  return choice;
}

void Item::menu_choice(int x){
  if(x == 1){
    add_inv();
  }
  else
    display_inv();
  }
// Specification C2 - Add Option
void Item::add_inv(){
  ++size;
  int* temp_quantity = new int[size];
  string* temp_name = new string[size];
  double* temp_cost = new double[size];
  for(int i = 0; i < size; ++i){
    temp_cost[i] = cost[i];
    temp_name[i] = name[i];
    temp_quantity[i] = quantity[i];
  }
  delete [] cost;
  cost = temp_cost;
  delete [] temp_cost;
  temp_cost = nullptr;
  delete [] name;
  name = temp_name;
  delete [] temp_name;
  temp_name = nullptr;
  delete [] quantity;
  quantity = temp_quantity;
  delete [] temp_quantity;
  temp_quantity = nullptr;

  for(int i = size - 1; i < size; ++i){
    cout << "Item name: ";
    cin >> name[i];
    cout << "Item cost: ";
    cin >> cost[i];
    cout << "Item quantity: ";
    cin >> quantity[i];
  }
}

// Specification C3 - Display Option
void Item::display_inv(){
  for(int i = 0; i < size; ++i){
    cout << "Item in Inventory: " << endl;
    cout << "#\t" << "Name\t" << "Cost\t" << "Quantity\t" << endl;
    cout << i + 1 << ". \t" << name[i] << "\t  " << cost[i] << "\t  " << quantity[i]  << endl;
  }
}
