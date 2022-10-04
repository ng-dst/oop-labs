#include <iostream>
#include <cstring>

#include "../utils/input.h"
#include "spmatrix.h"

void task(int* b, SpMatrix::SparseMatrix& sp) {
    size_t i = 0;
    SpMatrix::Row* r;
    SpMatrix::Elem* e;
    List::Item* cur = sp.rows->head, *rc;
    while (cur) {                                                   // iterating through list of rows
        r = (SpMatrix::Row*) cur->data;
        while (i < r->row) b[i++] = 0;                              // filling space between non-adjacent rows
        if (r->elems->length < sp.width)
            b[i++] = SpMatrix::get(sp, r->row, sp.width-1);  // not all elems are present, => not all > 0 => last
        else {
            rc = r->elems->head;
            while (rc) {
                e = (SpMatrix::Elem*) rc->data;
                if (e->value <= 0) break;
                rc = rc->next;
            }
            b[i++] = rc ? SpMatrix::get(sp, r->row, sp.width-1)  // not all > 0,  => last
                        : SpMatrix::get(sp, r->row, 0);          // all > 0,      => first
        }
        cur = cur->next;
    }
    while (i < sp.height) {
        b[i++] = 0;
    }
}

void print_commands() {
    std::cout << "set   -  place the value to a cell" << std::endl;
    std::cout << "get   -  get the value from a cell" << std::endl;
    std::cout << "print -  print the whole matrix" << std::endl;
    std::cout << "task  -  form a vector: \n"
                 "i-th element is the first in the i-th row (if the row contains positive numbers only), "
                 "otherwise - the last in the row" << std::endl;
    std::cout << "exit  -  exit the program" << std::endl;
}

void interactive() {
    std::cout << "Lab 1: sparse matrices" << std::endl;
    std::cout << " --- Matrix setup ---" << std::endl;

    char command[32];

    size_t h, w, r, c;
    int x;
    std::cout << "Enter matrix size" << std::endl;
    std::cout << "Height  " << std::ends;
    if (Input::getNumInRange(h, 1ul, (size_t) INT64_MAX) == -1) return;
    std::cout << "Width  " << std::ends;
    if (Input::getNumInRange(w, 1ul, (size_t) INT64_MAX) == -1) return;

    auto* sp = new SpMatrix::SparseMatrix(h, w);

    std::cout << "For command list, enter '?'" << std::endl;
    while (true) {
        if (Input::input(command) == -1) break;
        if (command[0] == '?') print_commands();

        else if (!strcmp("set", command)) {
            std::cout << "Row  " << std::ends;
            if (Input::getNumInRange(r, 0ul, h) == -1) break;
            std::cout << "Column  " << std::ends;
            if (Input::getNumInRange(c, 0ul, w) == -1) break;
            std::cout << "Value   " << std::ends;
            if (Input::input(x) == -1) break;
            try {
                SpMatrix::set(*sp, r, c, x);
            } catch (std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
        }
        else if (!strcmp("get", command)) {
            std::cout << "Row  " << std::ends;
            if (Input::getNumInRange(r, 0ul, h) == -1) break;
            std::cout << "Column  " << std::ends;
            if (Input::getNumInRange(c, 0ul, w) == -1) break;
            try {
                std::cout << "[" << r << "; " << c << "]:  " << SpMatrix::get(*sp, r, c) << std::endl;
            } catch (std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
        }
        else if (!strcmp("print", command)) {
            SpMatrix::print(std::cout, *sp);
        }
        else if (!strcmp("task", command)) {
            int* b = new int[h];
            task(b, *sp);
            std::cout << "Vector {b_i}:" << std::endl;
            for (size_t i = 0; i < h; i++)
                std::cout << b[i] << " ";
            std::cout << std::endl;
            delete[] b;
        }

        else if (!strcmp("exit", command)) break;
        else std::cout << "Unknown command. Try again" << std::endl;
    }
    SpMatrix::clear(*sp);
}

int main() {
    interactive();
    return 0;
}