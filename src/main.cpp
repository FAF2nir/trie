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
    std::vector<char> s1({'z', 'b', 'c'});
    
    trie<char>& t1 = t[s];

    trie<char>& t2 = t[s1];
    
    std::cout << "t1" << std::endl << t1 << std::endl;
    std::cout << "t2" << std::endl << t2 << std::endl;


    return 0;
}
