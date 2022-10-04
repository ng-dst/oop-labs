#ifndef LAB1_LIST_H
#define LAB1_LIST_H

#include <cstddef>

namespace List {

    struct Item {
        void* data;
        Item* next;

        explicit Item(void* data, Item* next = nullptr) : data(data), next(next) {}
    };

    struct List {
        size_t length;
        Item* head;
        Item* tail;

        List() : length(0), head(nullptr), tail(nullptr) {}
    };

    Item* getItemPtr(List& given_list, size_t index);
    void* popNext(List& given_list, Item* prev);
    void clear(List* given_list, size_t index);
    void clear(Item* given_item);

    void* get(List& given_list, size_t index);
    void* pop(List& given_list, size_t index = 0);
    void push(List& given_list, void* x);
    void append(List& given_list, void* x);
    void insert(List& given_list, size_t index, void* x);
    void print(List& given_list, const char& format);
    void clear(List& given_list);
}

#endif //LAB1_LIST_H
