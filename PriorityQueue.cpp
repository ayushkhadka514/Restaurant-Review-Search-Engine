#include "PriorityQueue.hpp"
#include <limits.h>

using namespace std;

void swap(ReviewInfo *a, ReviewInfo *b)
{
    ReviewInfo temp = *a; 
    *a = *b;
    *b = temp;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ(int cap)
{
    currentSize = 0;
    capacity = cap;
    heapArr = new ReviewInfo[cap];
}

/*
Destructor
*/
PriorityQ::~PriorityQ()
{
    delete [] heapArr;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
    int p = (index - 1)/2;
    return p;
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
    int l = (index * 2) + 1;
    return l;
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
    int r = (index * 2) + 2;
    return r;
}

void PriorityQ::peek()
{
    if(currentSize == 0){
        cout << "no record found" << endl;
        return;
    }
    cout << "Restaurant: "<< heapArr[0].restaurantName << endl;
    cout << "Customer:" << heapArr[0].customer << endl;
    cout << "Review:" << heapArr[0].review << endl;
    cout << "Time:" << heapArr[0].time << endl;
}

void PriorityQ::heapify(int i)
{
    int l = leftChild(i);
    int r = rightChild(i);
    int largest = i;

    if(l < currentSize && (heapArr[largest].time < heapArr[l].time)){
        largest = l;
    }
    if(r < currentSize && (heapArr[largest].time < heapArr[r].time)){
        largest = r;
    }

    if(largest != i){
        swap(&heapArr[i],&heapArr[largest]);
        heapify(largest);
    }
}

void PriorityQ::insertElement(ReviewInfo restaurant)
{
    if(currentSize == capacity){
        cout << "Maximum heap size reached. Cannot insert anymore." <<endl;
        return;
    }
    heapArr[currentSize] = restaurant;
    heapify(currentSize);
    currentSize++;
    int index = currentSize - 1;

    while(index!=0 && heapArr[index].time > heapArr[parent(index)].time){
        swap(&heapArr[index], &heapArr[parent(index)]);
        index = parent(index);
    }
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
    if(currentSize == 0){
        cout << "No reviews!" << endl;
        return;
    }
    for(int i = 0; i < currentSize; i++){
        cout << "\t" << "Customer: " << heapArr[i].customer << endl;
        cout << "\t" << "Review: " << heapArr[i].review << endl;
        cout << "\t" << "Time: " << heapArr[i].time << endl;
        cout << "\t" << "=====" << endl;
    }
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
    if(currentSize == 0){
        return;
    }
    if(currentSize == 1){
        currentSize--;
        return;
    }
    heapArr[0] = heapArr[currentSize - 1];
    currentSize--;
    heapify(0);

}
