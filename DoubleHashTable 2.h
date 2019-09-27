#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
    private:
    int count;
    int power;
    int array_size;
    T *array;
    state *array_state;
    
    int h1( T const & ) const; // first hash function
    int h2( T const & ) const; // second hash function
    
    public:
    DoubleHashTable( int = 5 );
    ~DoubleHashTable();
    int size() const;
    int capacity() const;
    bool empty() const;
    bool member( T const & ) const;
    T bin( int ) const;
    
    void print() const;
    
    void insert( T const & );
    bool remove( T const & );
    void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {
    
    for ( int i = 0; i < array_size; ++i ) {
        array_state[i] = EMPTY;
    }
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
    // enter your implemetation here
    delete[] array;
    delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
    // enter your implemetation here
    return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    // enter your implemetation here
    return array_size;
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
    // enter your implemetation here
    if (count!=0)
        return false;
    else
        return true;
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
    // enter your implemetation here
    int obj1= static_cast<int>(obj);
    int k=0;
    if (obj1<0) {
        k=obj1%array_size+array_size;
    }
    else{
        k= obj1% array_size;
    }
    return k;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
    // enter your implemetation here
    int obj1= static_cast<int>(obj);
    int k1=0;
    if (obj1<0) {
        k1=obj1%array_size+array_size;
    } else {
        k1=obj1/array_size;
    }
    int k2=k1%array_size;
    return k2;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
    // enter your implemetation hereßß
    int probe=h1(obj);
    int offset=h2(obj);
    if (array_state[probe]==EMPTY) return false;
    if (array[probe]==obj) {
        if (array_state[probe]==OCCUPIED) {
            return true;
        }
    }else{
        while (array[probe]!=obj) {
            if (offset%2==0) {
                offset++;
            }
            probe=(probe+offset)%array_size;
        }
        if (array_state[probe]==OCCUPIED)
            return true;
    }
    return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    // enter your implemetation here
    return array[n];
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
    // enter your implemetation here
    if (count==array_size) {
        throw overflow();
        return;
    }
    count+=1;
    int probe=h1(obj);
    int offset=h2(obj);
    if (array_state[probe]!=OCCUPIED) {
        array[probe]=obj;
        array_state[probe]=OCCUPIED;
    } else {
        while (array_state[probe]==OCCUPIED) {
            if (offset%2==0) {
                offset++;
            }
            probe=(probe+offset)%array_size;
        }
        array[probe]=obj;
        array_state[probe]=OCCUPIED;
    }
    return ;
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
    // enter your implemetation here
    if (count==0 || member(obj)==false) return false;
    count-=1;
    int probe=h1(obj);
    int offset=h2(obj);
    if (array[probe]==obj) {
        array_state[probe]=DELETED;
        return true;
    } else {
        while (array[probe]!=obj) {
            if (offset%2==0)
                offset++;
            probe=(probe+offset)%array_size;
        }
        array_state[probe]=DELETED;
        return true;
    }
    return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
    // enter your implemetation here
    count=0;
    delete[] array;
    delete[] array_state;
    //array=new *array;
    //array_state=new T*array_state;
    return ;
}

//Print function won't be tested
template<typename T >
void DoubleHashTable<T >::print() const {
    // enter your implemetation here
    return;
}

#endif
