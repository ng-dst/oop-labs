#ifndef OOP_MY_LIST_H
#define OOP_MY_LIST_H

#include <iostream>
#include <algorithm>


template <class T> class node;
template <class T> class my_list_iterator;


template <class T>
class my_list
{
public:
    typedef my_list_iterator<T> iterator;

    my_list();
    my_list(const my_list<T> & l);
    ~my_list();

    [[nodiscard]] bool empty() const;
    [[nodiscard]] unsigned int size() const;
    T & back() const;
    T & front() const;
    void push_front(const T & x);
    void push_back(const T & x);
    void pop_front();
    void pop_back();
    iterator begin() const;
    iterator end() const;
    void erase(iterator & pos);
    my_list<T> & operator=(const my_list<T> & l);

protected:
    node<T> * head;
    node<T> * tail;
    unsigned int length;
};

template <class T>
my_list<T>::my_list()
{
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template <class T>
my_list<T>::my_list(const my_list & l)
{
    head = nullptr;
    tail = nullptr;
    length = 0;
    for (node<T> * current = l.head; current != nullptr; current = current -> next_node)
        push_back(current->value);
}

template <class T>
typename my_list<T>::iterator my_list<T>::begin() const
{
    return iterator(head);
}

template <class T>
class node
{
private:
    explicit node(const T & x): value(x), next_node(nullptr), prev_node(nullptr) {}

    T value;
    node<T> * next_node;
    node<T> * prev_node;

    friend class my_list<T>;
    friend class my_list_iterator<T>;
};

template <class T> class my_list_iterator
{
public:
    typedef my_list_iterator<T> iterator;

    my_list_iterator(): current_node(nullptr) { }
    explicit my_list_iterator(node<T> * source_node): current_node(source_node) { }
    explicit my_list_iterator(my_list_iterator<T> * source_iterator): current_node(source_iterator->current_node) { }

    T & operator*();
    my_list_iterator<T> & operator=(const iterator & obj);
    bool operator==(const iterator & obj) const;
    bool operator!=(const iterator & obj) const;
    iterator & operator++();
    const my_list_iterator<T> operator++(int);

protected:
    node<T> * current_node;

    friend class my_list<T>;
};

template <class T>
T & my_list_iterator<T>::operator*()
{
    return current_node->value;
}

template <class T>
my_list_iterator<T> & my_list_iterator<T>::operator++()
{
    current_node = current_node->next_node;
    return *this;
}

template<class T>
const my_list_iterator<T> my_list_iterator<T>::operator++(int) {
    auto iter = iterator(*this);
    current_node = current_node->next_node;
    return iter;
}

template <class T>
void my_list<T>::push_back(const T & x)
{
    auto * new_node = new node<T> (x);
    if (head == nullptr)
        head = tail = new_node;
    else
    {
        new_node->prev_node = tail;
        tail->next_node = new_node;
        tail = new_node;
    }
    length++;
}

template<class T>
void my_list<T>::push_front(const T &x) {
    auto * new_node = new node<T> (x);
    if (head == nullptr)
        head = tail = new_node;
    else
    {
        new_node->next_node = head;
        head->prev_node = new_node;
        head = new_node;
    }
    length++;
}

template <class T>
typename my_list<T>::iterator my_list<T>::end() const
{
    return iterator((node<T>*) nullptr);
}

template <class T>
my_list <T>::~my_list()
{
    node <T> * first = head;
    while (first != nullptr)
    {
        node <T> * next = first->next_node;
        delete first;
        first = next;
    }
}

template<class T>
bool my_list<T>::empty() const {
    return length == 0;
}

template<class T>
unsigned int my_list<T>::size() const {
    return length;
}

template<class T>
T & my_list<T>::back() const {
    return tail->value;
}

template<class T>
T &my_list<T>::front() const {
    return head->value;
}

template<class T>
void my_list<T>::pop_front() {
    if (head == nullptr) throw std::out_of_range("popping from empty list");
    auto* prev_head = head;
    head = head->next_node;
    delete prev_head;
    length--;
}

template<class T>
void my_list<T>::pop_back() {
    if (tail == nullptr) throw std::out_of_range("popping from empty list");
    auto* prev_tail = tail;
    tail = tail->prev_node;
    delete prev_tail;
    length--;
}

template<class T>
void my_list<T>::erase(my_list_iterator<T> &pos) {
    node<T>* cur = pos.current_node;
    if (!cur) return;
    if (cur->next_node) cur->next_node->prev_node = cur->prev_node;
    else tail = cur->prev_node;
    if (cur->prev_node) cur->prev_node->next_node = cur->next_node;
    else head = cur->next_node;
    length--;
    delete cur;
}

template<class T>
my_list<T> &my_list<T>::operator=(const my_list<T> &l) {
    if (&l == this) return *this;
    length = 0;
    head = nullptr;
    tail = nullptr;
    for (node<T> * current = l.head; current != nullptr; current = current -> next_node)
        push_back(current->value);
    return *this;
}

template<class T>
bool my_list_iterator<T>::operator==(const iterator & obj) const
{
    return ( this->current_node == obj.current_node );
}

template <class T>
bool my_list_iterator<T>::operator!=(const iterator & obj) const
{
    return !( *this == obj );
}

template<class T>
my_list_iterator<T> &my_list_iterator<T>::operator=(const my_list_iterator::iterator &obj) {
    this->current_node = obj.current_node;
    return *this;
}


#endif //OOP_MY_LIST_H
