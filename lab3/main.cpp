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
    std::cout << " --- Ordered vector-table setup ---" << std::endl;

    char command[32];
    char info[Lab3::info_length];
    const char* s;
    int k;
    std::cout << "configuration: size=" << Lab3::max_size << ", actual length=0, allocation=static" << std::endl;

    Lab3::OrderedTable t;
    std::cout << "For command list, enter '?'" << std::endl;

    while (true) {
        if (Input::input(command) == -1) break;
        if (command[0] == '?') print_commands();

        else if (!strcmp("add", command)) {
            std::cout << "Key:  " << std::ends;
            if (Input::input(k) == -1) break;
            std::cout << "Info:  " << std::ends;
            if (Input::input(info) == -1) break;
            t.add(k, info);
            std::cout << "Element added." << std::endl;
        }
        else if (!strcmp("update", command)) {
            std::cout << "Key:  " << std::ends;
            if (Input::input(k) == -1) break;
            std::cout << "Info:  " << std::ends;
            if (Input::input(info) == -1) break;
            try {
                t.update(k, info);
                std::cout << "Info updated." << std::endl;
            }
            catch (std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        else if (!strcmp("input", command)) {
            std::cout << "Key:  " << std::ends;
            if (Input::input(k) == -1) break;
            std::cout << "Info:  " << std::ends;
            try {
                std::cin.ignore();
                t.inputElem(std::cin, k);
                std::cout << "Element added." << std::endl;
            }
            catch (std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        else if (!strcmp("find", command)) {
            std::cout << "Key:  " << std::ends;
            if (Input::input(k) == -1) break;
            s = t.find(k);
            if (!s) std::cout << "Element not found." << std::endl;
            else std::cout << "[" << k << "]:  '" << s << "'" << std::endl;
        }
        else if (!strcmp("rm", command)) {
            std::cout << "Key:  " << std::ends;
            if (Input::input(k) == -1) break;
            try {
                t.rm(k);
                std::cout << "Element removed." << std::endl;
            }
            catch (std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        else if (!strcmp("print", command)) {
            t.print(std::cout);
        }

        else if (!strcmp("exit", command)) break;
        else std::cout << "Unknown command. Try again" << std::endl;
    }
}

int main(int argc, char** argv) {
    interactive();
    return 0;
}