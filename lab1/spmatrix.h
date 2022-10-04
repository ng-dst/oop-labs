#ifndef LAB1_SPMATRIX_H
#define LAB1_SPMATRIX_H

#include <iostream>
#include <cstddef>
#include "lib/list.h"

namespace SpMatrix {

    struct SparseMatrix {
        size_t height;
        size_t width;
        List::List* rows;

        SparseMatrix(size_t h, size_t w, List::List& rows) : height(h), width(w), rows(&rows) {}
        SparseMatrix(size_t h, size_t w) : height(h), width(w), rows(nullptr) {
            rows = new List::List;
        }
    };

    struct Row {
        size_t row;
        List::List* elems;

        Row(size_t row, List::List& elems) : row(row), elems(&elems) {}
        explicit Row(size_t row) : row(row), elems(nullptr) {
            elems = new List::List;
        }
    };

    struct Elem {
        size_t column;
        int value;

        Elem(size_t col, int value) : column(col), value(value) {}
    };

    void set(SparseMatrix& sp, size_t row, size_t col, int value);
    int get(SparseMatrix& sp, size_t row, size_t col);
    std::ostream& print(std::ostream& stream, SparseMatrix& sp);
    void clear(SparseMatrix& sp);

}

#endif //LAB1_SPMATRIX_H
