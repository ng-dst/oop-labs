#include "../../Google_tests/lib/googletest/include/gtest/gtest.h"

#ifdef DYNAMIC
 #include "dynamic/OrderedTable.h"
#else
 #include "overloaded/OrderedTable.h"
#endif

TEST (OrderedTableConstructor, CopyConstructor) {
    Lab3::OrderedTable t1;
    t1.add(123, "456");
    Lab3::OrderedTable t2(t1);
    ASSERT_EQ(1, t2.length);
    ASSERT_STREQ("456", t2.find(123));
}

TEST (OrderedTableOperator, Index) {
    Lab3::OrderedTable t3;
    t3.add(21, "Info string");
    const Lab3::OrderedTable td(t3);
    const char* f2 = td[21]; // const ref operator is called
    ASSERT_NE(nullptr, f2);
    ASSERT_EQ(21, t3["Info string"]);
    auto s = strdup("abcdefgh");
    t3[21] = s; // non-const ref operator is called
    ASSERT_STREQ(t3[21], s);
    ASSERT_THROW(t3[-99] = s, std::invalid_argument);
}

TEST (OrderedTableOperator, Plus) {
    Lab3::OrderedTable t4;
    t4.add(123, "456");
    Lab3::OrderedTable t5;
    t5.add(345, "678");
    auto t6 = t4 + t5;
    ASSERT_NE(nullptr, t6.find(123));
    ASSERT_NE(nullptr, t6.find(345));
    t5 += t4;
    ASSERT_NE(nullptr, t5.find(123));
    ASSERT_NE(nullptr, t5.find(345));
}

TEST (OrderedTableOperator, Bool) {
    Lab3::OrderedTable t7;
    ASSERT_EQ(false, t7);
    ASSERT_EQ(true, !t7);
    t7.add(123, "456");
    ASSERT_EQ(true, t7);
    ASSERT_EQ(false, !t7);
}

TEST (OrderedTableOperator, Dec) {
    Lab3::OrderedTable t8;
    ASSERT_THROW(t8--, std::invalid_argument);
    ASSERT_THROW(--t8, std::invalid_argument);
    t8.add(123, "456");
    t8.add(26, "789");
    auto t9 = t8--;
    ASSERT_EQ(2, t9.length);
    ASSERT_EQ(nullptr, t8.find(123));
    auto ta = --t9;
    ASSERT_EQ(1, ta.length);
    ASSERT_EQ(1, t9.length);
    ASSERT_EQ(nullptr, t9.find(123));
}

TEST (OrderedTableOperator, Output) {
    Lab3::OrderedTable tb;
    tb.add(1234, "5678");
    tb.add(456, "9abc");
    std::stringstream s;
    s << tb;
    char str[16];
    s >> str;
    ASSERT_STREQ("[456]:", str);
    s >> str;
    ASSERT_STREQ("'9abc'", str);
    s >> str;
    ASSERT_STREQ("[1234]:", str);
    s >> str;
    ASSERT_STREQ("'5678'", str);
}

TEST (OrderedTableOperator, Input) {
    Lab3::OrderedTable tc;
    std::stringstream s("123\nabcdef\n");
    s >> tc;
    ASSERT_NE(nullptr, tc.find(123));
    ASSERT_STREQ("abcdef", tc.find(123));
}