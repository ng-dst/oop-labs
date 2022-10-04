#include "list.h"

#include <iostream>

namespace List {

    Item* getItemPtr(List& given_list, size_t index) {
        if (index >= given_list.length)
            return nullptr;
        if (index+1 == given_list.length)
            return given_list.tail;
        Item* item = given_list.head;
        for (size_t i = 0; i < index; i++)
            item = item->next;
        return item;
    }

    void* pop(List& given_list, size_t index) {
        void* x = nullptr;
        if (given_list.length <= index || !given_list.head)
            return nullptr;
        if (index == 0) {
            Item* prev = given_list.head;
            x = prev->data;
            given_list.head = given_list.head->next;
            if (!given_list.head)
                given_list.tail = nullptr;
            delete prev;
        }
        else if (index+1 < given_list.length) {
            Item* prev = getItemPtr(given_list, index - 1);
            Item* to_pop = prev->next;
            x = to_pop->data;
            prev->next = to_pop->next;
            delete to_pop;
        }
        else if (index+1 == given_list.length && given_list.length >= 2) {
            Item* prev = getItemPtr(given_list, given_list.length - 2);
            x = given_list.tail->data;
            given_list.tail = prev;
            delete prev->next;
            prev->next = nullptr;
        }
        given_list.length--;
        return x;
    }

    void push(List& given_list, void* x) {
        Item* ptr = new Item {x, given_list.head};
        given_list.head = ptr;
        given_list.length++;

        if (given_list.length == 1)
            given_list.tail = given_list.head;
    }

    void append(List& given_list, void* x) {
        if (given_list.length) {
            Item* ptr = new Item {x, nullptr};
            Item* last = given_list.tail;
            last->next = ptr;
            given_list.tail = ptr;
            given_list.length++;
        }
        else push(given_list, x);
    }

    void insert(List& given_list, size_t index, void* x) {
        if (index+1 > given_list.length) {
            append(given_list, x);
            return;
        }
        if (index == 0) {
            push(given_list, x);
            return;
        }
        Item* prev = getItemPtr(given_list, index-1);
        Item* ptr = new Item {x, prev->next};
        prev->next = ptr;
        given_list.length++;
    }

    std::ostream& print(std::ostream& stream, List& given_list) {
        Item* cur = given_list.head;
        for (size_t i = 0; i < given_list.length; i++) {
            stream << (int*) cur->data << " ";
            cur = cur->next;
        }
        stream << std::endl;
        return stream;
    }

}