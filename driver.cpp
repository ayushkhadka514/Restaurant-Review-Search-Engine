#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// g++ driver.cpp hash.cpp PriorityQueue.cpp 
// ./a.out test.txt 5

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
        return -1;
    }
	
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    int ch = 0;
    string chs;
    HashTable ht(5);
    bool option1 = false; // ensures option 1 only is selected once
	
    while(ch!=8)
    {
        displayMenu();
        cout << "Enter your choice >>";
        getline(cin, chs);
        ch = stoi(chs);
        switch (ch)
        {
            case 1:
			{
                if(option1 == false){
                    option1 = true;
                    ht.setup(fname);
                    cout << "Data structure built successfully!" << endl;
                }
                else{
                    cout << "Already built the data structure!" << endl;
                }
				//
				break;
            }
            case 2:
			{
                ReviewInfo temp;
                string time;
                cout << "Enter the restaurant name:" << endl;
                getline(cin, temp.restaurantName);

                cout << "Enter the customer name:" << endl;
                getline(cin, temp.customer);

                cout << "Enter review:" << endl;
                getline(cin, temp.review);

                cout << "Enter the time:" << endl;
                getline(cin, time);
                temp.time = stoi(time);

                ht.insertItem(temp);
                cout << endl;

                cout << "Review added!" << endl;
                //
				break;
            }
            case 3:
			{
                string name;
                cout << "Enter restaurant name for most recent review" << endl;
                getline(cin, name);
                node *temp = ht.searchItem(name);
                if(temp == nullptr){
                    cout << "No record found!" << endl;
                }
                else{
                    temp->pq.peek();
                }

				break;
            }
            case 4:
			{
                string name;
                cout << "Enter restaurant name to pop most recent review" << endl;
                getline(cin, name);
                node *temp = ht.searchItem(name);
                if(temp == nullptr){
                    cout << "No record found!" << endl;
                }
                else{
                    temp->pq.pop();
                    cout << "Successfully popped!" << endl;
                }
                //
				break;
            }
            case 5:
			{
				string name;
                cout << "Enter restaurant name for most recent review" << endl;
                getline(cin, name);
                node *temp = ht.searchItem(name);
                if(temp == nullptr){
                    cout << "No record found!" << endl;
                }
                else{
                    temp->pq.print();
                }
				break;
			}
            case 6:
                //
                cout << "Number of collisions: " << ht.getNumCollision() << endl;
                break;
            case 7:
                //
                ht.displayTable();
                break;
            case 8:
                cout << "Exiting!" << endl;
                return 0;
            default:
                cout << "Enter a valid option." << endl;
                break;
        }
    }
}
