#include "trie.hpp"

int main()
{
    //Test the tire with integer values
    Trie<int> testInt;
    testInt.insert("hello", 4);
    testInt.insert("ball", 2);
    testInt.insert("balloon", 3);
    testInt.remove("ball");

    if( testInt.search( "ball" ) )
        std::cout<<"ball was found in the int trie value: "<< testInt.getValue("ball") <<std::endl;
    if( testInt.search( "balloon" ) )
        std::cout<<"balloon was found in the int trie value: "<< testInt.getValue("balloon") <<std::endl;
    if( testInt.search( "hello" ) )
        std::cout<<"hello was found in the int trie value: "<< testInt.getValue("hello") <<std::endl;
    if( testInt.search( "you" ) )
        std::cout<<"you was found in the int trie value: "<< testInt.getValue("you") <<std::endl;
 
    //Test the tire with string values
    Trie<std::string> testStr;
    testStr.insert("hello", "hello value");
    testStr.insert("ball", "ball value");
    testStr.insert("balloon", "balloon value");
    testStr.remove("ball");

    if( testStr.search( "ball" ) )
        std::cout<<"ball was found in the string trie value: "<< testStr.getValue("ball") <<std::endl;
    if( testStr.search( "balloon" ) )
        std::cout<<"balloon was found in the string trie value: "<< testStr.getValue("balloon") <<std::endl;
    if( testStr.search( "hello" ) )
        std::cout<<"hello was found in the string trie value: "<< testStr.getValue("hello") <<std::endl;
    if( testStr.search( "you" ) )
        std::cout<<"you was found in the string trie value: "<< testStr.getValue("you") <<std::endl;

}
