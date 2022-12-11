#ifndef OOP_ORDEREDTABLE_H
#define OOP_ORDEREDTABLE_H

#include <cstddef>
#include "TableElemStatic.h"

namespace Lab3 {

    class OrderedTable {
    public:
        static const size_t max_size = 1024;

    private:
        TableElem _vector[max_size];
        void _cleanup();
        [[nodiscard]] size_t _findIndex(int key) const;
    public:

        size_t length;
        OrderedTable();
        OrderedTable(size_t n, TableElem* vector);

        std::istream& inputElem(std::istream& stream, int key);
        std::ostream& print(std::ostream& stream) const;
        [[nodiscard]] const char *find(int key) const;
        void add(const TableElem& elem);
        void add(int key, const char* info);
        void rm(int key);
        void update(int key, const char* info);
    };

}

#endif //OOP_ORDEREDTABLE_H
