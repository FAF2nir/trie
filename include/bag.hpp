template <typename T>
struct bag {
private:
    struct node {
        T info;
        node* next;
    };

    node* m_head;
    node* m_tail;

    /* private methods, used inside the container */
    void push_back(const T& info);
    void push_front(const T& info);
    void pop_back();
    void pop_front();
    void swap(node* a, node* b);

public:
    class iterator {
    private:
        node* m_ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        iterator(node*);

        reference operator*() const;
        pointer operator->() const;
        iterator& operator++();
        iterator& operator++(int);
        bool operator==(iterator const&) const;
        bool operator!=(iterator const&) const;

        operator bool() const;
    };

    class const_iterator {
    private:
        node const* m_ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T const;
        using pointer = T const*;
        using reference = T const&;

        const_iterator(node const*);

        reference operator*() const;
        pointer operator->() const;
        const_iterator& operator++();
        const_iterator& operator++(int);
        bool operator==(const_iterator const&) const;
        bool operator!=(const_iterator const&) const;

        operator bool() const;
    };

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    /* constructors */
    bag();
    bag(bag<T> const& b);
    bag(bag<T>&& b);

    /* destructor */
    ~bag();

    /* assignment operator */
    bag& operator=(bag<T> const& b);
    bag& operator=(bag<T>&& b);

    /* comparison operator */
    bool operator==(bag<T> const& b) const;
    bool operator!=(bag<T> const& b) const;

    /* methods */
    void clean();
    void add(const T& info);
    void sort();
    bool contains(const T& info) const;
    bool empty() const;
    node const* head() const;
    node* head();
    node const* tail() const;
    node* tail();
};

/* Iterator */
template <typename T>
bag<T>::iterator::iterator(node* ptr) : m_ptr(ptr) {}

template <typename T>
typename bag<T>::iterator::reference bag<T>::iterator::operator*() const {
    return m_ptr->info;
}

template <typename T>
typename bag<T>::iterator::pointer bag<T>::iterator::operator->() const {
    return &(m_ptr->info);
}

template <typename T>
typename bag<T>::iterator& bag<T>::iterator::operator++() {
    m_ptr = m_ptr->next;
    return *this;
}

template <typename T>
typename bag<T>::iterator& bag<T>::iterator::operator++(int) {
    iterator ret = *this;
    ++(*this);
    return ret;
}

template <typename T>
bool bag<T>::iterator::operator==(iterator const& rhs) const {
    return m_ptr == rhs.m_ptr;
}

template <typename T>
bool bag<T>::iterator::operator!=(iterator const& rhs) const {
    return m_ptr != rhs.m_ptr;
}

template <typename T>
bag<T>::iterator::operator bool() const {
    return m_ptr != nullptr;
}

template <typename T>
typename bag<T>::iterator bag<T>::begin() {
    return {m_head};
}

template <typename T>
typename bag<T>::iterator bag<T>::end() {
    return {nullptr};
}

/* const_iterator */
template <typename T>
bag<T>::const_iterator::const_iterator(node const* ptr) : m_ptr(ptr) {}

template <typename T>
typename bag<T>::const_iterator::reference bag<T>::const_iterator::operator*() const {
    return m_ptr->info;
}

template <typename T>
typename bag<T>::const_iterator::pointer bag<T>::const_iterator::operator->() const {
    return &(m_ptr->info);
}

template <typename T>
typename bag<T>::const_iterator& bag<T>::const_iterator::operator++() {
    m_ptr = m_ptr->next;
    return *this;
}

template <typename T>
typename bag<T>::const_iterator& bag<T>::const_iterator::operator++(int) {
    const_iterator ret = m_ptr;
    ++(*this);
    return ret;
}

template <typename T>
bool bag<T>::const_iterator::operator==(const_iterator const& rhs) const {
    return m_ptr == rhs.m_ptr;
}

template <typename T>
bool bag<T>::const_iterator::operator!=(const_iterator const& rhs) const {
    return m_ptr != rhs.m_ptr;
}

template <typename T>
bag<T>::const_iterator::operator bool() const {
    return m_ptr != nullptr;
}

template <typename T>
typename bag<T>::const_iterator bag<T>::begin() const {
    return {m_head};
}

template <typename T>
typename bag<T>::const_iterator bag<T>::end() const {
    return {nullptr};
}

/* constructors */
template <typename T>
bag<T>::bag() : m_head(nullptr), m_tail(nullptr) {};

template <typename T>
bag<T>::bag(bag const& b) : bag() {
    *this = b;
}

template <typename T>
bag<T>::bag(bag&& b) : bag() {
    *this = std::move(b);
}

/* destructor */
template <typename T>
bag<T>::~bag() {
    clean();
}

