#include "LemniscateBooth.h"
#include <cmath>
#include <cstdio>

namespace AlgebraicCurves {

    LemniscateBooth::LemniscateBooth() {
        _m = 1.0;
        _c = 1.0;
        calculatePolar();
    }
    LemniscateBooth::LemniscateBooth(const double m, const double c) {
        _m = m;
        _c = c;
        calculatePolar();
    }
    LemniscateBooth::LemniscateBooth(LemniscateBooth &lem) {
    _m = lem.getM();
    _c = lem.getC();
    calculatePolar();
    }

    double LemniscateBooth::getM() const {
        return _m;
    }

    double LemniscateBooth::getC() const {
        return _c;
    }

    void LemniscateBooth::setM(const double m) {
        _m = m;
        calculatePolar();
    }

    void LemniscateBooth::setC(const double c) {
        _c = c;
        calculatePolar();
    }

    void LemniscateBooth::calculatePolar() {
        _2m2 = _m * _m * 2;
        _a2 = fabs(_2m2 + _c);
        _b2 = fabs(_2m2 - _c);
    }

    CurveType LemniscateBooth::curveType() const {
        if (_c == 0.0) return CIRCLE;
        if (_c == -_2m2 || _c == _2m2) return TWO_CIRCLES;
        if (-_2m2 < _c && _c < _2m2) return ELLIPTIC;
        return HYPERBOLIC;
    }

    double LemniscateBooth::area() const {
        CurveType t = curveType();
        if (t == ELLIPTIC)
            return pi/2 * (_a2 + _b2);
        if (t == HYPERBOLIC) {
            double a = sqrt(_a2), b = sqrt(_b2);
            return (_a2 - _b2) / 2 * atan2(a, b) + a*b/2;
        }
        if (t == CIRCLE) {
            return pi * _a2;
        }
        // two circles
        return pi * _2m2;
    }

    double LemniscateBooth::radius(const double w) const {
        CurveType t = curveType();
        if (t == ELLIPTIC)
            return sqrt(_a2 * cos(w)*cos(w) + _b2 * sin(w)*sin(w));
        if (t == HYPERBOLIC)
            return sqrt(_a2 * cos(w)*cos(w) - _b2 * sin(w)*sin(w));
        if (t == CIRCLE) {
            return sqrt(_a2);
        }
        double s = sqrt(_a2) * fabs(cos(w));
        return s;
    }

    double* LemniscateBooth::polarCoords() const {
        auto* c = new double[2]();
        c[0] = sqrt(_a2);
        c[1] = sqrt(_b2);
        return c;
    }

    char* LemniscateBooth::repr() const {
        static const char* fmt = "Lemniscate of Booth\n"
                                 "Type:                    %s\n"
                                 "Equation (cartesian):    (x^2 + y^2)^2 - (%.3lf) x^2 + (%.3lf) y^2 = 0\n"
                                 "Parameters (cartesian):  m = %.3lf, c = %.3lf\n"
                                 "Equation (polar):        r^2 = %.3lf cos^2(w) %c %.3lf sin^2(w)\n"
                                 "Parameters (polar):      a = %.3lf, b = %.3lf\n"
                                 "Area:                    %.4lf\n";
        auto* s = new char[512]();
        CurveType type = curveType();
        const char *t = (const char*[]) {
                "Elliptic",
                "Hyperbolic",
                "Circle",
                "Two circles"
        }[type];
        snprintf(s, 511, fmt,
                 t,
                 _2m2+_c, _2m2-_c,
                 _m, _c,
                 _a2, type == HYPERBOLIC ? '-' : '+', _b2,
                 sqrt(_a2), sqrt(_b2),
                 area());
        return s;
    }

}