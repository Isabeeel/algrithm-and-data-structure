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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
private:
    Trie_node **children;
    bool is_terminal;
    static int const CHARACTERS = 26;
    
    
public:
    Trie_node();
    Trie_node *child( int ) const;
    
    bool member( std::string const &, int ) const;
    
    bool insert( std::string const &, int );
    bool erase( std::string const &, int, Trie_node *& );
    void clear();
    
    friend class Trie;
    
    // if ptr is a pointer to a Trie_node object
    // in one of the friendly classes, you should:
    //    use   ptr->next_   to modify it
    //    use   ptr->next()      to access it
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {
    // empty constructor
}

Trie_node *Trie_node::child( int n ) const {
    if ( children == nullptr ) {
        return nullptr;
    } else {
        return children[n];
    }
}

bool Trie_node::member( std::string const &str, int depth ) const {
    char cr=tolower(str[depth]);
    int n=cr-'a';
    if (children == nullptr) {
        if (depth==str.length()) {
            return is_terminal;
        }
        return false;
    }else{
        if (depth==str.length()) {
            return is_terminal;
        }
        if (children[n]==nullptr) {
            //            std::cout << char(n+'a') << std::endl;
            return false;
        }
    }
    return children[n]->member(str, depth+1);
}

bool Trie_node::insert( std::string const &str, int depth ) {
    char cr=tolower(str[depth]);
    int n=cr-'a';
    if (depth==str.length()) {
        //        std::cout << char(n+'a') << std::endl;
        is_terminal=true;
        return true;
    }
    if (children==nullptr) {
        children=new Trie_node*[26];
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        Trie_node *child_node=new Trie_node();
        //        std::cout << char(n+'a') << std::endl;
        children[n]=child_node;
        //child_node->children=new Trie_node*[26];
        //        for (int i=0; i<26; i++) {
        //            child_node->children[i]=nullptr;
        //        }
        //child_node->children=new Trie_node*[26];
    }
    if (children[n]==nullptr) {
        Trie_node *child_node=new Trie_node();
        //        std::cout << char(n+'a') << std::endl;
        children[n]=child_node;
    }
    //return children[n]->insert(str,depth+1);
    //    std::cout << char(n+'a') << std::endl;
    return children[n]->insert(str, depth+1);
}

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {
    char cr=tolower(str[depth]);
    int n=cr-'a';
    if (depth==str.length()) {
        //return true;
        is_terminal=false;
        if (children!=nullptr) {
            return true;
        }
        delete this;
        ptr_to_this = nullptr;
        return true;
    } else {
        bool lastC=children[n]->erase(str, depth+1, children[n]);
        if (lastC==true) {
            //if (depth==0) {
            //    ptr_to_this->children[n]=nullptr;
            //    return true;
            //}
            if (children == nullptr) {
                //delete ptr_to_this->children[n];
                //delete[] children;
                delete this;
                ptr_to_this=nullptr;
                return true;
            }
            for (int i=0; i<26; i++) {
                if (child(i)!=nullptr) {
                    return true;
                }
            }
            delete[] children;
            delete this;
            ptr_to_this=nullptr;
            return true;
        }
    }
    return false;
}

void Trie_node::clear() {
    if (this == nullptr) {
        return;
    }
    if (children==nullptr) {
        delete this;
    } else {
        for (int i=0; i<26; i++) {
            if (children[i]!=nullptr) {
                children[i]->clear();
                //delete children[i];
            }
        }
        delete[] children;
        delete this;
    }
}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
