#include <iostream>
#include <cstring>
#include "OrderedTable.h"

namespace Lab3 {

    // -------------------------------- Constructors -------------------------------- //

    OrderedTable::OrderedTable() {
        length = 0;
        max_size = quota;
        _vector = (TableElem**) calloc(quota, sizeof(void*));
    }

    OrderedTable::OrderedTable(const OrderedTable &t) {
        length = t.length;
        max_size = length + quota;
        _vector = (TableElem**) calloc(max_size, sizeof(void*));
        for (size_t i = 0; i < length; i++) {
            auto te = (TableElem*) malloc(sizeof(TableElem));
            te->key = t._vector[i]->key;
            te->info = strdup(t._vector[i]->info);
            _vector[i] = te;
        }
    }

    OrderedTable::OrderedTable(OrderedTable&& t) noexcept {
        length = t.length;
        max_size = t.max_size;
        _vector = t._vector;
        t.length = 0;
        t._vector = nullptr;
    }

    OrderedTable::~OrderedTable() {
        if (_vector) {
            for (int i = 0; i < length; i++) {
                free(_vector[i]->info);
                free(_vector[i]);
            }
            free(_vector);
        }
    }

    // -------------------------------- Internal utilities -------------------------------- //

    size_t OrderedTable::_findIndex(const int key) const {
        if (!length)
            return 0;
        size_t low = 0, high = length, mid;
        while (high > low) {
            mid = (low + high)/2;
            if (_vector[mid]->key == key)
                return mid;
            if (_vector[mid]->key < key)
                low = mid + 1;
            else
                high = mid;
        }
        return low;
    }

    void OrderedTable::_cleanup() {
        size_t i = 0;
        while (i < length) {
            if (!_vector[i])
                memmove(&_vector[i], &_vector[i+1], (length - i)*sizeof(void*));
            i++;
        }
    }

    void OrderedTable::_extend() {
        _vector = (TableElem**) realloc(_vector, (max_size + quota) * 3/2 * sizeof(void*));
        max_size += quota;
    }

    void OrderedTable::_shrink() {
        _vector = (TableElem**) realloc(_vector, (length + quota)*sizeof(void*));
        max_size = length + quota;
    }

    // -------------------------------- Read / Write methods -------------------------------- //

    void OrderedTable::add(TableElem* elem) {
        size_t i = _findIndex(elem->key);
        if (i < length && _vector[i]->key == elem->key) {
            throw std::invalid_argument("Cannot add: duplicate key");
        }
        if (length >= max_size) _extend();
        memmove(&_vector[i+1], &_vector[i], (length - i)*sizeof(void*));
        _vector[i] = elem;
        length++;
    }

    void OrderedTable::add(const int key, const char* info) {
        if (!info)
            throw std::invalid_argument("Cannot add: info is nullptr");
        auto elem = (TableElem*) malloc(sizeof(TableElem));
        elem->key = key;
        elem->info = strdup(info);
        add(elem);
    }

    void OrderedTable::update(const int key, const char *info) {
        if (!info)
            throw std::invalid_argument("Cannot update: info is nullptr");
        size_t i = _findIndex(key);
        if (i >= length || _vector[i]->key != key)
            throw std::invalid_argument("Could not update element: key not found");
        free(_vector[i]->info);
        _vector[i]->info = strdup(info);
    }

    const char* OrderedTable::find(const int key) const {
        if (!length)
            return nullptr;
        size_t i = _findIndex(key);
        if (i < length && _vector[i]->key == key)
            return _vector[i]->info;
        return nullptr;
    }

    void OrderedTable::rm(const int key) {
        if (!length)
            throw std::invalid_argument("Cannot remove element from empty table");
        size_t i = _findIndex(key);
        if (i >= length || _vector[i]->key != key)
            throw std::invalid_argument("Could not remove element: key not found");
        free(_vector[i]->info);
        free(_vector[i]);
        _vector[i] = nullptr;
        _cleanup();
        length--;
        if (length < max_size - 2*quota) _shrink();
    }

