#include <iostream>
#include "trie.cpp"

int main()
{
    trie<char> t;

    try {
        std::cin >> t;
    }
    catch (parser_exception e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::vector<char> s({'b', 'c', 'z'});
    
    trie<char>& t1 = t[s];
    
    std::cout<< "t1" << std::endl << t1 << std::endl;

    return 0;
}
