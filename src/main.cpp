#include <iostream>
#include <algorithm>
#include "trie.cpp"
#include <cassert>
#include <fstream>

void test_construction_destruction() {
    trie<char> t1;
    assert(t1.get_weight() == 0.0);

    trie<char> t2(5.1);
    assert(t2.get_weight() == 5.1);

    std::cout << "Construction and destruction tests passed." << std::endl;
}

void test_parsing() {
/*    std::ifstream file1("trie_char.tr");
    trie<char> t1;
    file1 >> t1;
    file1.close();

    std::ifstream file2("trie_double.tr");
    trie<double> t2;
    file2 >> t2;
    file2.close();

    std::ifstream file3("trie_string.tr");
    trie<std::string> t3;
    file3 >> t3;
    file3.close();

    std::cout << "Parsing tests passed." << std::endl;
*/}


void test_basic_operations() {
    trie<char> t;
    t.set_weight(3.1);

    trie<char> child1(2.9);
    child1.set_label(new char('b'));
    t.add_child(child1);

    trie<char> child2(7.0);
    child2.set_label(new char('c'));
    t.add_child(child2);

    std::cout << "Basic operations tests passed." << std::endl;
}

void test_iterators() {
    trie<char> t;
    t.set_weight(3.1);

    trie<char> child1(2.9);
    child1.set_label(new char('b'));
    t.add_child(child1);

    trie<char> child2(7.0);
    child2.set_label(new char('c'));
    t.add_child(child2);

    // Test node_iterator
    auto node_it = t.root();
    assert(node_it == t.root());

    // Test leaf_iterator
    auto leaf_it = t.begin();
    assert(leaf_it.get_leaf().get_weight() == 2.9);
    ++leaf_it;

    std::cout << "Iterator tests passed." << std::endl;
}

void test_prefix_search() {
    trie<char> t;
    t.set_weight(3.1);

    trie<char> child1(2.9);
    child1.set_label(new char('b'));
    t.add_child(child1);

    trie<char> child2(7.0);
    child2.set_label(new char('c'));
    t.add_child(child2);

    std::vector<char> prefix{'b'};
    auto subtrie = t[prefix];
    assert(subtrie.get_weight() == 2.9);

    std::cout << "Prefix search tests passed." << std::endl;
}

void test_max_leaf() {
    trie<char> t;
    t.set_weight(3.1);

    trie<char> child1(2.9);
    child1.set_label(new char('b'));
    t.add_child(child1);

    trie<char> child2(7.0);
    child2.set_label(new char('c'));
    t.add_child(child2);

    std::cout << t << std::endl;

    auto max_leaf = t.max();
    assert(max_leaf.get_weight() == 7);

    std::cout << "Max leaf tests passed." << std::endl;
}

int main()
{
    trie<int> t;
    try {
        std::cin >> t;
    } catch(parser_exception e) {
        std::cout << e.what() << std::endl;
    }

    trie<int> t1 = t;

    t1 = t1[{2, 7}];

    std::cout << t1 << std::endl;

    return 0;
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
