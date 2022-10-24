#ifndef UTILS_INPUT_H
#define UTILS_INPUT_H

#include <iostream>

namespace Input {
    template <class T>
    int input(T &a) {
        while (true) {
            std::cout << "> " << std::ends;
            std::cin >> a;
            if (std::cin.good())
                return 0;
            if (std::cin.eof())
                return EOF;
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Try again" << std::endl;
        }
    }

    template <class T>
    int getNumInRange(T &a, T nmin, T nmax) {
        while (true) {
            if (input(a) == -1) return -1;
            if (a < nmin || a > nmax) {
                std::cout << "Invalid size. Try again" << std::endl;
            } else return 0;
        }
    }

}

#endif
