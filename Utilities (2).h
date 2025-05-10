#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
template<typename T>
void handleException(const T& msg) {
    std::cerr << "Error: " << msg << "\n";
}
#endif
