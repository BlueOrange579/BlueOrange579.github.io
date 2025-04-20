# Data Structure Enhancement

The artifact that was used for this enhancement is a inventory management console application where one can add and delete items stored in a dynamic array, as well as display all the items on the screen. This is a project that I completed for my Object Oriented Programming with C++ class in 2019.

The reason that this particular artifact was chosen was because it would be good to showcase my skill in using different data structures. In this artifact I used a dynamic array to save the items and interact with them, which is not as efficient as using other methods, which is why using a different data structure would be a good would be a good demonstration of my skills in that field. To enhance the artifact I used a map that has the key as a string, and the value is a structure that contains the price and quantity of the item. With the enhancements that I conducted to the artifact I met the course outcomes that I had planned to meet in module one. 
During the process of enhancing the artifact I learned a lot more about working with maps and the different functions that help you work with maps. I also learned more about structures and and how to used them as values for a map. A challenge that I faced was finding a good way to iterate through the map, and accessing the different values of the structure in the map. After doing so research I used a range based iteration and was able to successfully access all the data in the map and structure.

## Technology Used
- Git
- C++
- Raylib
- Raygui

## [Original Artifact](https://github.com/BlueOrange579/BlueOrange579.github.io/blob/main/OriginalArtifact/InvInq.cpp)

```
// Specification C1 - Dynamic Array
void Item::set_values(){
  name = new string[size];
  quantity= new int[size];
  cost = new double[size];
}
```

## [Enhanced Artifact](https://github.com/BlueOrange579/BlueOrange579.github.io/tree/main/DataStructures_Algorithms)

```
// Struct to contain the item qty and price
struct Items{
    double price;
    int qty;
};

/// Map to save all the items
std::map<std::string, Items> myItems = {};
```