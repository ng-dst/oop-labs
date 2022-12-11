#include <iostream>
#include <cstring>

#include "input.h"
#include "OrderedTable.h"

void print_commands() {
    std::cout << "add    -  add new element" << std::endl;
    std::cout << "update -  update info for existing element" << std::endl;
    std::cout << "input  -  input new element from stdin" << std::endl;
    std::cout << "find   -  find element by key" << std::endl;
    std::cout << "rm     -  remove element" << std::endl;
    std::cout << "print  -  print the entire table" << std::endl;
    std::cout << "exit   -  exit the program" << std::endl;
}

void interactive() {
    std::cout << "Lab 3:  Container classes" << std::endl;
    std::cout << " --- Ordered vector-table --- " << std::endl;

    char command[32];
    char info[Lab3::info_length];
    const char* s;
    int k;

    Lab3::OrderedTable t;
    std::cout << "For command list, enter '?'" << std::endl;

    while (true) {
        try {
            if (Input::input(command) == EOF) break;
            if (command[0] == '?') print_commands();

            else if (!strcmp("add", command)) {
                std::cout << "Key:  " << std::ends;
                if (Input::input(k) == EOF) break;
                std::cout << "Info:  " << std::ends;
                if (Input::input(info) == EOF) break;
                t.add(k, info);
                std::cout << "Element added." << std::endl;
            }
            else if (!strcmp("update", command)) {
                std::cout << "Key:  " << std::ends;
                if (Input::input(k) == EOF) break;
                std::cout << "Info:  " << std::ends;
                if (Input::input(info) == EOF) break;
                t.update(k, info);
                std::cout << "Info updated." << std::endl;
            }
            else if (!strcmp("input", command)) {
                std::cout << "Key:  " << std::ends;
                if (Input::input(k) == EOF) break;
                std::cout << "Info:  " << std::ends;
                std::cin.ignore();
                t.inputElem(std::cin, k);
                std::cout << "Element added." << std::endl;
            }
            else if (!strcmp("find", command)) {
                std::cout << "Key:  " << std::ends;
                if (Input::input(k) == EOF) break;
                s = t.find(k);
                if (!s) std::cout << "Element not found." << std::endl;
                else std::cout << "[" << k << "]:  '" << s << "'" << std::endl;
            }
            else if (!strcmp("rm", command)) {
                std::cout << "Key:  " << std::ends;
                if (Input::input(k) == EOF) break;
                t.rm(k);
                std::cout << "Element removed." << std::endl;
            }
            else if (!strcmp("print", command)) {
                t.print(std::cout);
            }

            else if (!strcmp("exit", command)) break;
            else std::cout << "Unknown command. Try again" << std::endl;

        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    interactive();
    return 0;
}