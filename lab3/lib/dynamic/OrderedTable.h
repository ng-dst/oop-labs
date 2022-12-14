#ifndef OOP_ORDEREDTABLE_H
#define OOP_ORDEREDTABLE_H

#include <cstddef>
#include "TableElemDynamic.h"

namespace Lab3 {
    static const size_t quota = 32;
    static const size_t info_length = 32;

    class OrderedTable {
    private:
        size_t max_size;
        TableElem** _vector;
        void _cleanup();
        void _extend();
        void _shrink();
        [[nodiscard]] size_t _findIndex(int key) const;
    public:
        size_t length;
        OrderedTable();
        OrderedTable(const OrderedTable& t);
        OrderedTable(OrderedTable&& t) noexcept;
        ~OrderedTable();

        std::istream& inputElem(std::istream& stream, int key);
        std::ostream& print(std::ostream& stream) const;
        [[nodiscard]] const char *find(int key) const;
        void add(TableElem* elem);
        void add(int key, const char* info);
        void rm(int key);
        void update(int key, const char* info);

        OrderedTable& operator = (const OrderedTable& t);
        OrderedTable& operator = (OrderedTable&& t) noexcept;
        OrderedTable operator + (const OrderedTable& t);
        OrderedTable& operator += (const OrderedTable& t);

        friend std::ostream& operator << (std::ostream& stream, const OrderedTable& t);
        friend std::istream& operator >> (std::istream& stream, OrderedTable& t);

        OrderedTable& operator -- ();
        const OrderedTable operator -- (int);

        char*& operator [] (int key);
        const char*& operator [] (int key) const;
        int operator [] (const char* info) const;

        operator bool() const; // здесь без explicit для удобства записи выражений типа  if(table) { ... }
                               // (подразумевается проверка на непустоту таблицы)
    };

}

#endif //OOP_ORDEREDTABLE_H
