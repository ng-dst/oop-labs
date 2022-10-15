#ifndef OOP_TABLEVECTOR_H
#define OOP_TABLEVECTOR_H

namespace Lab3 {
    static const size_t info_length = 32;
    struct TableElem {
        int key;
        char info[info_length]{};
        TableElem(): key(0) { info[0] = '\0'; }
    };
}

#endif //OOP_TABLEVECTOR_H
