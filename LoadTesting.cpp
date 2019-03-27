#include <iostream>
#include <new>
#include <limits>
#include "gc.h"

// A simple class for load testing GCPtr
class LoadTest {

private:
    int a;
    int b;

public:
    double n[100000]; // just to take up memory
    double val;

    LoadTest() {
        a = b = 0;
    }

    LoadTest(int x, int y) {
        a = x;
        b = y;
        val = 0.0;
    }

    friend std::ostream &operator<< (std::ostream &strm, LoadTest &obj);
};

// Create an inserter for LoadTest
std::ostream &operator<< (std::ostream &strm, LoadTest &obj) {
    strm << "(" << obj.a << " " << obj.b << ")";
    return strm;
}

int main() {

    GCPtr<LoadTest> mp;
    int i;

    for (int j = 0; j < 20000; ++j) {
        try {

            mp = new LoadTest(i, i);

        } catch (bad_alloc xa) {

            // When an allocation error occurs, recycle
            // garbage by calling collect().
            std::cout << "Last object: " << *mp << endl;
            std::cout << "Length of gclist before calling collect(): "
            << mp.gclistSize() << endl;

            GCPtr<LoadTest>::collect();
            std::cout << "Length of gclist after calling collect(): "
            << mp.gclistSize() << endl;
        }
    }
    return 0;
}