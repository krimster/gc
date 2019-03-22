#include <iostream>
#include <new>
#include "gc.h"

int main() {

    GCPtr<int> p;

    try {
        p = new int;
    } catch (bad_alloc exc) {
        return 1;
    }

    *p = 88;

    std::cout << "Value at p is: " << *p << endl;

    int k  = *p;

    std::cout << "k is " << k << endl;

    return 0;
}