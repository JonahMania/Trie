#include "trie.hpp"

int main()
{
    Trie test;
    test.insert("hello");
    test.insert("ball");
    test.insert("balloon");
    test.remove("ball");

    if( test.search( "ball" ) )
        std::cout<<"ball was found in the trie"<<std::endl;
    if( test.search( "balloon" ) )
        std::cout<<"balloon was found in the trie"<<std::endl;
    if( test.search( "hello" ) )
        std::cout<<"hello was found in the trie"<<std::endl;
    if( test.search( "you" ) )
        std::cout<<"you was found in the trie"<<std::endl; 
}
