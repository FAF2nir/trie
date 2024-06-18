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

        trie<char> t1 = std::move(t);

        std::cout << "t1: " << std::endl;
        std::cout << t1;

        return 0;
}