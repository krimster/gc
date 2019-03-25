#include <iostream>
#include <new>
#include "gc.h"


class MyClass {
    int a;
    int b;

public:
    double val;

    MyClass(int x, int y) {
         a = x;
         b = y;
         val = 0.0;
    }

    ~MyClass() {
        cout << "Destructing MyClass (" <<
        a << ", " << b << ")\n";
    }

    int sum() {
        return a + b;
    }

    friend std::ostream &operator<<(std::ostream &strm, MyClass &obj);
};

// An overloaded inserter to display MyClass
std::ostream &operator<< (std::ostream &strm, MyClass &obj) {
    strm << "(" << obj.a << " " << obj.b << ")";
    return strm;
}

int main() {

    try {

        GCPtr<MyClass> ob = new MyClass(10, 20);

        // Show value via overloaded inserter
        std::cout << *ob << endl;

        // Change object pointed to by ob
        ob = new MyClass(11, 21);
        std::cout << *ob << endl;

        // Call a member function through GCPtr
        std::cout << "Sum is : " << ob->sum() << endl;

        // Assign a value to a class member through a GCPtr
        ob->val = 98.6;
        std::cout << "ob->va: " << ob->val << endl;

        std::cout << "ob is now " << *ob << endl;

    } catch (bad_alloc &exc) {
        std::cout << "Allocation error!\n";
        return 1;
    }

    return 0;
}