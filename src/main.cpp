#include <iostream>
#include <algorithm>
#include "trie.cpp"
#include <cassert>
#include <fstream>

int main()
{

    trie<int> t;
    trie<int> sub;

    try {
        std::cin >> t;
        std::cin >> sub;
    } catch(parser_exception e) {
        std::cout << e.what() << std::endl;
    }


    t[{1}] = std::move(sub);
    std::cout << t << std::endl;
    std::cout << sub << std::endl;

    
}
/*
1: 0 children = {}

2: 1.1 children = {}

3: children = { 1 3.3 children = {} }

4: children = { 1 7.3 children = {}, 2 5.3 children = {} }

5: children = { 1 3.3 children = {}, 2 5.3 children = {}, 3 1.2 children = {} }

6: children = { 1 children = { 1 5.3 children = {}, 2 2.2 children = {} }, 2 5.3 children = {}, 3 1.2 children = {} }

7: children = { 1 children = { 1 5.3 children = {}, 2 2.2 children = {} }, 2 children = { 1 10.1 children = {} }, 3 1.2 children = {} }

8: children = { 1 children = { 1 10.1 children = {} }, 2 children = { 7 10.1 children = {} }, 3 1.2 children = {} }


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
            cazzo 0 children = {},
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
    true children = {
        a children = {
            cazo 3.3 children = {},
            pene 4.5 children = {}
        },

        b children = {
            puza children = {
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
            cazzo 0 children = {},
            pene 4.5 children = {}
        },

        c children = {
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
