#ifndef _TRIE_HPP_
#define _TRIE_HPP_
/**********************
* Author: Jonah Mania *
* Date: 11/16/2014    *
**********************/

#include <iostream>

#define ARRAY_SIZE 26

template <typename T>
struct trieNode
{
    //Default constructor for node
    trieNode();
    //Constructor to set a node with new value
    trieNode( T v );
    //True if node is leaf node
    bool isLeaf;
    //Array of pointers to children nodes
    trieNode<T>* children[ARRAY_SIZE]; 
    //Element to be stored in a node of the trie
    T value;
};

template <typename T>
class Trie
{
    public:
        //Constructor for Trie
        Trie();
        //Deconstructor for Trie
        ~Trie();
        //Inserts a key into the trie
        void insert( std::string key, T v );
        //Removes a key from the trie
        bool remove( std::string key );
        //Searches the trie and returns true if the key is found
        bool search( std::string key );
        //Searches the trie and returns the value at a specified key if found
        T getValue( std::string ); 
    private:
        //Root node of the trie
        trieNode<T> *root;

};

//TrieNode default constructor
template <typename T>
trieNode<T>::trieNode()
{
    //Set pointers in children array to NULL
    trieNode<T>* children[ARRAY_SIZE] = {};
}
//TrieNode constructor to set value
template <typename T>
trieNode<T>::trieNode( T v )
{
    //Set pointers in children array to NULL
    trieNode<T>* children[ARRAY_SIZE] = {};
    //Set the trieNode's value to v
    value = v;
}
//Trie constructor
template <typename T>
Trie<T>::Trie()
{
    root = new trieNode<T>();
}
//Recursivly delete nodes in the tree
template <typename T>
void deleteTrie( trieNode<T>* root )
{
    //Check each item of children array and call deleteTrie recursivly for values not equal to NULL
    for(int i = 0; i < ARRAY_SIZE; ++i )
    {
        if( root->children[i] != NULL )
            deleteTrie( root->children[i] );
    }

    //Delete every item in the children array
    for( int i = 0; i < ARRAY_SIZE; ++i )
    {
        if( root->children[i] != NULL )
            delete root->children[i];
    }
}
//Trie deconstructor
template <typename T>
Trie<T>::~Trie()
{
    deleteTrie( root );
    delete root;
}
//Insert method
template <typename T>
void Trie<T>::insert( std::string key, T v )
{
    //Start at root node
    trieNode<T>* curr = root;
    //Loop through key
    for( int i = 0; i < key.size(); ++i )
    {
        //If the current child for the letter in the key is NULL insert an internal node
        if( curr->children[ key[i] - 97 ] == NULL )
            curr->children[ key[i] - 97 ] = new trieNode<T>( v );
        //If the child is not NULL move on to the next letter
        curr = curr->children[ key[i] - 97 ];
    }
    curr->isLeaf = true;
}
//Looks at all children of a node and returns true if they are all NULL
template <typename T>
bool checkChildren( trieNode<T>* curr )
{
    if( curr != NULL )
    {
        for( int i = 0; i < ARRAY_SIZE; ++i )
        {
            if( curr->children[i] != NULL )
                return false;
            if( i == ARRAY_SIZE - 1 )
                return true;
        }
    }
    return false;
}
//Helper function for remove
template <typename T>
void removeRecursive( trieNode<T>* curr, std::string key, int level )
{
    //Create a node to keep track of the root 
    trieNode<T>* currRoot = curr;
    //Set the leaf of the key to false
    if( level == key.size() - 1 )
        curr->children[key[level] - 97]->isLeaf = false;
    //If the current node is not NULL and our current level is not past the end of the key
    if( curr != NULL && level != key.size() - 1 )
    {
        //Set curr to the next letter in the key
        curr = curr->children[ key[level] - 97 ];
        //Recursivly call removeRecursive while incrementing the level by 1
        removeRecursive( curr, key, ++level );
        //If the node corresponding to the next letter in the key has no children delete it
        if( checkChildren( curr->children[key[level] - 97] ) )
        {
            delete curr->children[key[level] - 97];
            curr->children[key[level] - 97] = NULL;
        }
    }
    //If the node corresponding to the first letter in the key has no children delete it
    if( level - 1 == 0 )
    {
        if( checkChildren( currRoot->children[key[0] - 97] ) )
        {
            delete currRoot->children[ key[0] - 97 ];
            currRoot->children[ key[0] - 97 ] = NULL;
        }
    }
}
//Returns true when item is removed correctly and false if key does not exist
template <typename T>
bool Trie<T>::remove( std::string key )
{
    trieNode<T>* curr = root;
    //Check that the key exists in the trie
    for( int i = 0; i < key.size(); ++i )
    {
        if( curr->children[ key[i] - 97 ] == NULL )
            return false;
        curr = curr->children[ key[i] - 97 ];
    }
    //Call removeRecursive
    removeRecursive( root, key, 0 );
    return true;
}
//Returns true if the key is found in the trie
template <typename T>
bool Trie<T>::search( std::string key )
{
    trieNode<T>* curr = root;
    for( int i = 0; i < key.size(); ++i )
    {
        //If the the node corresponding to the next letter of the key does not exist return false
        if( curr->children[ key[i] - 97 ] == NULL )
            return false;
        //If the the node corresponding to the next letter of the key does exist move to that node
        curr = curr->children[ key[i] - 97 ];
    }
    //If the last letter in the key is the leaf return true
    if( curr->isLeaf )
        return true;
    return false;
}
//Searches the trie and returns the value at a specified key if found
template <typename T>
T Trie<T>::getValue( std::string key )
{
    trieNode<T>* curr = root;
    for( int i = 0; i < key.size(); ++i )
    {
        //If the the node corresponding to the next letter of the key does not exist break out of the loop
        if( curr->children[ key[i] - 97 ] == NULL )
            break;
        //If the the node corresponding to the next letter of the key does exist move to that node
        curr = curr->children[ key[i] - 97 ];
    }
    //If the last letter in the key is the leaf return the value of that key
    if( curr->isLeaf )
        return curr->value;
}
#endif
