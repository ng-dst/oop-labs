#include <cmath>

#include "../../Google_tests/lib/googletest/include/gtest/gtest.h"
#include "LemniscateBooth.h"

TEST (LemniscateBoothConstructor, DefaultConstructor) {
    AlgebraicCurves::LemniscateBooth b1;
    ASSERT_DOUBLE_EQ(1.0, b1.getM());
    ASSERT_DOUBLE_EQ(1.0, b1.getC());
    auto p = b1.polarCoords();
    ASSERT_NEAR(sqrt(3.0), p[0], 1e-4);
    ASSERT_NEAR(1.0, p[1], 1e-4);
    delete [] p;
}

TEST (LemniscateBoothConstructor, InitConstructor) {
    AlgebraicCurves::LemniscateBooth b2(5.0, 2.0);
    ASSERT_DOUBLE_EQ(5.0, b2.getM());
    ASSERT_DOUBLE_EQ(2.0, b2.getC());
    AlgebraicCurves::LemniscateBooth b3(b2);
    ASSERT_DOUBLE_EQ(5.0, b3.getM());
    ASSERT_DOUBLE_EQ(2.0, b3.getC());
}

TEST (LemniscateBoothSetters, Setters) {
    AlgebraicCurves::LemniscateBooth bc;
    bc.setM(2.0);
    bc.setC(-9.0);
    ASSERT_DOUBLE_EQ(2.0, bc.getM());
    ASSERT_DOUBLE_EQ(-9.0, bc.getC());
    auto p = bc.polarCoords();
    ASSERT_NEAR(1.0, p[0], 1e-4);
    ASSERT_NEAR(sqrt(17), p[1], 1e-4);
    delete[] p;
}

TEST (LemniscateBoothProps, Type) {
    AlgebraicCurves::LemniscateBooth b4(5.0, 2.0);
    ASSERT_EQ(AlgebraicCurves::ELLIPTIC, b4.curveType());
    AlgebraicCurves::LemniscateBooth b5(1.0, -10.0);
    ASSERT_EQ(AlgebraicCurves::HYPERBOLIC, b5.curveType());
    AlgebraicCurves::LemniscateBooth b6(3.0, 0.0);
    ASSERT_EQ(AlgebraicCurves::BERNULLI, b6.curveType());
    AlgebraicCurves::LemniscateBooth b7(1.0, -2.0);
    ASSERT_EQ(AlgebraicCurves::TWO_CIRCLES, b7.curveType());
}

TEST (LemniscateBoothProps, Area) {
    AlgebraicCurves::LemniscateBooth b8(5.0, 2.0);
    ASSERT_NEAR(157.07963, b8.area(), 1e-4);
    AlgebraicCurves::LemniscateBooth b9(1.0, -10.0);
    ASSERT_NEAR(3.529541, b9.area(), 1e-4);
    AlgebraicCurves::LemniscateBooth ba(1.0, -2.0);
    ASSERT_NEAR(6.283185, ba.area(), 1e-4);
    AlgebraicCurves::LemniscateBooth bb(1.0, 0.0);
    ASSERT_NEAR(2.000000, bb.area(), 1e-4);
}