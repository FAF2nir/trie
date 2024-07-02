#include <iostream>
#include <algorithm>
#include "trie.cpp"

int main()
{
    trie<std::string> t;

    try {
        std::cin >> t;
    }
    catch (parser_exception e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << t << std::endl;
}
/*
children = {
    compilers children = {
        g++ children = {
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

children = {
	a children = { b 1.1 children = {}, c 0.5 children = {} },
	d children = { e children = { f 3.3 children = {} } }
}

children = {
    a 3.1 children = {}, 
    ac children = {
        bc 2.9 children = {},
        c children = {
            dg children = {
                x 7.0 children = {},
                yz 5.3 children = {}
            }
        }
    }
}
*/
