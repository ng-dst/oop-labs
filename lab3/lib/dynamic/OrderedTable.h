#ifndef OOP_ORDEREDTABLE_H
#define OOP_ORDEREDTABLE_H

#include <cstddef>
#include "TableElem.h"

#ifndef SIZE
#define SIZE 1024
#endif

namespace Lab3 {

    class OrderedTable {
    private:
        TableElem _vector[SIZE];
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
