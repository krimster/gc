#include <iostream>
#include <new>
#include "gc.h"

int main() {

    GCPtr<int> p;
    GCPtr<int> q;

    try {

        p = new int(10);
        q = new int(11);

        cout << "Value at p is: " << *p << endl;
        cout << "Value at q is: " << *q << endl;

        cout << "Before entering block. \n";

        // Now create a local object
        { // start block

            GCPtr<int> r;
            r = new int(12);
            cout << "Value at r is: " << *r << endl;
        } // end the block causing r to go out of scope

        cout << "After exiting block.\n";


    } catch (bad_alloc exc) {
        cout << "Allocation failure!\n";
        return 1;
    }

    cout << "Done\n";

    return 0;
}

