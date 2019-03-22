#include <iostream>
#include <new>
#include "gc.h"

int main() {

    try {

        // Create a GCPtr to an allocated array of 10 ints
        GCPtr<int> ap = new int[10];

        // Give the array some values using an array indexing
        for (int i = 0; i < 10; ++i) {
            ap[i] = i;
        }

        // Now show the content of the array.
        for (int j = 0; j < 10; ++j) {
            std::cout << ap[j] << " ";
        }
         cout << endl;

    } catch (bad_alloc exc) {
        std::cout << "Allocation failure!\n";
        return 1;
    }
}