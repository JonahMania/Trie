#include "trie.hpp"
/*******************
Name: Jonah Mania
date: 11/16/2014
*******************/

//TrieNode constructor
trieNode::trieNode()
{
    //Set pointers in children array to NULL
    trieNode* children[ARRAY_SIZE] = {};     
}
//Trie constructor
Trie::Trie()
{
    root = new trieNode();
}
//Recursivly delete nodes in the tree
void deleteTrie( trieNode* root )
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
Trie::~Trie()
{
    deleteTrie( root );
    delete root;
}
//Insert method
void Trie::insert( std::string key )
{
    //Start at root node
    trieNode* curr = root;
    //Loop through key
    for( int i = 0; i < key.size(); ++i )
    {
        //If the current child for the letter in the key is NULL insert an internal node
        if( curr->children[ key[i] - 97 ] == NULL )
            curr->children[ key[i] - 97 ] = new trieNode(); 
        //If the child is not NULL move on to the next letter
        curr = curr->children[ key[i] - 97 ];  
    }    
    curr->isLeaf = true;
}
//Looks at all children of a node and returns true if they are all NULL
bool checkChildren( trieNode* curr )
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
void removeRecursive( trieNode* curr, std::string key, int level )
{
    //Create a node to keep track of the root 
    trieNode* currRoot = curr;
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
bool Trie::remove( std::string key )
{
    trieNode* curr = root;
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
bool Trie::search( std::string key )
{
    trieNode* curr = root;
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
