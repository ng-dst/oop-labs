#include "spmatrix.h"

namespace SpMatrix {

    void set(SparseMatrix& sp, size_t row, size_t col, int value) {
        if (row < 0 || row >= sp.height || col < 0 || col >= sp.width)
            throw std::invalid_argument("Matrix indices are out of range");
        if (sp.rows->length == 0) {
            Elem* elem = new Elem(col, value);
            Row* r = new Row(row);
            List::push(*r->elems, elem);
            List::push(*sp.rows, r);
        }
        else if (sp.rows->length != 0) {
            List::Item* cur = sp.rows->head, *prev = nullptr;
            // search through sorted  List of Rows  by  row
            while (cur && ((Row*) cur->data)->row < row) {
                prev = cur;
                cur = cur->next;
            }
            if (!cur) {  // reached end of the list, the new row = last
                Elem *elem = new Elem(col, value);
                Row *r = new Row(row);
                List::push(*r->elems, elem);
                List::append(*sp.rows, r);
            }
            else if (((Row*) cur->data)->row == row) {  // such row exists
                // search through sorted  List of Elems  by  col  inside a row
                Row* r = (Row*) cur->data;
                List::Item* rc = r->elems->head, *rp = nullptr;
                while (rc && ((Elem*) rc->data)->column < col) {
                    rp = rc;
                    rc = rc->next;
                }
                if (!rc) {  // end of the row, last col
                    Elem* elem = new Elem(col, value);
                    List::append(*r->elems, elem);
                }
                else if (((Elem*) rc->data)->column == col) {  // exact same element exists, replacing
                    Elem* elem = (Elem*) rc->data;
                    elem->value = value;
                }
                else if (!rp) {  // no iters, first col
                    Elem* elem = new Elem(col, value);
                    List::push(*r->elems, elem);
                }
                else {  // insert a new elem in the row
                    Elem* elem = new Elem(col, value);
                    rp->next = new List::Item(elem, rc);
                    r->elems->length++;
                }
            }
            else if (!prev) {  // no iterations, the new row = first
                Elem* elem = new Elem(col, value);
                Row* r = new Row(row);
                List::push(*r->elems, elem);
                List::push(*sp.rows, r);
            }
            else {  // insert a new row
                Elem* elem = new Elem(col, value);
                Row* r = new Row(row);
                List::push(*r->elems, elem);
                prev->next = new List::Item(r, cur);
                sp.rows->length++;
            }
        }

    }

    int get(SparseMatrix& sp, size_t row, size_t col) {
        if (row < 0 || row >= sp.height || col < 0 || col >= sp.width)
            throw std::invalid_argument("Matrix indices are out of range");
        if (sp.rows->length == 0) return 0;
        List::Item* cur;
        for (cur = sp.rows->head; cur && ((Row*) cur->data)->row < row; cur = cur->next);
        if (!cur || ((Row*) cur->data)->row != row) return 0;
        Row* r = (Row*) cur->data;
        for (cur = r->elems->head; cur && ((Elem*) cur->data)->column < col; cur = cur->next);
        if (!cur || ((Elem*) cur->data)->column != col) return 0;
        return ((Elem*) cur->data)->value;
    }

    std::ostream& print(std::ostream& stream, SparseMatrix& sp) {
        stream << "Matrix (" << sp.height << " rows, " << sp.width << " columns):" << std::endl;
        for (size_t i = 0; i < sp.height; i++) {
            for (size_t j = 0; j < sp.width; j++)
                stream << get(sp, i, j) << " ";
            stream << std::endl;
        }
        stream << std::endl;
        return stream;
    }

    void clear(SparseMatrix& sp) {
        while (sp.rows->head) {
            Row* r = (Row*) List::pop(*sp.rows);
            while (r->elems->head) {
                Elem* e = (Elem*) List::pop(*r->elems);
                delete e;
            }
            delete r->elems;
            delete r;
        }
        delete sp.rows;
        delete &sp;
    }
}