/* copy assignment */
template <typename T>
bag<T>& bag<T>::operator=(bag const& rhs) {
    if (this != &rhs) {
        clean();

        node* ptr = rhs.m_head;
        while (ptr)
        {
            push_back(ptr->info);
            ptr = ptr->next;
        }
    }
    return *this;
}

/* move assignment */
template <typename T>
bag<T>& bag<T>::operator=(bag&& b) {
    if (this != &b)
    {
        clean();

        m_head = b.m_head;
        m_tail = b.m_tail;

        b.m_head = b.m_tail = nullptr;
    }
    return *this;
}

/* comparison */
template <typename T>
bool bag<T>::operator==(bag<T> const& b) const {
    node* ptr1 = m_head;
    node* ptr2 = b.m_head;

    while(ptr1 && ptr2) {
        if(*(ptr1->info.get_label()) != *(ptr2->info.get_label())) {
            return false;
        }

        if(ptr1->info.get_weight() != ptr2->info.get_weight()) {
            return false;
        }

        if(ptr1->info.get_children() != ptr2->info.get_children()) {
            return false;
        }

        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    return ptr1 == nullptr && ptr2 == nullptr;
}

template <typename T>
bool bag<T>::operator!=(bag<T> const& b) const {
    return !(*this == b);
}

/* private methods */
template <typename T>
void bag<T>::push_back(const T& info) {
    if (empty()) {
        push_front(info);
    }
    else {
        m_tail->next = new node{ info, nullptr };
        m_tail = m_tail->next;
    }
}

template <typename T>
void bag<T>::push_front(const T& info) {

    if (empty()) {
        m_head = m_tail = new node{ info, nullptr };
    }
    else {
        m_head = new node{ info, m_head };
    }
}

template <typename T>
void bag<T>::pop_front() {
    if (empty()) {
        return;
    }

    if (m_head == m_tail)
    {
        delete m_head;
        m_head = m_tail = nullptr;
        return;
    }

    node* tmp = m_head;
    m_head = m_head->next;
    delete tmp;
}

template <typename T>
void bag<T>::pop_back() {
    if (empty()) {
        return;
    }
    else {
        node* ptr = m_head;
        while (ptr->next != m_tail) {
            ptr = ptr->next;
        }

        delete m_tail;
        ptr->next = nullptr;
        m_tail = ptr;
    }
}

template <typename T>
void bag<T>::clean() {
    while(!empty()) {
        pop_front();
    }
}

template <typename T>
void bag<T>::sort() {
    if(empty() || m_head == m_tail) {
        return;
    }

    node* ptr = m_head;
    node* nptr = m_head->next;
    
    while(ptr && nptr) {
        while(nptr) {

            if(*(ptr->info.get_label()) > *(nptr->info.get_label())) {
                swap(ptr, nptr);
            }

            nptr = nptr->next;
        }

        ptr = ptr->next;
        nptr = ptr->next;
    }
}

template <typename T>
void bag<T>::swap(node* a, node* b) {
    auto al_tmp = a->info.get_label();
    T tmp = a->info;
    a->info = b->info;
    b->info = tmp;

    a->info.set_label(b->info.get_label());
    b->info.set_label(al_tmp);
}

/* public methods */
template <typename T>
typename bag<T>::node const* bag<T>::head() const {
    return m_head;
}

template <typename T>
typename bag<T>::node* bag<T>::head() {
    return m_head;
}

template <typename T>
typename bag<T>::node const* bag<T>::tail() const {
    return m_tail;
}

template <typename T>
typename bag<T>::node* bag<T>::tail() {
    return m_tail;
}

/* adds elements in ascending order*/
template <typename T>
void bag<T>::add(const T& t) {
    if (empty()) {
        push_front(t);
        return;
    }

    if (*(t.get_label()) < *(m_head->info.get_label())) {
        push_front(t);
        return;
    }

    if (*(m_tail->info.get_label()) < *(t.get_label())) {
        push_back(t);
        return;
    }

    node* ptr = m_head;
    bool inserted = false;
    while (ptr->next && !inserted) {
        if (*(t.get_label()) < *(ptr->next->info.get_label())) {
            node* n = new node{ t, ptr->next };
            ptr->next = n;
            inserted = true;
        }
        ptr = ptr->next;
    }
}

template <typename T>
bool bag<T>::contains(const T& info) const {
    for(const_iterator it = begin(); it != end(); ++it) {
        if( *(it->get_label()) == *(info.get_label()) ) {
            return true;
        }
    }

    return false;
}

template <typename T>
bool bag<T>::empty() const {
    return m_head == nullptr;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, bag<T> const& b) {
    os << "[ ";
    for(T const& el : b) {
        os << *(el.get_label()) << " ";
    }

    os << "]";

    return os;
}