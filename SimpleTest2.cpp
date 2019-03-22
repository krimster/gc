#include <iostream>
#include <new>
#include "gc.h"

int main() {

    GCPtr<int> p;
    GCPtr<int> q;

    try {

        p = new int(10);
        q = new int(11);

        std::cout << "Value at p is: " << *p << endl;
        std::cout << "Value at q is: " << *q << endl;

        std::cout << "Before entering block. \n";

        // Now create a local object
        { // start block

            GCPtr<int> r = new int(12);
            std::cout << "Value at r is: " << *r << endl;
        } // end the block causing r to go out of scope

        std::cout << "After exiting block.\n";


    } catch (bad_alloc exc) {
        std::cout << "Allocation failure!\n";
        return 1;
    }

    std::cout << "Done\n";

    return 0;
}

