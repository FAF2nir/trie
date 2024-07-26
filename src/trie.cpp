#include "../include/trie.hpp"  // It is forbidden to include other libraries!

template <typename T>
trie<T>::trie() : m_p(nullptr), m_l(nullptr), m_c(), m_w(0) {}

template <typename T>
trie<T>::trie(double w) : m_p(nullptr), m_l(nullptr), m_c(), m_w(w) {}

template <typename T>
trie<T>::trie(trie<T> const& t) : m_p(nullptr), m_l(t.m_l ? new T(*t.m_l) : nullptr), m_c(t.m_c), m_w(t.m_w) {
    for(trie<T>& c : m_c) {
        c.m_p = this;
    }
}

template <typename T>
trie<T>::trie(trie<T>&& t) : m_p(nullptr), m_l(t.m_l), m_c(std::move(t.m_c)), m_w(std::move(t.m_w)) {
    for(trie<T>& c : m_c) {
        c.m_p = this;
    }
    t.m_l = nullptr;
    t.m_p = nullptr;
}

template <typename T>
trie<T>::~trie() {
    if(m_l) delete m_l;
}

template <typename T>
trie<T>& trie<T>::operator=(trie<T> const& rhs) {
    if(this != &rhs) {
        m_w = rhs.m_w;
        m_c = rhs.m_c;

        if(!m_c.empty()) {
            typename bag<trie<T>>::iterator this_it = m_c.begin();
            typename bag<trie<T>>::const_iterator rhs_it = rhs.m_c.begin();

            while(this_it != m_c.end() && rhs_it != rhs.m_c.end()) {
                if(this_it->m_l) {
                    delete this_it->m_l;
                    this_it->m_l = nullptr;
                }
                if(rhs_it->m_l) {
                    this_it->m_l = new T( *(rhs_it->m_l) );
                }

                ++this_it;
                ++rhs_it;
            }
        }
    }
    return *this;
}

