#ifndef OOP_TABLEVECTOR_H
#define OOP_TABLEVECTOR_H

namespace Lab3 {
    struct TableElem {
        int key;
        char* info;
        TableElem(): key(0), info(nullptr) {}
    };
}

#endif //OOP_TABLEVECTOR_H
