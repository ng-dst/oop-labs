#ifndef OOP_TABLEVECTOR_H
#define OOP_TABLEVECTOR_H

#ifndef INFO_LENGTH
#define INFO_LENGTH 32
#endif

namespace Lab3 {
    struct TableElem {
        int key;
        char info[INFO_LENGTH]{};
        TableElem(): key(0) { info[0] = '\0'; }
    };
}

#endif //OOP_TABLEVECTOR_H
