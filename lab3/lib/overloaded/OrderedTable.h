#ifndef OOP_ORDEREDTABLE_H
#define OOP_ORDEREDTABLE_H

#include <cstddef>
#include "TableElemStatic.h"

namespace Lab3 {
    static const size_t max_size = 1024;

    class OrderedTable {
    private:
        TableElem _vector[max_size];
        void _cleanup();
        [[nodiscard]] size_t _findIndex(int key) const;
    public:
        size_t length;
        OrderedTable();
        OrderedTable(size_t n, TableElem* vector);
        OrderedTable(const OrderedTable& t);

        std::istream& inputElem(std::istream& stream, int key);
        std::ostream& print(std::ostream& stream) const;
        [[nodiscard]] const char *find(int key) const;
        void add(const TableElem& elem);
        void add(int key, const char* info);
        void rm(int key);
        void update(int key, const char* info);

        OrderedTable operator + (const OrderedTable& t) const;
        OrderedTable& operator += (const OrderedTable& t);

        friend std::ostream& operator << (std::ostream& stream, const OrderedTable& t);
        friend std::istream& operator >> (std::istream& stream, OrderedTable& t);

        OrderedTable& operator -- ();
        const OrderedTable operator -- (int);

        char*& operator [] (int key);
        const char* operator [] (int key) const;
        int operator [] (const char* info) const;

        operator bool() const;
    };

}

#endif //OOP_ORDEREDTABLE_H