template <typename T>
trie<T>& trie<T>::operator=(trie<T>&& rhs) {
    if(this != &rhs) {
        m_w = std::move(rhs.m_w);
        m_c = std::move(rhs.m_c);

        for(trie<T>& child : m_c) {
            child.m_p = this;
        }
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
    if(m_c.empty() != t.m_c.empty()) {
        return false;
    }

    return (m_w == t.m_w) && (m_c == t.m_c);
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

/* NODE AND LEAF ITERATORS */

/* node iterator */
template <typename T>
trie<T>::node_iterator::node_iterator(trie<T>* ptr) : m_ptr(ptr) {}

template <typename T>
typename trie<T>::node_iterator::reference trie<T>::node_iterator::operator*() const {
    return *(m_ptr->m_l);
}

template <typename T>
typename trie<T>::node_iterator::pointer trie<T>::node_iterator::operator->() const {
    return m_ptr->m_l;
}

template <typename T>
typename trie<T>::node_iterator& trie<T>::node_iterator::operator++() {
    if(m_ptr) {
        m_ptr = m_ptr->get_parent();
    }
    return *this;
}

template <typename T>
typename trie<T>::node_iterator trie<T>::node_iterator::operator++(int) {
    node_iterator ret(m_ptr);
    ++(*this);
    return ret;
}

template <typename T>
bool trie<T>::node_iterator::operator==(node_iterator const& rhs) const {
    return m_ptr == rhs.m_ptr;
}

template <typename T>
bool trie<T>::node_iterator::operator!=(node_iterator const& rhs) const {
    return m_ptr != rhs.m_ptr;
}

/* const_node_iterator */
template <typename T>
trie<T>::const_node_iterator::const_node_iterator(trie<T> const* ptr) : m_ptr(ptr) {}

template <typename T>
typename trie<T>::const_node_iterator::reference trie<T>::const_node_iterator::operator*() const {
    return *(m_ptr->m_l);
}

template <typename T>
typename trie<T>::const_node_iterator::pointer trie<T>::const_node_iterator::operator->() const {
        return m_ptr->m_l;
}

template <typename T>
typename trie<T>::const_node_iterator& trie<T>::const_node_iterator::operator++() {
    if(m_ptr) {
        m_ptr = m_ptr->m_p;
    }

    return *this;
}

template <typename T>
typename trie<T>::const_node_iterator trie<T>::const_node_iterator::operator++(int) {
    const_node_iterator ret(m_ptr);
    ++(*this);
    return ret;
}

template <typename T>
bool trie<T>::const_node_iterator::operator==(const_node_iterator const& rhs) const {
    return m_ptr == rhs.m_ptr; 
}

template <typename T>
bool trie<T>::const_node_iterator::operator!=(const_node_iterator const& rhs) const {
    return m_ptr != rhs.m_ptr;
}

/* leaf_iterator */
template <typename T>
trie<T>::leaf_iterator::leaf_iterator(trie<T>* ptr) : m_ptr(ptr) {}

template <typename T>
typename trie<T>::leaf_iterator::reference trie<T>::leaf_iterator::operator*() const {
    return *(m_ptr->m_l);
}

template <typename T>
typename trie<T>::leaf_iterator::pointer trie<T>::leaf_iterator::operator->() const {
    return m_ptr->m_l;
}

template <typename T>
typename trie<T>::leaf_iterator& trie<T>::leaf_iterator::operator++() {
    trie<T>* parent = get_leaf().m_p;

    if(parent == nullptr) {
        m_ptr = nullptr;
        return *this;
    }

    //iterate over the siblings of the current node and get the next one.
    typename bag<trie<T>>::iterator c_it = parent->m_c.begin();
    while(*(c_it->m_l) != *(m_ptr->m_l)) { ++c_it; }
    ++c_it;


    if(c_it != parent->m_c.end()) {
        //if it is a leaf, just set m_ptr to it. If not, set m_ptr to the first leaf of the sub-trie
        if(c_it->m_c.empty()) {
            m_ptr = &(*c_it);
        } else {
            m_ptr = &(c_it->begin().get_leaf());
        }
    } else {
        //if it has reached the end of this bag, the new leaf is end() of the next up-trie

        while(parent->end() == nullptr && parent->m_p != nullptr) {
            parent = parent->m_p;
        }

        m_ptr = &(parent->end().get_leaf());
    }

    return *this;
}

template <typename T>
typename trie<T>::leaf_iterator trie<T>::leaf_iterator::operator++(int) {
    leaf_iterator ret(m_ptr);
    ++(*this);
    return ret;
}

template <typename T>
bool trie<T>::leaf_iterator::operator==(leaf_iterator const& rhs) const {
    return m_ptr == rhs.m_ptr;
}

template <typename T>
bool trie<T>::leaf_iterator::operator!=(leaf_iterator const& rhs) const {
    return m_ptr != rhs.m_ptr;
}

template <typename T>
trie<T>::leaf_iterator::operator node_iterator() const {
    return node_iterator(m_ptr);
}

template <typename T>
trie<T>& trie<T>::leaf_iterator::get_leaf() const {
    return *m_ptr;
}

/* const_leaf_iterator */
template <typename T>
trie<T>::const_leaf_iterator::const_leaf_iterator(trie<T> const* ptr) : m_ptr(ptr) {}

template <typename T>
typename trie<T>::const_leaf_iterator::reference trie<T>::const_leaf_iterator::operator*() const {
    return *(m_ptr->m_l);
}

template <typename T>
typename trie<T>::const_leaf_iterator::pointer trie<T>::const_leaf_iterator::operator->() const {
    return m_ptr->m_l;
}

template <typename T>
typename trie<T>::const_leaf_iterator& trie<T>::const_leaf_iterator::operator++() {
    trie<T> const* parent = get_leaf().m_p;

    if(parent == nullptr) {
        m_ptr = nullptr;
        return *this;
    }

    //iterate over the siblings of the current node and get the next one.
    typename bag<trie<T>>::const_iterator c_it = parent->m_c.begin();
    while(*(c_it->m_l) != *(m_ptr->m_l)) { ++c_it; }
    ++c_it;


    if(c_it != parent->m_c.end()) {
        //if it is a leaf, just set m_ptr to it. If not, set m_ptr to the first leaf of the sub-trie
        if(c_it->m_c.empty()) {
            m_ptr = &(*c_it);
        } else {
            m_ptr = &(c_it->begin().get_leaf());
        }
    } else {
        //if it has reached the end of this bag, the new leaf is end() of the next up-trie
        while(parent->end() == nullptr && parent->m_p != nullptr) {
            parent = parent->m_p;
        }

        m_ptr = &(parent->end().get_leaf());
    }

    return *this;
}

template <typename T>
typename trie<T>::const_leaf_iterator trie<T>::const_leaf_iterator::operator++(int) {
    const_leaf_iterator ret(m_ptr);
    ++(*this);
    return ret;
}

template <typename T>
bool trie<T>::const_leaf_iterator::operator==(const_leaf_iterator const& rhs) const {
    return m_ptr == rhs.m_ptr; 
}

template <typename T>
bool trie<T>::const_leaf_iterator::operator!=(const_leaf_iterator const& rhs) const {
    return m_ptr != rhs.m_ptr; 
}

template <typename T>
trie<T>::const_leaf_iterator::operator const_node_iterator() const {
    return {m_ptr};
}

template <typename T>
trie<T> const& trie<T>::const_leaf_iterator::get_leaf() const {
    return *m_ptr;
}

/* trie.hpp iterator methods */

template <typename T>
typename trie<T>::const_leaf_iterator trie<T>::begin() const {
    if(m_c.empty()) {
        return {this};
    }

    return (m_c.head())->info.begin();
}

template <typename T>
typename trie<T>::const_leaf_iterator trie<T>::end() const {
    if(m_p == nullptr) {
        return {nullptr};
    }

    trie<T> const* parent = m_p;
    typename bag<trie<T>>::const_iterator c_it = parent->m_c.begin();

    while(*c_it != *this) { ++c_it; }
    ++c_it;

    if(c_it != parent->m_c.end()) {
        if(c_it->m_c.empty()) { 
            return {&(*c_it)};
        }
        else { 
            return {c_it->begin()};
        }
    } else {
        return {nullptr};
    }
}

template <typename T>
typename trie<T>::leaf_iterator trie<T>::begin() {
    if(m_c.empty()) {
        return {this};
    }

    return (m_c.head())->info.begin();
}

template <typename T>
typename trie<T>::leaf_iterator trie<T>::end() {
    if(m_p == nullptr) {
        return {nullptr};
    }

    trie<T>* parent = m_p;
    typename bag<trie<T>>::iterator c_it = parent->m_c.begin();

    while(*c_it != *this) { ++c_it; }
    ++c_it;

    if(c_it != parent->m_c.end()) {
        if(c_it->m_c.empty()) { 
            return {&(*c_it)};
        }
        else { 
            return {c_it->begin()};
        }
    } else {
        return {nullptr};
    }
}

template <typename T>
typename trie<T>::node_iterator trie<T>::root() {
    return {this};
}

template <typename T>
typename trie<T>::const_node_iterator trie<T>::root() const{
    return {this};
}

/* max_leaf */
template <typename T>
trie<T>& trie<T>::max() {
    if(m_c.empty()) {
        return *this;
    }

    trie<T>* max_leaf = &(begin().get_leaf());

    for(trie<T>& c : m_c) {
        trie<T>& child_max = c.max();
        if(child_max.m_w > max_leaf->m_w) {
            max_leaf = &child_max;
        }
    }

    return *max_leaf;
}

template <typename T>
trie<T> const& trie<T>::max() const {
    if(m_c.empty()) {
        return *this;
    }

    trie<T> const* max_leaf = &(begin().get_leaf());

    for(trie<T> const& c : m_c) {
        trie<T> const& child_max = c.max();
        if(child_max.m_w > max_leaf->m_w) {
            max_leaf = &child_max;
        }
    }

    return *max_leaf;
}

/*
    CFG:
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
    if(t.get_children().empty()) {
        if(t.get_label() != nullptr) {
            os << *(t.get_label()) << " ";
        }

        os << t.get_weight() << " children={}";
    
    } else {
        bag<trie<T>> const& children = t.get_children();

        if(t.get_label() != nullptr) { 
            os << *(t.get_label()) << " "; 
        }
        os<< "children={ ";

        typename bag<trie<T>>::const_iterator it = children.begin();
        do {
            os << *it;

            if(++it != children.end()) {
                os << ", ";
            }
        } while(it != children.end());

        os << " }";
    }
    
    return os;
}