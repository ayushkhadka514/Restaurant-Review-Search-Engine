// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>

using namespace std;

node* HashTable::createNode(string restaurantName, node* next)
{
    node *newNode = new node{restaurantName, PriorityQ(50), next}; 

    return newNode;
}

HashTable::HashTable(int bsize)
{
    tableSize = bsize;
    numCollision = 0;
    table = new node*[tableSize];
    for(int i = 0; i < tableSize; i++){
        table[i] = nullptr; // set all pointers to null
    }
}

HashTable::~HashTable()
{
    for (int i = 0; i < tableSize; i++) {
        node* current = table[i]; // go to each head pointer starting from [0]
        while (current != nullptr) { // traverse until the end of the list
            node* toDelete = current;  
            current = current->next; // set current to a new "head" because head is being deleted
            delete toDelete;
        }
    }
    delete[] table; // delete allocated heap memory
}

void HashTable::displayTable()
{
    cout << "---------------------" << endl;
    for(int i = 0; i < tableSize; i++){
        cout << i << " |";
        if(table[i] == nullptr){
            cout << "NULL" << endl; // empty "bucket"
        }
        else{
            node *temp = table[i];
            while(temp != nullptr){
                cout << temp->restaurantName << "-->";
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }
    }
    cout << "---------------------" << endl;
}

unsigned int HashTable::hashFunction(string restaurantName)
{
    int len = restaurantName.length();
    int ascii = 0;
    for(int i = 0; i < len; i++){
        ascii += restaurantName[i]; //adds each character of the restraunt name
    }
    return ascii%tableSize; // returns a key 0-4
}

node* HashTable::searchItem(string restaurantName)
{
    int key = hashFunction(restaurantName);
    node *temp = table[key]; // sets temp to head pointer of the bucket
    while(temp != nullptr){ // if bucket is not empty 
        if(temp->restaurantName == restaurantName){ // traverses the LL to find the restraunt name
            return temp;
        }
        temp = temp->next; // will keep traverseing the bucket until NULL
    } // if bucket is empty, skips entire while loop and returns NULL
    return nullptr;
}

void HashTable::insertItem(ReviewInfo restaurant)
{
    node *temp = searchItem(restaurant.restaurantName);
    int key = hashFunction(restaurant.restaurantName);
    if(temp == nullptr){ // if restraunt is not in table
        if(table[key] != nullptr){ //if "bucket" is occupied by other restraunt
            numCollision++;
        }
        temp = createNode(restaurant.restaurantName, table[key]); // set the new node's next to the head
        table[key] = temp; //make new node the head
        temp->pq.insertElement(restaurant);
    }
    else{
        temp->pq.insertElement(restaurant);
    }
    
}


void HashTable::setup(string fname)
{
    ifstream file;
    string line, restaurant_name, review, customer, time;

    file.open(fname);

    if(!file.is_open()){
        cout << "Failed to open file!" << endl;
        return;
    }
    while(getline(file, line)){
        ReviewInfo temp;
        stringstream ss(line);

        getline(ss, restaurant_name, ';');
        temp.restaurantName = restaurant_name;

        getline(ss, review, ';');
        temp.review = review;

        getline(ss, customer, ';');
        temp.customer = customer;

        getline(ss, time, ';');
        temp.time = stoi(time);

        insertItem(temp);
    }
    file.close();
    
}