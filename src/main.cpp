#include <iostream>
#include <algorithm>
#include "trie.cpp"

int main()
{
    trie<char> t1;

    try {
        std::cin >> t1;
    }
    catch (parser_exception e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    trie<char> const& t = t1;
    trie<char>& s = t1;

    /* assume t is a trie<T> */
    for (auto leaf_it = t.begin(); leaf_it != t.end(); leaf_it++) {
        trie<char>::const_node_iterator node_it = leaf_it; // we convert leaf_it into node_it to navigate from leaf to root
        std::vector<char> s;
        while (node_it != t.root()) {
            s.push_back(*node_it);
            node_it++;
        }
        std::reverse(s.begin(), s.end());
        for (auto const& x: s) std::cout << x << ' ';
        std::cout << '\n';
    }
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