    std::istream& OrderedTable::inputElem(std::istream &stream, const int key) {
        size_t i = _findIndex(key);
        if (length != 0 && i < length && _vector[i]->key == key)
            throw std::invalid_argument("Element already present");
        char buf[info_length];
        stream.get(buf, info_length);
        if (!stream.good())
            throw std::runtime_error("Could not input element info from istream");
        add(key, buf);
        return stream;
    }

    std::ostream& OrderedTable::print(std::ostream &stream) const {
        for (size_t i = 0; i < length; i++)
            stream << "[" << _vector[i]->key << "]:  '" << _vector[i]->info << "'" << std::endl;
        return stream;
    }

    // -------------------------------- Overloaded operators -------------------------------- //

    OrderedTable& OrderedTable::operator=(const OrderedTable &t) {
        if (this != &t) {
            if (_vector) {
                for (int i = 0; i < length; i++) {
                    free(_vector[i]->info);
                    free(_vector[i]);
                }
                free(_vector);
            }
            length = t.length;
            max_size = length + quota;
            _vector = (TableElem**) calloc(max_size, sizeof(void*));
            for (size_t i = 0; i < length; i++) {
                auto te = (TableElem*) malloc(sizeof(TableElem));
                te->key = t._vector[i]->key;
                te->info = strdup(t._vector[i]->info);
                _vector[i] = te;
            }
        }
        return *this;
    }

    OrderedTable& OrderedTable::operator=(OrderedTable &&t) noexcept {
        if (this != &t) {
            if (_vector) {
                for (int i = 0; i < length; i++) {
                    free(_vector[i]->info);
                    free(_vector[i]);
                }
                free(_vector);
            }
            length = t.length;
            max_size = t.max_size;
            _vector = t._vector;
            t.length = 0;
            t._vector = nullptr;
        }
        return *this;
    }

    OrderedTable::operator bool() const {
        return length != 0;
    }

    const char*& OrderedTable::operator[](int key) const {
        return (const char*&) (*(OrderedTable*) this)[key];
    }

    char*& OrderedTable::operator[](int key) {
        if (!length)
            throw std::invalid_argument("Trying to assign an element in empty table");
        size_t i = _findIndex(key);
        if (i < length && _vector[i]->key == key)
            return _vector[i]->info;
        throw std::invalid_argument("Trying to access non-existent element");
    }

    int OrderedTable::operator[](const char *info) const {
        for (size_t i = 0; i < length; i++) {
            if (!strcmp(info, _vector[i]->info))
                return _vector[i]->key;
        }
        throw std::invalid_argument("Could not find string in the table");
    }

    const OrderedTable OrderedTable::operator--(int) {
        if (!length) rm(0);  // will throw
        OrderedTable obj(*this);
        int k = this->_vector[this->length - 1]->key;
        this->rm(k);
        return obj;
    }

    OrderedTable &OrderedTable::operator--() {
        if (!length) rm(0);  // will throw
        int k = this->_vector[this->length - 1]->key;
        this->rm(k);
        return *this;
    }

    OrderedTable &OrderedTable::operator+=(const OrderedTable &t) {
        for (size_t i = 0; i < t.length; i++) {
            auto elem = (TableElem*) malloc(sizeof(TableElem));
            elem->key = t._vector[i]->key;
            elem->info = strdup(t._vector[i]->info);
            this->add(elem);
        }
        return *this;
    }

    OrderedTable OrderedTable::operator+(const OrderedTable &t) {
        OrderedTable tmp(*this);
        tmp += t;
        return tmp;
    }

    std::ostream &operator<<(std::ostream &stream, const OrderedTable &t) {
        return t.print(stream);
    }

    std::istream &operator>>(std::istream &stream, OrderedTable &t) {
        int k;
        char buf[info_length];
        stream >> k;
        if (!stream.good()) return stream;
        stream >> buf;
        if (stream.good()) t.add(k, buf);
        return stream;
    }

}