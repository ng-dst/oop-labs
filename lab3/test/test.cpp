#include "../../Google_tests/lib/googletest/include/gtest/gtest.h"
#include "OrderedTable.h"

#include <cstring>

TEST (OrderedTableConstructor, DefaultConstructor) {
    Lab3::OrderedTable t1;
    ASSERT_EQ(0, t1.length);
    ASSERT_EQ(nullptr, t1.find(0));
}

TEST (OrderedTableConstructor, InitConstructor) {
    Lab3::TableElem vec[2];
    vec[0].key = 1234;
    strcpy(vec[0].info, "Sample text 1");
    vec[1].key = 1337;
    strcpy(vec[1].info, "Sample text 2");
    Lab3::OrderedTable t2(2, vec);
    const char* f = t2.find(1234);
    const char* g = t2.find(1337);
    ASSERT_NE(nullptr, f);
    ASSERT_NE(nullptr, g);
    ASSERT_EQ(nullptr, t2.find(999));
    ASSERT_EQ(nullptr, t2.find(1300));
    ASSERT_EQ(nullptr, t2.find(2900));
    ASSERT_EQ(0, strncmp("Sample text 1", f, INFO_LENGTH));
    ASSERT_EQ(0, strncmp("Sample text 2", g, INFO_LENGTH));
}

TEST (OrderedTableAdd, Add) {
    Lab3::OrderedTable t3;
    t3.add(27, "Info string 1");
    t3.add(36, "Info string 2");
    t3.add(42, "Info string 4");
    t3.add(40, "Info string 3");
    t3.add(21, "Info string 0");
    const char* f1 = t3.find(19);
    const char* f2 = t3.find(21); // +
    const char* f3 = t3.find(27); // +
    const char* f4 = t3.find(33);
    const char* f5 = t3.find(42); // +
    const char* f6 = t3.find(57);
    ASSERT_EQ(nullptr, f1);
    ASSERT_EQ(nullptr, f4);
    ASSERT_EQ(nullptr, f6);
    ASSERT_NE(nullptr, f2);
    ASSERT_NE(nullptr, f3);
    ASSERT_NE(nullptr, f5);
    Lab3::OrderedTable t6;
    for (int i = 0; i < SIZE; i++)
        t6.add(i, "aaa");
    ASSERT_THROW(t6.add(-2, "aaa"), std::overflow_error);
}

TEST (OrderedTableAdd, Update) {
    Lab3::OrderedTable t4;
    t4.add(147, "info1");
    ASSERT_THROW(t4.update(999, "111"), std::invalid_argument);
    t4.update(147, "info2");
    ASSERT_NE(nullptr, t4.find(147));
}

TEST (OrderedTableRm, Remove) {
    Lab3::OrderedTable t5;
    ASSERT_THROW(t5.rm(0), std::invalid_argument);
    t5.add(9, "aaa");
    t5.add(5, "aaa");
    t5.add(7, "aaa");
    ASSERT_THROW(t5.rm(-99), std::invalid_argument);
    t5.rm(5);
    ASSERT_EQ(nullptr, t5.find(5));
}

