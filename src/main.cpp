#include <iostream>
#include "trie.cpp"

int main()
{
    trie<std::string> t;
    trie<std::string> t1;

    try {
        std::cin >> t;
        std::cin >> t1;
    }
    catch (parser_exception e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << (t == t1) << std::endl;
    std::cout << (t != t1) << std::endl; 
    return 0;
}
