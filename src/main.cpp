#include <iostream>
#include "trie.cpp"

int main()
{
    trie<std::string> t1;
    trie<std::string> t2;

    try {
        std::cin >> t1;
        std::cin >> t2;
    }
    catch (parser_exception e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << t1[{"compilers", "g+"}] << std::endl;
    std::cout << t2[{"lab1", "g++"}] << std::endl;

    std::cout << (t1[{"compilers", "g+"}] == t2[{"lab1", "g++"}]) << std::endl;
    std::cout << (t1 == t2) << std::endl;


    return 0;
}
/*
children = {
    compilers children = {
        g+ children = {
            size 3.3 children = {}
        },
        javac 3.1 children = {}
    },
    languages children = {
        c++ 1.1 children = {},
        java 0.5 children = {}
    }
}

children = {
    lab1 children = {
        g++ children = {
            size 3.3 children = {}
        },
        javac 3.1 children = {}
    },
    lab2 children = {
        c++ 1.1 children = {},
        java 0.5 children = {}
    }
}
*/
