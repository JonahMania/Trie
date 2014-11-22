#ifndef _TRIE_HPP_
#define _TRIE_HPP_

#include <iostream>

#define ARRAY_SIZE 27

//typedef char contentType;

struct trieNode
{
    //Constructor for node
    trieNode();
    //True if node is leaf node
    bool isLeaf;
    //Array of pointers to children nodes
    trieNode* children[ARRAY_SIZE];  
};

class Trie
{
    public:
        //Constructor for Trie
        Trie();
        //Deconstructor for Trie
        ~Trie();
        //Inserts a key into the trie
        void insert( std::string key );
        //Removes a key from the trie
        bool remove( std::string key );
        //Searches the trie and returns true if the key is found
        bool search( std::string key );
    private:
        //Root node of the trie
        trieNode *root;

};

#endif
