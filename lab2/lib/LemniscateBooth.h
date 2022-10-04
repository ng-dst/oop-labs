#ifndef LAB2_LEMNISCATEBOOTH_H
#define LAB2_LEMNISCATEBOOTH_H

#include "CurveType.h"

namespace AlgebraicCurves {
    static const double pi = 3.1415926;

    class LemniscateBooth {
    /*     1. class state
     *     2. constructors
     *     3. type of curve
     *     4. area
     *     5. polar params
     *     6. r(w) in polar
     *     7. text repr()
     */
    private:
        // cartesian:   (x^2 + y^2)^2 - (2m^2 + n)x - (2m^2 - n)y = 0
        double _2m2=0.0, _m, _c;
        /* polar:
         *     -2m^2 < c < 2m^2:   r^2 = a^2 cos w + b^2 sin w
         *             c > 2m^2:   r^2 = a^2 cos w - b^2 sin w
         *            c < -2m^2:   r^2 = - a^2 cos w + b^2 sin w
         */
        double _a2=0.0, _b2=0.0;
        //  a2 = |2m2 + c|    b2 = |2m2 - c|
        void calculatePolar();
    public:
        LemniscateBooth();
        LemniscateBooth(double m, double c);
        LemniscateBooth(LemniscateBooth& lem);

        [[nodiscard]] double getM() const;
        [[nodiscard]] double getC() const;

        void setM(double);
        void setC(double);

        [[nodiscard]] CurveType curveType() const;
        [[nodiscard]] double area() const;
        [[nodiscard]] double radius(double w) const;
        [[nodiscard]] double* polarCoords() const;

        [[nodiscard]] char* repr() const;
    };
}

#endif //LAB2_LEMNISCATEBOOTH_H
