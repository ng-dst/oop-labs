#include <iostream>
#include <cstring>
#include "OrderedTable.h"

namespace Lab3 {

    OrderedTable::OrderedTable() {
        length = 0;
    }

    OrderedTable::OrderedTable(size_t n, TableElem* vector) {
        if (!vector)
            throw std::invalid_argument("Cannot copy: vector is nullptr");
        length = n;
        memcpy(_vector, vector, n*sizeof(TableElem));
    }

    size_t OrderedTable::_findIndex(const int key) const {
        if (!length)
            return 0;
        size_t low = 0, high = length, mid;
        while (high > low) {
            mid = (low + high)/2;
            if (_vector[mid].key == key)
                return mid;
            if (_vector[mid].key < key)
                low = mid + 1;
            else
                high = mid;
        }
        return low;
    }

    void OrderedTable::_cleanup() {
        size_t i = 0;
        while (i < length) {
            if (!_vector[i].info[0])
                memmove(&_vector[i], &_vector[i+1], (length - i)*sizeof(TableElem));
            i++;
        }
    }

    void OrderedTable::add(const TableElem &elem) {
        if (length >= max_size)
            throw std::overflow_error("Could not add new element: table is full");
        size_t i = _findIndex(elem.key);
        memmove(&_vector[i+1], &_vector[i], (length - i)*sizeof(TableElem));
        _vector[i] = elem;
        length++;
    }

    void OrderedTable::add(const int key, const char* info) {
        if (!info)
            throw std::invalid_argument("Cannot add: info is nullptr");
        TableElem elem;
        elem.key = key;
        strncpy(elem.info, info, info_length);
        add(elem);
    }

    void OrderedTable::update(const int key, const char *info) {
        if (!info)
            throw std::invalid_argument("Cannot update: info is nullptr");
        size_t i = _findIndex(key);
        if (length == 0 || _vector[i].key != key)
            throw std::invalid_argument("Could not update element: key not found");
        strncpy(_vector[i].info, info, info_length);
    }

    const char* OrderedTable::find(const int key) const {
        if (!length)
            return nullptr;
        size_t i = _findIndex(key);
        if (_vector[i].key == key)
            return _vector[i].info;
        return nullptr;
    }

    void OrderedTable::rm(const int key) {
        if (!length)
            throw std::invalid_argument("Cannot remove element from empty table");
        size_t i = _findIndex(key);
        if (_vector[i].key != key)
            throw std::invalid_argument("Could not remove element: key not found");
        _vector[i].key = 0;
        _vector[i].info[0] = '\0';
        _cleanup();
        length--;
    }

    std::istream& OrderedTable::inputElem(std::istream &stream, const int key) {
        size_t i = _findIndex(key);
        if (length == 0 || _vector[i].key != key) {
            add(key, "");
        }
        else throw std::invalid_argument("Element already present");
        stream.get(_vector[i].info, info_length);
        // stream >> _vector[i].info;
        return stream;
    }

    std::ostream& OrderedTable::print(std::ostream &stream) const {
        for (size_t i = 0; i < length; i++)
            stream << "[" << _vector[i].key << "]:  '" << _vector[i].info << "'" << std::endl;
        return stream;
    }

}