#include <iostream>
#include <algorithm>
#include "trie.cpp"
#include <cassert>
#include <fstream>

int main()
{
    trie<int> t;
    try {
        std::cin >> t;
    } catch(parser_exception e) {
        std::cout << e.what() << std::endl;
    }
    t.path_compress();

    std::cout << t << std::endl;

    for(trie<int>::leaf_iterator it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << std::endl;
    }
}