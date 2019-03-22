#include <iostream>
#include <new>
#include "gc.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    GCPtr<int> p;

    try {
        p = new int;
    } catch (bad_alloc exc) {
        return 1;
    }

    *p = 88;

    cout << "Value at p is: " << *p << endl;

    int k  = *p;

    cout << "k is " << k << endl;

    return 0;
}