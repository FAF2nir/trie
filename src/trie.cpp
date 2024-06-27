#include "../include/trie.hpp"  // It is forbidden to include other libraries!

template <typename T>
trie<T>::trie() : m_p(nullptr), m_l(nullptr), m_c(), m_w(0) {}

template <typename T>
trie<T>::trie(double w) : m_p(nullptr), m_l(nullptr), m_c(), m_w(w) {}

template <typename T>
trie<T>::trie(trie<T> const& t) : trie() {
    *this = t;
}

template <typename T>
trie<T>::trie(trie<T>&& t) : trie() {
    *this = std::move(t);
}

template <typename T>
trie<T>::~trie() {
    if(m_l) delete m_l;
}

template <typename T>
trie<T>& trie<T>::operator=(trie<T> const& rhs) {
    if(this != &rhs) {
        if(rhs.m_l) { m_l = new T(*rhs.m_l); }

        if(rhs.m_w != 0) {
            m_w = rhs.m_w;
        }
        else {
            m_c = rhs.m_c;
            for(trie<T>& child : m_c) {
                child.m_p = this;
            }
        }
    }
    return *this;
}

template <typename T>
trie<T>& trie<T>::operator=(trie<T>&& rhs) {
    if(this != &rhs) {
        m_p = rhs.m_p;
        m_l = rhs.m_l;
        m_w = rhs.m_w;
        m_c = std::move(rhs.m_c);

        for(trie<T>& child : m_c) {
            child.m_p = this;
        }

        rhs.m_p = nullptr;
        rhs.m_l = nullptr;
    }
    return *this;
}

/* setters */
template <typename T>
void trie<T>::set_weight(double w) { m_w = w; }

template <typename T>
void trie<T>::set_label(T* l) { m_l = l; }

template <typename T>
void trie<T>::set_parent(trie<T>* p) { m_p = p; }

template <typename T>
void trie<T>::add_child(trie<T> const& c) {
    if(m_c.contains(c)) {
        throw parser_exception("[!] Error: this element is already in the bag.");
    }

    if(m_w != 0) {
        m_w = 0;
    }

    m_c.add(c);
}

/* getters */
template <typename T>
double trie<T>::get_weight() const { return m_w; }

template <typename T>
T const* trie<T>::get_label() const { return m_l; }

template <typename T>
trie<T> const* trie<T>::get_parent() const { return m_p; }

template <typename T>
bag<trie<T>> const& trie<T>::get_children() const { return m_c; }

template <typename T>
T* trie<T>::get_label() { return m_l; }

template <typename T>
trie<T>* trie<T>::get_parent() { return m_p; }

template <typename T>
bag<trie<T>>& trie<T>::get_children() { return m_c; }


/* comparison */
template <typename T>
bool trie<T>::operator==(trie<T> const& t) const {
    
    if( (m_l == nullptr && t.m_l != nullptr) || (m_l != nullptr && t.m_l == nullptr) ) {
        return false;
    }

    if(m_l != nullptr && t.m_l != nullptr) {
        if( *(m_l) != *(t.m_l) ) {
            return false; 
        }
    }

    if(m_w != t.m_w) {
        return false;
    }

    if(m_c != t.m_c) {
        return false;
    }

    return true;
}

template <typename T>
bool trie<T>::operator!=(trie<T> const& t) const {
    return !(*this == t);
}

template <typename T>
trie<T>& trie<T>::operator[](std::vector<T> const& s) {
    trie<T>* sub_trie = this;

    if(s.empty()) {
        return *sub_trie;
    }

    for(typename bag<trie<T>>::iterator it = get_children().begin(); it != get_children().end(); ++it) {
        if( (it->get_label() != nullptr) && ( *(it->get_label()) == s.at(0)) ) {
            std::vector<T> sub_vec(s.begin()+1, s.end());
            sub_trie = &(*it)[sub_vec];
        }
    }

    return *sub_trie;
}

template <typename T>
trie<T> const& trie<T>::operator[](std::vector<T> const& s) const {
    trie<T> const* sub_trie = this;
    
    if(s.empty()) {
        return *sub_trie;    
    }

    for(typename bag<trie<T>>::const_iterator it = get_children().begin(); it != get_children().end(); ++it) {
        if( (it->get_label() != nullptr) && ( *(it->get_label()) == s.at(0)) ) { 
            std::vector<T> sub_vec(s.begin()+1, s.end());
            sub_trie = &(*it)[sub_vec];
        }
    }
    
    return *sub_trie;
}

/*
    parsing:

    TRIE -> LEAF | NODE
    LEAF -> double children = {}
    NODE -> children = { label1 TRIE, ... }
*/

template <typename T>
trie<T> NODE(std::istream& is, trie<T>* parent, T* label);
template <typename T>
trie<T> LEAF(std::istream& is, trie<T>* parent, T* label);
template <typename T>
trie<T> TR(std::istream& is, trie<T>* parent, T* label);


static void consume_children(std::istream& is)
{
    //consume eventual spacing
    char c;
    is >> c;
    is.putback(c);

    //consume the keyword 'children'
    char buff[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    is.read(buff, 8);
    std::string s(buff);

    if (s != "children") throw parser_exception("[!] Parser Error: 'children' expected.");

    //consume '=', ignoring eventual spacing
    is >> c;
    if (c != '=') throw parser_exception("[!] Parser Error: '=' expected.");

    //consume '{', ignoring eventual spacing
    is >> c;
    if (c != '{') throw parser_exception("[!] Parser Error: '{' expected.");
}

template <typename T>
trie<T> NODE(std::istream& is, trie<T>* parent, T* label) {
    consume_children(is);

    trie<T> r;
    r.set_label(label);
    r.set_parent(parent);

    char c;
    do {
        T lab;
        is >> lab;
        T* l = new T(lab);

        r.add_child(TR(is, &r, l));

        is >> c;
    } while(c == ',');

    if(c != '}') {
        throw parser_exception("[!] Parser Error: '}' or ',' expected.");
    }

    return r;
}

template <typename T>
trie<T> LEAF(std::istream& is, trie<T>* parent, T* label) {
    double w;
    is >> w;

    trie<T> r(w);
    r.set_label(label);
    r.set_parent(parent);

    consume_children(is);

    char c;
    is >> c;
    if(c != '}') {
        throw parser_exception("[!] Parser Error: '}' expected.");
    }

    return r;
}

template <typename T>
trie<T> TR(std::istream& is, trie<T>* parent, T* label) {
    char c;
    is >> c;
    is.putback(c);

    if(c == 'c') {
        return NODE(is, parent, label);
    } else {
        return LEAF(is, parent, label);
    }
}

template <typename T>
std::istream& operator>>(std::istream& is, trie<T>& t) {
    if(!is.eof()) {
        t = TR<T>(is, nullptr, nullptr);
    }

    return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, trie<T> const& t) {
    std::cout << t.get_children();
    
    return os;
}
