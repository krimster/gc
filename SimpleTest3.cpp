#include <iostream>
#include <new>
#include "gc.h"

int main() {

    try {
        // Allocate and discard objects
        GCPtr<int> p = new int(1);
        p = new int(2);
        p = new int(3);
        p = new int(4);

        // Manually collect unused objects for
        // demonstration purposes
        GCPtr<int>::collect();

        std::cout << "*p: " << *p << endl;

    } catch (bad_alloc exc) {
        std::cout << "Allocation failure!\n";
        return 1;
    }
    return 0;
}