#include <iostream>
#include <cstring>

#include "../utils/input.h"
#include "src/LemniscateBooth.h"

void print_commands() {
    std::cout << "set    -  set m, c parameters of curve" << std::endl;
    std::cout << "get    -  get the curve parameters m, c" << std::endl;
    std::cout << "print  -  print info about curve" << std::endl;
    std::cout << "polar  -  get polar parameters a, b" << std::endl;
    std::cout << "area   -  calculate area inside curve" << std::endl;
    std::cout << "radius -  calculate distance from (0,0) to curve for angle w" << std::endl;
    std::cout << "exit   -  exit the program" << std::endl;
}

void interactive() {
    std::cout << "Lab 2:  Algebraic curves" << std::endl;
    std::cout << " --- Lemniscate of Booth setup ---" << std::endl;

    char command[32];
    double m, c;
    std::cout << "Enter curve parameters:" << std::endl;
    std::cout << "m:  " << std::ends;
    if (Input::input(m) == -1)
        return;
    std::cout << "c:  " << std::ends;
    if (Input::input(c) == -1)
        return;

    auto* booth = new AlgebraicCurves::LemniscateBooth(m, c);
    std::cout << "For command list, enter '?'" << std::endl;
    while (true) {
        if (Input::input(command) == -1) break;
        if (command[0] == '?') print_commands();

        else if (!strcmp("set", command)) {
            std::cout << "Enter curve parameters:  (_ to skip)" << std::endl;
            std::cout << "m: " << std::ends;
            std::cin >> m;
            if (std::cin.good()) {
                booth->setM(m);
                std::cout << "m set to " << m << std::endl;
            } else {
                std::cin.clear();
                std::cin.ignore();
            }
            std::cout << "c: " << std::ends;
            std::cin >> c;
            if (std::cin.good()) {
                booth->setC(c);
                std::cout << "c set to " << c << std::endl;
            } else {
                std::cin.clear();
                std::cin.ignore();
            }
        }
        else if (!strcmp("get", command)) {
            std::cout << "m = " << booth->getM() << std::endl;
            std::cout << "c = " << booth->getC() << std::endl;
        }
        else if (!strcmp("area", command)) {
            std::cout << "S = " << booth->area() << std::endl;
        }
        else if (!strcmp("polar", command)) {
            auto polar = booth->polarCoords();
            std::cout << "a = " << polar[0] << std::endl;
            std::cout << "b = " << polar[1] << std::endl;
            delete[] polar;
        }
        else if (!strcmp("radius", command)) {
            std::cout << "w: " << std::ends;
            if (Input::input(m) == -1) break;
            std::cout << "r(" << m << ") = " << booth->radius(m) << std::endl;
        }
        else if (!strcmp("print", command)) {
            char* s = booth->repr();
            std::cout << s << std::endl;
            delete[] s;
        }

        else if (!strcmp("exit", command)) break;
        else std::cout << "Unknown command. Try again" << std::endl;
    }
    delete booth;
}




int main() {
    interactive();
    return 0;
}
