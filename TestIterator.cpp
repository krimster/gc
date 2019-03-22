#include <iostream>
#include <new>
#include "gc.h"

int main() {

    try {
        // Create a GCPtr to an allocated array of ints
        GCPtr<int, 10> ap = new int[10];

        // Declare an int iterator
        GCPtr<int>::GCIterator itr;

        // Assign itr a pointer to the start of the array
        itr = ap.begin();

        // Give the array for values using array indexing
        for (unsigned i = 0; i < itr.size(); ++i) {
            ap[i] = i;
        }

        // Now cycle through the array using the iterator
        for (itr = ap.begin(); itr != ap.end(); itr++) {
            std::cout << *itr << " ";
        }
        std::cout << endl;

    } catch (bad_alloc exc) {
        std::cout << "Allocation failurea!\n";
        return 1;
    } catch (OutOfRangeExc exc) {
        std::cout << "Out of range access!\n";
        return 1;
    }

    return 0;
}
