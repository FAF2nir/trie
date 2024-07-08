#include <iostream>
#include <algorithm>
#include "trie.cpp"

int main()
{
    trie<std::string> t1;

    try {
        std::cin >> t1;
    }
    catch (parser_exception e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    trie<std::string> t2 = t1;

    std::cout << (t1 == t2) << std::endl;
}
/*
children = {
    true children = {
        a children = {
            cazzo 3.3 children = {},
            pene 4.5 children = {}
        },

        b children = {
            puzza children = {
                sgorbio 5.5 children = {},
                sburro children = {
                    susina 9.2 children = {},
                    suso 0.0 children = {},
                    susan 9.0 children = {}
                },
                sbarrio 4.4 children = {}
            }
        }
    },

    false children = {
        a children = {
            cazzo 3.3 children = {},
            pene 4.5 children = {}
        },

        b children = {
            puzza children = {
                sgorbio 5.5 children = {},
                sburro children = {
                    susina 9.2 children = {},
                    suso 0 children = {},
                    susan 8.0 children = {}
                },
                sbarrio 4.4 children = {}
            }
        }
    }
}



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
