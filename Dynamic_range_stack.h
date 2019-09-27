/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

class Dynamic_range_stack {
private:
    int entry_count;
    int max_count;
    int min_count;
    int initial_capacity;
    int current_capacity;
    
    int *stack_array;
    int *maximum_array;
    int *minimum_array;
    
    // You may wish to include a number of helper functions
    // in order to abstract out some operations
    
    
public:
    Dynamic_range_stack( int = 10 );
    ~Dynamic_range_stack();
    
    int top() const;
    int size() const;
    bool empty() const;
    int capacity() const;
    
    int maximum() const;
    int minimum() const;
    
    
    void push( int const & );
    int pop();
    void clear();
    
    
    // Friends
    
    friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

Dynamic_range_stack::Dynamic_range_stack( int n ):
entry_count( 0 ),
min_count( 0 ),
max_count( 0 ),
initial_capacity( std::max( 1, n ) ),
current_capacity( initial_capacity ),
stack_array( new int[current_capacity] ),
maximum_array( new int[current_capacity] ),
minimum_array( new int[current_capacity] ) {
    // empty constructor
}

Dynamic_range_stack::~Dynamic_range_stack() {
    // Enter your implementation here.
    delete[] stack_array;
    delete[] minimum_array;
    delete[] maximum_array;
}

int Dynamic_range_stack::top() const {
    // Enter your implementation here.
    if (entry_count==0)
        throw underflow();
    else
        return stack_array[entry_count-1];
}

int Dynamic_range_stack::maximum() const {
    // Enter your implementation here.
    if (entry_count==0)
        throw underflow();
    else
        return maximum_array[entry_count-1];
}

int Dynamic_range_stack::minimum() const {
    // Enter your implementation here.
    if (entry_count==0)
        throw underflow();
    else
        return minimum_array[entry_count-1];
}

int Dynamic_range_stack::size() const {
    // Enter your implementation here.
    return entry_count;
}

bool Dynamic_range_stack::empty() const {
    // Enter your implementation here.
    if (entry_count!=0)
        return false;
    else
        return true;
}

int Dynamic_range_stack::capacity() const {
    // Enter your implementation here.
    return current_capacity;
}



void Dynamic_range_stack::push( int const &obj ) {
    // Enter your implementation here.
    if (current_capacity==entry_count) {
        int nin_capacity=2*entry_count;
        int *stack_array2=new int[nin_capacity];
        int *maximum_array2=new int[nin_capacity];
        int *minimum_array2=new int[nin_capacity];
        for (int i=0; i<entry_count; i+=1) {
            stack_array2[i]=stack_array[i];
            maximum_array2[i]=maximum_array[i];
            minimum_array2[i]=minimum_array[i];
        }
        stack_array2[entry_count]=obj;
        maximum_array2[entry_count]=(maximum_array2[entry_count-1]>obj)?maximum_array2[entry_count-1]:obj;
        minimum_array2[entry_count]=(minimum_array2[entry_count-1]<obj)?minimum_array2[entry_count-1]:obj;
        delete[] stack_array;
        delete[] minimum_array;
        delete[] maximum_array;
        stack_array=stack_array2;
        maximum_array=maximum_array2;
        minimum_array=minimum_array2;
        current_capacity= nin_capacity;
    } else {
        stack_array[entry_count]=obj;
        if (entry_count==0) {
            maximum_array[entry_count]=obj;
            minimum_array[entry_count]=obj;
        } else {
            maximum_array[entry_count]=(maximum_array[entry_count-1]>obj)?maximum_array[entry_count-1]:obj;
            minimum_array[entry_count]=(minimum_array[entry_count-1]<obj)?minimum_array[entry_count-1]:obj;
        }
    }
    entry_count+=1;
    //current_capacity=initial_capacity-entry_count;
    min_count+=1;
    max_count+=1;
    return;
}

int Dynamic_range_stack::pop() {
    // Enter your implementation here.
    if (entry_count==0) {
        throw underflow();
    } else {
        int top=stack_array[entry_count-1];
        entry_count-=1;
        //current_capacity=initial_capacity-entry_count;
        min_count-=1;
        max_count-=1;
        return top;
    }
}

void Dynamic_range_stack::clear() {
    // Enter your implementation here.
    //current capacity!=initial
    //
    if (current_capacity!=initial_capacity) {
        delete[] stack_array;
        delete [] minimum_array;
        delete [] maximum_array;
        stack_array=new int[initial_capacity];
        maximum_array=new int[initial_capacity];
        minimum_array=new int[initial_capacity];
        current_capacity=initial_capacity;
    }
    entry_count=0;
    current_capacity=initial_capacity-entry_count;
    min_count=0;
    max_count=0;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {
    // Print out your stacks
    
    return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
